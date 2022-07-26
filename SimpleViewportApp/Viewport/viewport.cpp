#include "viewport.h"
#include <QOpenGLContext>
#include <QDebug>
#include <QMouseEvent>
#include "meshtools.h"
#include <cmath>

Viewport::Viewport(Camera *camera, QWidget *parent) :
    QOpenGLWidget(parent),
    m_camera(camera)
{
}

Viewport::~Viewport()
{
}

void Viewport::addObject(DrawableObject *drawableObject)
{
    m_drawableObjects.append(drawableObject);
}

void Viewport::removeObject(DrawableObject *drawableObject)
{
    int index = m_drawableObjects.indexOf(drawableObject);
    Q_ASSERT(index != -1);
    m_drawableObjects.removeAt(index);
}

void Viewport::clearObjects()
{
    m_drawableObjects.clear();
}

void Viewport::setCameraCordinates(QVector3D newCor)
{
    QVector3D origin = m_camera->origin();
    origin = newCor;
    //origin.setZ(origin.z() + 20);
    m_camera->setOrigin(origin);
}

void Viewport::initializeGL()
{
}

void Viewport::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void Viewport::paintGL()
{
    qglClearColor(m_backgroundColor);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (DrawableObject *drawableObject : m_drawableObjects)
        drawableObject->draw(m_camera->viewMatrix(), m_camera->projectionMatrix(aspectRatio()));
}

float Viewport::aspectRatio() const
{
    Q_ASSERT(height() != 0);
    return width() / float(height());
}

void Viewport::qglClearColor(const QColor &color)
{
    glClearColor(color.redF(), color.greenF(), color.blueF(), color.alphaF());
}

void Viewport::mousePressEvent(QMouseEvent *event)
{
    bool altPressed = (event->modifiers() == Qt::AltModifier);
    bool startPanning = (event->buttons() == Qt::MiddleButton) && altPressed;
    bool startRotating = (event->buttons() == Qt::LeftButton) && altPressed;
    if (startPanning) {
        m_navigationState = NavigationState::Pan;
        m_srcPos = event->pos();
    }
    bool startZooming = (event->buttons() == Qt::RightButton) && altPressed;
    if (startZooming) {
        m_navigationState = NavigationState::Zoom;
        m_srcPos = event->pos();
    }
    if (startRotating) {
        m_navigationState = NavigationState::Rotate;
        m_srcPos = event->pos();
        m_cameraRotation = m_camera->rotation();
    }
}

void Viewport::mouseMoveEvent(QMouseEvent *event)
{
    if (m_navigationState == NavigationState::Zoom)
        doZooming(event->pos());
    if (m_navigationState == NavigationState::Rotate)
        doRotation(event->pos());
    if (m_navigationState == NavigationState::Pan)
        doPanning(event->pos());
}

void Viewport::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    m_navigationState = NavigationState::None;
}

void Viewport::wheelEvent(QWheelEvent *event)
{
    doWheelZooming(event->delta());
}

void Viewport::doZooming(const QPoint &dstPos)
{
    const QPoint diff = dstPos - m_srcPos;
    float shift = -diff.x() - diff.y();
    QVector3D origin = m_camera->origin() * (1 + shift * 1e-3);
    m_camera->setOrigin(origin);
    m_srcPos = dstPos;
    update();
}

void Viewport::doRotation(const QPoint &dstPos)
{
    QPoint shift = dstPos - m_srcPos;
    float rotationSpeed = 0.1f;
    float angleX = -shift.y() * rotationSpeed;
    float angleY = -shift.x() * rotationSpeed;
    QQuaternion srcRotation = m_cameraRotation;
    QQuaternion dstRotationX = QQuaternion::fromAxisAndAngle(1, 0, 0, angleX);
    QQuaternion dstRotationY = QQuaternion::fromAxisAndAngle(0, 1, 0, angleY);
    QQuaternion dstRotation = dstRotationY * srcRotation * dstRotationX;
    m_cameraRotation = dstRotation;
    m_camera->setRotation(dstRotation);
    m_srcPos = dstPos;
    update();
}

void Viewport::doPanning(const QPoint &dstPos)
{
    QMatrix4x4 projectionMatrix = m_camera->projectionMatrix(aspectRatio());
    float depth = m_camera->origin().z();
    QVector3D srcPos3D = unprojectScreenPointToEye(m_srcPos, depth, projectionMatrix, size());
    QVector3D dstPos3D = unprojectScreenPointToEye(dstPos, depth, projectionMatrix, size());
    QVector3D shift = dstPos3D - srcPos3D;
    m_camera->setOrigin(m_camera->origin() - shift);
    m_srcPos = dstPos;
    update();
}

void Viewport::doWheelZooming(float delta)
{
    QVector3D origin = m_camera->origin();
    float speed = 1e-3f;
    //origin += -delta * origin * speed;
    origin.setZ(origin.z() + (-delta * origin.z() * speed));
    m_camera->setOrigin(origin);
    update();
}

QVector3D Viewport::fitToView(QVector<QVector3D> vertices)
{
    QVector3D minCor(vertices[0].x(), 0, 0);
    QVector3D maxCor(vertices[0].x(), 0, 0);
    for(int i = 1; i < vertices.size(); i ++){

        if(vertices[i].x() < minCor.x()){
            minCor.setX(vertices[i].x());
        } else if(vertices[i].x() > maxCor.x()){
            maxCor.setX(vertices[i].x());
        }

        if(vertices[i].y() < minCor.y()){
            minCor.setY(vertices[i].y());
        } else if(vertices[i].y() > maxCor.y()){
            maxCor.setY(vertices[i].y());
        }

        if(vertices[i].z() < minCor.z()){
            minCor.setZ(vertices[i].z());
        } else if(vertices[i].z() > maxCor.z()){
            maxCor.setZ(vertices[i].z());
        }
    }

    QVector3D vec(abs(maxCor.x() + minCor.x()) / 2,
                  abs(maxCor.y() + minCor.y()) / 2,
                  abs(maxCor.x() - minCor.x()) + (abs(maxCor.x() - minCor.x()) * sqrt(2)) / 2);

    return vec;
}

QVector3D Viewport::unprojectScreenPointToEye(const QPoint &pos, float depth, const QMatrix4x4 &projectionMatrix, const QSize &screenSize)
{
    QPointF normPos = Camera::screenPointToNormScreenPoint(pos, screenSize);
    return Camera::unproject(projectionMatrix, normPos, depth);
}
