#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include "drawableobject.h"
#include "camera.h"
#include "drawablemesh.h"

class Viewport : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit Viewport(Camera *camera, QWidget *parent = nullptr);
    virtual ~Viewport() override;
    void addObject(DrawableObject *drawableObject);
    void removeObject(DrawableObject *drawableObject);
    void clearObjects();

    void setCameraCordinates(QVector3D newCor);
    static QVector3D fitToView(QVector<QVector3D> vertices);

protected:
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;
    float aspectRatio() const;
    static void qglClearColor(const QColor &color);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void doZooming(const QPoint &dstPos);
    void doRotation(const QPoint &dstPos);
    void doPanning(const QPoint &dstPos);
    void doWheelZooming(float delta);


    static QVector3D unprojectScreenPointToEye(const QPoint &pos, float depth, const QMatrix4x4 &projectionMatrix, const QSize &screenSize);
protected:
    enum class NavigationState {
        None = 0,
        Pan = 1,
        Zoom = 2,
        Rotate = 3
    };
    QVector<DrawableObject *> m_drawableObjects;
    Camera *m_camera = nullptr;
    QColor m_backgroundColor = QColor(54, 57, 63);
    NavigationState m_navigationState = NavigationState::None;
    QPoint m_srcPos;
    QQuaternion m_cameraRotation;
};

#endif // VIEWPORT_H
