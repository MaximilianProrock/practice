#ifndef OBJWRITER_H
#define OBJWRITER_H

#include <QString>
#include <model.h>
#include <QVector>


class ObjWriter
{
public:
    static void write(Model model, QString fileName);

    static QString writeVertices(QVector<QString> vertices, QString token);
    static QVector<QString> convert3DVectorsToStringVectors(QVector<QVector3D> vertices);
    static QVector<QString> convert2DVectorsToStringVectors(QVector<QVector2D> vertices);

    static QString writeFace(
            QVector<QVector<int>> m_polygonVertexIndices,
            QVector<QVector<int>> m_polygonTextureVertexIndices,
            QVector<QVector<int>> m_polygonNormalVertexIndices,
            QString token);
    static QString writeFacePolygon(QVector<int> vertexIndPol, QVector<int> textureVertexIndPol, QVector<int> normalVertexIndPol);
    static QString writeFacePolygonWithoutTextures(QVector<int> vertexIndPol, QVector<int> normalVertexIndPol);
    static QString writeFacePolygonWithoutNormals(QVector<int> vertexIndPol, QVector<int> textureVertexIndPol);
    static QString writeFacePolygonWithoutTexturesAndNormals(QVector<int> vertexIndPol);

    static bool isModelReadyForRecording(Model model);
    static bool isPolygonReadyForRecording(QVector<QVector<int>> polygon);
protected:
    ObjWriter();

};

#endif // OBJWRITER_H
