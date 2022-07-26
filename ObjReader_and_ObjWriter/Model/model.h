#ifndef MODEL_H
#define MODEL_H

#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <polygon.h>


class Model
{
public:
    Model();

     QVector<QVector3D> getVerices();
     QVector<QVector2D> getTexureVerices();
     QVector<QVector3D> getNormalVerices();

     QVector<QVector<int>> getPoligonVertexIndices();
     QVector<QVector<int>> getPoligonTextureVertexIndices();
     QVector<QVector<int>> getPoligonNormalVertexIndices();

     QVector<QVector3D> addVerices(QVector3D vertex);
     QVector<QVector2D> addTexureVerices(QVector2D vertex);
     QVector<QVector3D> addNormalVerices(QVector3D vertex);

     QVector<QVector<int>> addPoligonVertexIndices(QVector<int> verticesInd);
     QVector<QVector<int>> addPoligonTextureVertexIndices(QVector<int> verticesInd);
     QVector<QVector<int>> addPoligonNormalVertexIndices(QVector<int> verticesInd);


     Polygon getPolygons();


//     QString toStringVerices();
//     QString toStringTexureVerices();
//     QString toStringNormalVerices();

protected:
    QVector<QVector3D> m_verices;
    QVector<QVector2D> m_texture_verices;
    QVector<QVector3D> m_normal_verices;

//    QVector<QVector<int>> m_polygonVertexIndices;
//    QVector<QVector<int>> m_polygonTextureVertexIndices;
//    QVector<QVector<int>> m_polygonNormalVertexIndices;

    Polygon polygon;
};

#endif // MODEL_H
