#include "polygon.h"

Polygon::Polygon()
{

}

Polygon::Polygon(QVector<QVector<int> > new_m_polygonVertexIndices, QVector<QVector<int> > new_m_polygonTextureVertexIndices, QVector<QVector<int> > new_m_polygonNormalVertexIndices)
{
    m_polygonVertexIndices = new_m_polygonVertexIndices;
    m_polygonTextureVertexIndices = new_m_polygonTextureVertexIndices;
    m_polygonNormalVertexIndices = new_m_polygonNormalVertexIndices;
}

QVector<QVector<int> > Polygon::getPoligonVertexIndices()
{
    return m_polygonVertexIndices;
}

QVector<QVector<int> > Polygon::getPoligonTextureVertexIndices()
{
    return m_polygonTextureVertexIndices;
}

QVector<QVector<int> > Polygon::getPoligonNormalVertexIndices()
{
    return m_polygonNormalVertexIndices;
}

QVector<QVector<int> > Polygon::addPoligonVertexIndices(QVector<int> verticesInd)
{
    m_polygonVertexIndices.append(verticesInd);
    return m_polygonVertexIndices;
}

QVector<QVector<int> > Polygon::addPoligonTextureVertexIndices(QVector<int> verticesInd)
{
    m_polygonTextureVertexIndices.append(verticesInd);
    return m_polygonTextureVertexIndices;
}

QVector<QVector<int> > Polygon::addPoligonNormalVertexIndices(QVector<int> verticesInd)
{
    m_polygonNormalVertexIndices.append(verticesInd);
    return m_polygonNormalVertexIndices;
}


