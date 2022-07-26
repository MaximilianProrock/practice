#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>
#include <QVector3D>

class Camera
{
public:
    Camera();
    QMatrix4x4 viewMatrix() const;
    QMatrix4x4 projectionMatrix(float screenAspectRatio) const;
    void setFov(float fov);
    void setZNear(float zNear);
    void setZFar(float zFar);
    void setOrigin(const QVector3D &origin);
    void setRotation(const QQuaternion &rotation);
    void setTarget(const QVector3D &target);
    QQuaternion rotation() const;
    QVector3D origin() const;
    QVector3D target() const;
    static QVector3D unproject(const QMatrix4x4 &projectionMatrix, const QPointF &normScreenPoint, float depth);
    static QPointF screenPointToNormScreenPoint(const QPoint &screenPoint, const QSize &screenSize);
protected:
    float m_fovY = 25;
    float m_zNear = 0.01;
    float m_zFar = 1000;
    QVector3D m_origin = { 0, 0, 5 };
    QQuaternion m_rotation;
    QVector3D m_target;
protected:
    static float degToRad(float deg);
    QMatrix4x4 cameraToWorldMatrix() const;
};

#endif // CAMERA_H

