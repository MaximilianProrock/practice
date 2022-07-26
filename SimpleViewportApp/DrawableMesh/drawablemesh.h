#ifndef DRAWABLEMESH_H
#define DRAWABLEMESH_H

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include "drawableobject.h"

class DrawableMesh : public DrawableObject
{
public:
    DrawableMesh(QVector<QVector3D> vertices, QVector<int> polygonVertexIndices, QVector<int> polygonStart, QVector<QVector3D> normals, QVector<int> polygonNormalIndices, QVector3D colour, bool normalMap);
    ~DrawableMesh() override;
    void draw(QMatrix4x4 viewMatrix, QMatrix4x4 projectionMatrix) override;
    void setColour(QVector3D colour);
    void enableNormalMap(bool nm);
protected:
    QOpenGLBuffer *m_vertexBuffer = nullptr;
    QOpenGLBuffer *m_normalBuffer = nullptr;
    int m_nVertices = -1;
    QOpenGLShaderProgram *m_shader = nullptr;

    QVector3D colourVector;
    bool normalMapOn;
};

#endif // DRAWABLEMESH_H

