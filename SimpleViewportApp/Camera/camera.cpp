#include "camera.h"
#include <QtMath>

Camera::Camera()
{
}

QMatrix4x4 Camera::viewMatrix() const
{
    QMatrix4x4 cameraToWorld = cameraToWorldMatrix();
    bool invertible = true;
    QMatrix4x4 worldToCamera = cameraToWorld.inverted(&invertible);
    Q_ASSERT(invertible);
    return worldToCamera;
}

QMatrix4x4 Camera::projectionMatrix(float screenAspectRatio) const
{
    float ySide = m_zNear * tan(degToRad(m_fovY) / 2);
    float xMax = ySide * screenAspectRatio;
    float yMax = ySide;
    float xMin = -xMax;
    float yMin = -yMax;
    QMatrix4x4 projectionMatrix;
    projectionMatrix.frustum(xMin, xMax, yMin, yMax, m_zNear, m_zFar);
    return projectionMatrix;
}

void Camera::setFov(float fov)
{
    m_fovY = fov;
}

void Camera::setZNear(float zNear)
{
    m_zNear = zNear;
}

void Camera::setZFar(float zFar)
{
    m_zFar = zFar;
}

void Camera::setOrigin(const QVector3D &origin)
{
    m_origin = origin;
}

void Camera::setRotation(const QQuaternion &rotation)
{
    m_rotation = rotation;
}

void Camera::setTarget(const QVector3D &target)
{
    m_target = target;
}

QQuaternion Camera::rotation() const
{
    return m_rotation;
}

QVector3D Camera::origin() const
{
    return m_origin;
}

QVector3D Camera::target() const
{
    return m_target;
}

QVector3D Camera::unproject(const QMatrix4x4 &projectionMatrix, const QPointF &normScreenPoint, float depth)
{
    float zEye = -depth;
    float w = projectionMatrix(3, 2) * zEye + projectionMatrix(3, 3) * 1;
    const float xClip = normScreenPoint.x() * w;
    const float yClip = normScreenPoint.y() * w;
    const float zClip = (projectionMatrix(2, 2) * zEye + projectionMatrix(2, 3));
    QVector4D ndcPoint(xClip, yClip, zClip, w);
    bool invertible = true;
    const QMatrix4x4 projectionMatrixInv = projectionMatrix.inverted(&invertible);
    Q_ASSERT(invertible);
    return QVector3D(projectionMatrixInv * ndcPoint);
}

QPointF Camera::screenPointToNormScreenPoint(const QPoint &screenPoint, const QSize &screenSize)
{
    float xNorm = 2 * (screenPoint.x()) / float(screenSize.width()) - 1;
    float yNorm = 1 - 2 *(screenPoint.y()) / float(screenSize.height());
    return QPointF(xNorm, yNorm);
}

float Camera::degToRad(float deg)
{
    return deg / 180 * M_PI;
}

QMatrix4x4 Camera::cameraToWorldMatrix() const
{
    QMatrix4x4 m;
    m.translate(m_target);
    m.rotate(m_rotation);
    m.translate(m_origin);
    return m;
}
