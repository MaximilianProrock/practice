#ifndef TEST_OBJREADER_H
#define TEST_OBJREADER_H

#include <QObject>

class Test_ObjReader: public QObject
{
    Q_OBJECT
public:
    Test_ObjReader(QObject *parent = 0);

private slots:
    void parseVector3D();
    void parseVector3D_1();
    void parseVector3D_2();
    void parseVector3D_3();
    void parseVector3D_4();
    void parseVector3D_5();

    void parseVector2D();
    void parseVector2D_1();
    void parseVector2D_2();
    void parseVector2D_3();
    void parseVector2D_4();
    void parseVector2D_5();

    void parseFace();
    void parseFace_1();
    void parseFace_2();
    void parseFace_3();
    void parseFace_4();
    void parseFace_5();
};

#endif // TEST_OBJREADER_H
