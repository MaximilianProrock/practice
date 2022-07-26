#ifndef DRAWABLEGRID_H
#define DRAWABLEGRID_H

#include <QOpenGLBuffer>
#include <QColor>
#include "drawableobject.h"

class DrawableGrid : public DrawableObject
{
public:
    DrawableGrid(double size, int nSegments, QColor color);
    void draw(QMatrix4x4 viewMatrix, QMatrix4x4 projectionMatrix) override;
protected:
    QOpenGLBuffer m_vertexBuffer;
    double m_size = 3.0;
    int m_nSegments = 10;
    QColor m_color = QColor(128, 128, 128);
};

#endif // DRAWABLEGRID_H

