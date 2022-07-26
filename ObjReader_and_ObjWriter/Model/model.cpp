#include "model.h"
#include <QVector>
#include <QVector2D>
#include <QVector3D>

Model::Model()
{

}

QVector<QVector3D> Model::getVerices()
{
    return m_verices;
}

QVector<QVector2D> Model::getTexureVerices()
{
    return m_texture_verices;
}

QVector<QVector3D> Model::getNormalVerices()
{
    return m_normal_verices;
}

QVector<QVector<int> > Model::getPoligonVertexIndices()
{
    return polygon.getPoligonVertexIndices();
}

QVector<QVector<int> > Model::getPoligonTextureVertexIndices()
{
    return polygon.getPoligonTextureVertexIndices();
}
QVector<QVector<int> > Model::getPoligonNormalVertexIndices()
{
    return polygon.getPoligonNormalVertexIndices();
}

QVector<QVector3D> Model::addVerices(QVector3D vertex)
{
    m_verices.append(vertex);
    return m_verices;
}

QVector<QVector2D> Model::addTexureVerices(QVector2D vertex)
{
    m_texture_verices.append(vertex);
    return m_texture_verices;
}

QVector<QVector3D> Model::addNormalVerices(QVector3D vertex)
{
    m_normal_verices.append(vertex);
    return m_normal_verices;
}

QVector<QVector<int> > Model::addPoligonVertexIndices(QVector<int> verticesInd)
{
    return polygon.addPoligonVertexIndices(verticesInd);
}

QVector<QVector<int> > Model::addPoligonTextureVertexIndices(QVector<int> verticesInd)
{
    return polygon.addPoligonTextureVertexIndices(verticesInd);
}
QVector<QVector<int> > Model::addPoligonNormalVertexIndices(QVector<int> verticesInd)
{
    return polygon.addPoligonNormalVertexIndices(verticesInd);
}

Polygon Model::getPolygons()
{
    return polygon;
}
