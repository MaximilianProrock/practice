#include <QTest>
#include <QString>
#include "test_objwriter.h"
#include "objwriter.h"
#include "objwriterexception.h"

Test_ObjWriter::Test_ObjWriter(QObject *parent):
    QObject(parent)
{
}

void Test_ObjWriter::writeVertices()
{
    QVector<QString> vertices;
    vertices.append("1 2 3");
    QString result = ObjWriter::writeVertices(vertices, "v");
    QCOMPARE(result, "v 1 2 3\n");
}

void Test_ObjWriter::writeVertices_1()
{
    QVector<QString> vertices;
    vertices.append("1 2 3");
    vertices.append("12 26 48");
    QString result = ObjWriter::writeVertices(vertices, "v");
    QCOMPARE(result, "v 1 2 3\nv 12 26 48\n");
}

void Test_ObjWriter::writeVertices_2()
{
    QVector<QString> vertices;
    vertices.append("1 2 3");
    vertices.append("12 26 48");
    vertices.append("147.0007 48.458 78.001");
    QString result = ObjWriter::writeVertices(vertices, "v");
    QCOMPARE(result, "v 1 2 3\nv 12 26 48\nv 147.0007 48.458 78.001\n");
}

void Test_ObjWriter::writeTestureVertices()
{
    QVector<QString> vertices;
    vertices.append("1 2 3");
    QString result = ObjWriter::writeVertices(vertices, "vt");
    QCOMPARE(result, "vt 1 2 3\n");
}

void Test_ObjWriter::writeNormalVertices()
{
    QVector<QString> vertices;
    vertices.append("1 2 3");
    QString result = ObjWriter::writeVertices(vertices, "vn");
    QCOMPARE(result, "vn 1 2 3\n");
}

void Test_ObjWriter::writeFacePolygon()
{
    QVector<int> vertexIndPol;
    QVector<int> textureVertexIndPol;
    QVector<int> normalVertexIndPol;

    vertexIndPol.append(1);
    vertexIndPol.append(2);
    vertexIndPol.append(3);

    QString result = ObjWriter::writeFacePolygon(vertexIndPol, textureVertexIndPol, normalVertexIndPol);
    QCOMPARE(result, "2 3 4 ");
}

void Test_ObjWriter::writeFacePolygon_1()
{
    QVector<int> vertexIndPol;
    QVector<int> textureVertexIndPol;
    QVector<int> normalVertexIndPol;

    vertexIndPol.append(1);
    vertexIndPol.append(2);
    vertexIndPol.append(3);

    textureVertexIndPol.append(1);
    textureVertexIndPol.append(2);
    textureVertexIndPol.append(3);

    QString result = ObjWriter::writeFacePolygon(vertexIndPol, textureVertexIndPol, normalVertexIndPol);
    QCOMPARE(result, "2/2 3/3 4/4 ");
}

void Test_ObjWriter::writeFacePolygon_2()
{
    QVector<int> vertexIndPol;
    QVector<int> textureVertexIndPol;
    QVector<int> normalVertexIndPol;

    vertexIndPol.append(1);
    vertexIndPol.append(2);
    vertexIndPol.append(3);

    textureVertexIndPol.append(1);
    textureVertexIndPol.append(2);
    textureVertexIndPol.append(3);

    normalVertexIndPol.append(1);
    normalVertexIndPol.append(2);
    normalVertexIndPol.append(3);

    QString result = ObjWriter::writeFacePolygon(vertexIndPol, textureVertexIndPol, normalVertexIndPol);
    QCOMPARE(result, "2/2/2 3/3/3 4/4/4 ");
}

void Test_ObjWriter::writeFacePolygon_3()
{
    QVector<int> vertexIndPol;
    QVector<int> textureVertexIndPol;
    QVector<int> normalVertexIndPol;

    vertexIndPol.append(1);
    vertexIndPol.append(2);
    vertexIndPol.append(3);

    normalVertexIndPol.append(1);
    normalVertexIndPol.append(2);
    normalVertexIndPol.append(3);

    QString result = ObjWriter::writeFacePolygon(vertexIndPol, textureVertexIndPol, normalVertexIndPol);
    QCOMPARE(result, "2//2 3//3 4//4 ");
}

void Test_ObjWriter::writeFace()
{
    QVector<QVector<int>> m_polygonVertexIndices;
    QVector<int> vertexIndPol1;
    QVector<int> vertexIndPol2;
    QVector<int> vertexIndPol3;

    vertexIndPol1.append(1);
    vertexIndPol1.append(2);
    vertexIndPol1.append(3);
    m_polygonVertexIndices.append(vertexIndPol1);

    vertexIndPol2.append(1);
    vertexIndPol2.append(2);
    vertexIndPol2.append(3);
    m_polygonVertexIndices.append(vertexIndPol2);

    vertexIndPol3.append(1);
    vertexIndPol3.append(2);
    vertexIndPol3.append(3);
    m_polygonVertexIndices.append(vertexIndPol3);

    QString result = ObjWriter::writeFace(m_polygonVertexIndices, m_polygonVertexIndices, m_polygonVertexIndices, "f");
    QCOMPARE(result, "f 2/2/2 3/3/3 4/4/4 \nf 2/2/2 3/3/3 4/4/4 \nf 2/2/2 3/3/3 4/4/4 \n");

}

void Test_ObjWriter::writeFace_1()
{
    QVector<QVector<int>> m_polygonVertexIndices;
    QVector<QVector<int>> m_texturePolygonVertexIndices;
    QVector<int> vertexIndPol1;
    QVector<int> vertexIndPol2;
    QVector<int> vertexIndPol3;

    vertexIndPol1.append(1);
    vertexIndPol1.append(2);
    vertexIndPol1.append(3);
    m_polygonVertexIndices.append(vertexIndPol1);

    vertexIndPol2.append(1);
    vertexIndPol2.append(2);
    vertexIndPol2.append(3);
    m_polygonVertexIndices.append(vertexIndPol2);

    vertexIndPol3.append(1);
    vertexIndPol3.append(2);
    vertexIndPol3.append(3);
    m_polygonVertexIndices.append(vertexIndPol3);

    QString result = ObjWriter::writeFace(m_polygonVertexIndices, m_texturePolygonVertexIndices, m_polygonVertexIndices, "f");
    QCOMPARE(result, "f 2//2 3//3 4//4 \nf 2//2 3//3 4//4 \nf 2//2 3//3 4//4 \n");

}

void Test_ObjWriter::writeFace_2()
{
    QVector<QVector<int>> m_polygonVertexIndices;
    QVector<QVector<int>> m_normalPolygonVertexIndices;
    QVector<int> vertexIndPol1;
    QVector<int> vertexIndPol2;
    QVector<int> vertexIndPol3;

    vertexIndPol1.append(1);
    vertexIndPol1.append(2);
    vertexIndPol1.append(3);
    m_polygonVertexIndices.append(vertexIndPol1);

    vertexIndPol2.append(1);
    vertexIndPol2.append(2);
    vertexIndPol2.append(3);
    m_polygonVertexIndices.append(vertexIndPol2);

    vertexIndPol3.append(1);
    vertexIndPol3.append(2);
    vertexIndPol3.append(3);
    m_polygonVertexIndices.append(vertexIndPol3);

    QString result = ObjWriter::writeFace(m_polygonVertexIndices, m_polygonVertexIndices, m_normalPolygonVertexIndices, "f");
    QCOMPARE(result, "f 2/2 3/3 4/4 \nf 2/2 3/3 4/4 \nf 2/2 3/3 4/4 \n");

}

void Test_ObjWriter::writeFace_3()
{
    QVector<QVector<int>> m_polygonVertexIndices;
    QVector<QVector<int>> m_normalPolygonVertexIndices;
    QVector<QVector<int>> m_texturePolygonVertexIndices;
    QVector<int> vertexIndPol1;
    QVector<int> vertexIndPol2;
    QVector<int> vertexIndPol3;

    vertexIndPol1.append(1);
    vertexIndPol1.append(2);
    vertexIndPol1.append(3);
    m_polygonVertexIndices.append(vertexIndPol1);

    vertexIndPol2.append(1);
    vertexIndPol2.append(2);
    vertexIndPol2.append(3);
    m_polygonVertexIndices.append(vertexIndPol2);

    vertexIndPol3.append(1);
    vertexIndPol3.append(2);
    vertexIndPol3.append(3);
    m_polygonVertexIndices.append(vertexIndPol3);

    QString result = ObjWriter::writeFace(m_polygonVertexIndices, m_texturePolygonVertexIndices, m_normalPolygonVertexIndices, "f");
    QCOMPARE(result, "f 2 3 4 \nf 2 3 4 \nf 2 3 4 \n");

}

void Test_ObjWriter::convert3DVectorsToStringVectors()
{
    QVector<QVector3D> vertices;
    vertices.append(QVector3D(2, 5, 7));
    QVector<QString> temp = ObjWriter::convert3DVectorsToStringVectors(vertices);
    QString result = temp.at(0);
    QCOMPARE(result, "2 5 7");
}

void Test_ObjWriter::convert3DVectorsToStringVectors_1()
{
    QVector<QVector3D> vertices;
    vertices.append(QVector3D(2, 5, 7));
    vertices.append(QVector3D(2.0002, 75.01, 71));
    QVector<QString> temp = ObjWriter::convert3DVectorsToStringVectors(vertices);
    QString result1 = temp.at(0);
    QString result2 = temp.at(1);
    QCOMPARE(result1, "2 5 7");
    QCOMPARE(result2, "2.0002 75.01 71");
}

void Test_ObjWriter::convert2DVectorsToStringVectors()
{
    QVector<QVector2D> vertices;
    vertices.append(QVector2D(2, 5));
    QVector<QString> temp = ObjWriter::convert2DVectorsToStringVectors(vertices);
    QString result = temp.at(0);
    QCOMPARE(result, "2 5");
}

void Test_ObjWriter::convert2DVectorsToStringVectors_1()
{
    QVector<QVector2D> vertices;
    vertices.append(QVector2D(2, 5));
    vertices.append(QVector2D(2.0002, 75.01));
    QVector<QString> temp = ObjWriter::convert2DVectorsToStringVectors(vertices);
    QString result1 = temp.at(0);
    QString result2 = temp.at(1);
    QCOMPARE(result1, "2 5");
    QCOMPARE(result2, "2.0002 75.01");
}

void Test_ObjWriter::isPolygonReadyForRecording()
{
    QVector<int> vertexIndPol;

    vertexIndPol.append(1);
    vertexIndPol.append(2);
    vertexIndPol.append(3);

    Polygon polygon;
    polygon.addPoligonVertexIndices(vertexIndPol);

    bool result = ObjWriter::isPolygonReadyForRecording(polygon.getPoligonVertexIndices());
    QCOMPARE(result, true);

}

void Test_ObjWriter::isPolygonReadyForRecording_1()
{
    QVector<int> vertexIndPol;

    vertexIndPol.append(1);
    vertexIndPol.append(2);

    Polygon polygon;
    polygon.addPoligonVertexIndices(vertexIndPol);
    try {
        bool result = ObjWriter::isPolygonReadyForRecording(polygon.getPoligonVertexIndices());
    }  catch (ObjWriterException exp) {
        QCOMPARE(exp.getMessage(), "Error in the construction of a vector polygon.");
    }
}

void Test_ObjWriter::isPolygonReadyForRecording_2()
{
    QVector<int> vertexIndPol;

    vertexIndPol.append(1);
    vertexIndPol.append(2);
    vertexIndPol.append(-3);

    Polygon polygon;
    polygon.addPoligonVertexIndices(vertexIndPol);
    try {
        bool result = ObjWriter::isPolygonReadyForRecording(polygon.getPoligonVertexIndices());
    }  catch (ObjWriterException exp) {
        QCOMPARE(exp.getMessage(), "Data entered incorrectly.");
    }
}

void Test_ObjWriter::isPolygonReadyForRecording_3()
{
    QVector<int> vertexIndPol;

    vertexIndPol.append(1);
    vertexIndPol.append(2);
    vertexIndPol.append(-3);

    QVector<int> vertexIndPol1;

    vertexIndPol1.append(1);
    vertexIndPol1.append(2);
    vertexIndPol1.append(3);

    Polygon polygon;
     polygon.addPoligonVertexIndices(vertexIndPol1);
    polygon.addPoligonVertexIndices(vertexIndPol);
    try {
        bool result = ObjWriter::isPolygonReadyForRecording(polygon.getPoligonVertexIndices());
    }  catch (ObjWriterException exp) {
        QCOMPARE(exp.getMessage(), "Data entered incorrectly.");
        QCOMPARE(exp.line(), 2);
    }
}
