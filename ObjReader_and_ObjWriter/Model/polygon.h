#ifndef POLYGON_H
#define POLYGON_H

#include <QVector>

class Polygon
{
private:
    QVector<QVector<int>> m_polygonVertexIndices;
    QVector<QVector<int>> m_polygonTextureVertexIndices;
    QVector<QVector<int>> m_polygonNormalVertexIndices;
public:
    Polygon();
    Polygon(
            QVector<QVector<int>> new_m_polygonVertexIndices,
            QVector<QVector<int>> new_m_polygonTextureVertexIndices,
            QVector<QVector<int>> new_m_polygonNormalVertexIndices
            );
    QVector<QVector<int>> getPoligonVertexIndices();
    QVector<QVector<int>> getPoligonTextureVertexIndices();
    QVector<QVector<int>> getPoligonNormalVertexIndices();

    QVector<QVector<int>> addPoligonVertexIndices(QVector<int> verticesInd);
    QVector<QVector<int>> addPoligonTextureVertexIndices(QVector<int> verticesInd);
    QVector<QVector<int>> addPoligonNormalVertexIndices(QVector<int> verticesInd);
};

#endif // POLYGON_H
