#ifndef TEST_OBJWRITER_H
#define TEST_OBJWRITER_H

#include <QObject>

class Test_ObjWriter:public QObject
{
    Q_OBJECT
public:
    explicit Test_ObjWriter(QObject *parent = 0);
private slots:
    void writeVertices();
    void writeVertices_1();
    void writeVertices_2();
    void writeTestureVertices();
    void writeNormalVertices();

    void writeFacePolygon();
    void writeFacePolygon_1();
    void writeFacePolygon_2();
    void writeFacePolygon_3();

    void writeFace();
    void writeFace_1();
    void writeFace_2();
    void writeFace_3();

    void convert3DVectorsToStringVectors();
    void convert3DVectorsToStringVectors_1();

    void convert2DVectorsToStringVectors();
    void convert2DVectorsToStringVectors_1();

    void isPolygonReadyForRecording();
    void isPolygonReadyForRecording_1();
    void isPolygonReadyForRecording_2();
    void isPolygonReadyForRecording_3();

};

#endif // TEST_OBJWRITER_H
