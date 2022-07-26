#include "test_objreader.h"
#include "objreader.h"
#include "objreaderexception.h"
#include "polygon.h"

#include <iostream>
using namespace std;

#include <QTest>

Test_ObjReader::Test_ObjReader(QObject *parent):
    QObject(parent)
{
}

void Test_ObjReader::parseVector3D()
{
    QString str = "1 2 3 \n";
    QVector3D vector = ObjReader::parseVector3D(str, 0);
    QCOMPARE(vector.x(), 1);
    QCOMPARE(vector.y(), 2);
    QCOMPARE(vector.z(), 3);
}

void Test_ObjReader::parseVector3D_1()
{
    QString str = "1 2 3\n";
    QVector3D vector = ObjReader::parseVector3D(str, 0);
    QCOMPARE(vector.x(), 1);
    QCOMPARE(vector.y(), 2);
    QCOMPARE(vector.z(), 3);
}

void Test_ObjReader::parseVector3D_2()
{
    QString str = "1             2    3\n";
    QVector3D vector = ObjReader::parseVector3D(str, 0);
    QCOMPARE(vector.x(), 1);
    QCOMPARE(vector.y(), 2);
    QCOMPARE(vector.z(), 3);
}

void Test_ObjReader::parseVector3D_3()
{
    QString str = "1.0002 2.45 34.23\n";
    QVector3D vector = ObjReader::parseVector3D(str, 0);
    QCOMPARE(vector.x(), 1.0002f);
    QCOMPARE(vector.y(), 2.45f);
    QCOMPARE(vector.z(), 34.23f);
}

void Test_ObjReader::parseVector3D_4()
{
    QString str = "1.0002 2.45\n";
    try {
        QVector3D vector = ObjReader::parseVector3D(str, 0);
    }  catch (ObjReaderException exp) {
        QCOMPARE(exp.getMessage(), "Too few vertex arguments.");
        QCOMPARE(exp.line(), 0);
    }
}

void Test_ObjReader::parseVector3D_5()
{
    QString str = "1.0002 2.45 \n";
    try {
        QVector3D vector = ObjReader::parseVector3D(str, 0);
    }  catch (ObjReaderException exp) {
        QString msg = exp.what();
        QCOMPARE(exp.getMessage(), "Too few vertex arguments.");
        QCOMPARE(exp.line(), 0);
    }
}



void Test_ObjReader::parseVector2D()
{
    QString str = "1 2 \n";
    QVector2D vector = ObjReader::parseVector2D(str, 0);
    QCOMPARE(vector.x(), 1);
    QCOMPARE(vector.y(), 2);
}

void Test_ObjReader::parseVector2D_1()
{
    QString str = "1 2\n";
    QVector2D vector = ObjReader::parseVector2D(str, 0);
    QCOMPARE(vector.x(), 1);
    QCOMPARE(vector.y(), 2);
}

void Test_ObjReader::parseVector2D_2()
{
    QString str = "         1                2       \n";
    QVector2D vector = ObjReader::parseVector2D(str, 0);
    QCOMPARE(vector.x(), 1);
    QCOMPARE(vector.y(), 2);
}

void Test_ObjReader::parseVector2D_3()
{
    QString str = "1.0002 2.45\n";
    QVector2D vector = ObjReader::parseVector2D(str, 0);
    QCOMPARE(vector.x(), 1.0002f);
    QCOMPARE(vector.y(), 2.45f);
}

void Test_ObjReader::parseVector2D_4()
{
    QString str = "1.0002\n";
    try {
        QVector2D vector = ObjReader::parseVector2D(str, 0);
    }  catch (ObjReaderException exp) {
        QCOMPARE(exp.getMessage(), "Too few texture vertex arguments.");
        QCOMPARE(exp.line(), 0);
    }
}

void Test_ObjReader::parseVector2D_5()
{
    QString str = "1.0002 \n";
    try {
        QVector2D vector = ObjReader::parseVector2D(str, 0);
    }  catch (ObjReaderException exp) {
        QCOMPARE(exp.getMessage(), "Too few texture vertex arguments.");
        QCOMPARE(exp.line(), 0);
    }
}
void Test_ObjReader::parseFace()
{
    QString str = "1 2 3 \n";
    Polygon polygon = ObjReader::parseFace(str, 0);
    QCOMPARE(polygon.getPoligonVertexIndices().at(0).at(0), 0);
    QCOMPARE(polygon.getPoligonVertexIndices().at(0).at(1), 1);
    QCOMPARE(polygon.getPoligonVertexIndices().at(0).at(2), 2);
}

void Test_ObjReader::parseFace_1()
{
    QString str = "1/1 2/2 3/3 \n";
    Polygon polygon = ObjReader::parseFace(str, 0);
    QCOMPARE(polygon.getPoligonVertexIndices().at(0).at(0), 0);
    QCOMPARE(polygon.getPoligonVertexIndices().at(0).at(1), 1);
    QCOMPARE(polygon.getPoligonVertexIndices().at(0).at(2), 2);

    QCOMPARE(polygon.getPoligonTextureVertexIndices().at(0).at(0), 0);
    QCOMPARE(polygon.getPoligonTextureVertexIndices().at(0).at(1), 1);
    QCOMPARE(polygon.getPoligonTextureVertexIndices().at(0).at(2), 2);
}

void Test_ObjReader::parseFace_2()
{
    QString str = "1//1 2//2 3//3 \n";
    Polygon polygon = ObjReader::parseFace(str, 0);
    QCOMPARE(polygon.getPoligonVertexIndices().at(0).at(0), 0);
    QCOMPARE(polygon.getPoligonVertexIndices().at(0).at(1), 1);
    QCOMPARE(polygon.getPoligonVertexIndices().at(0).at(2), 2);

    QCOMPARE(polygon.getPoligonNormalVertexIndices().at(0).at(0), 0);
    QCOMPARE(polygon.getPoligonNormalVertexIndices().at(0).at(1), 1);
    QCOMPARE(polygon.getPoligonNormalVertexIndices().at(0).at(2), 2);
}

void Test_ObjReader::parseFace_3()
{
    QString str = "1/1/1 2/2/2 3/3/3 \n";
    Polygon polygon = ObjReader::parseFace(str, 0);
    QCOMPARE(polygon.getPoligonVertexIndices().at(0).at(0), 0);
    QCOMPARE(polygon.getPoligonVertexIndices().at(0).at(1), 1);
    QCOMPARE(polygon.getPoligonVertexIndices().at(0).at(2), 2);

    QCOMPARE(polygon.getPoligonTextureVertexIndices().at(0).at(0), 0);
    QCOMPARE(polygon.getPoligonTextureVertexIndices().at(0).at(1), 1);
    QCOMPARE(polygon.getPoligonTextureVertexIndices().at(0).at(2), 2);

    QCOMPARE(polygon.getPoligonNormalVertexIndices().at(0).at(0), 0);
    QCOMPARE(polygon.getPoligonNormalVertexIndices().at(0).at(1), 1);
    QCOMPARE(polygon.getPoligonNormalVertexIndices().at(0).at(2), 2);
}

void Test_ObjReader::parseFace_4()
{
    QString str = "1.0002\n";
    try {
        Polygon polygon = ObjReader::parseFace(str, 0);
    }  catch (ObjReaderException exp) {
        QCOMPARE(exp.getMessage(), "Too few arguments.");
        QCOMPARE(exp.line(), 0);
    }
}

void Test_ObjReader::parseFace_5()
{
    QString str = "1.0002/15.45/48/75 1.0002/15.45/48/75 1.0002/15.45/48/75\n";
    try {
        Polygon polygon = ObjReader::parseFace(str, 0);
    }  catch (ObjReaderException exp) {
        QCOMPARE(exp.getMessage(), "Invalid element size.");
        QCOMPARE(exp.line(), 0);
    }
}
