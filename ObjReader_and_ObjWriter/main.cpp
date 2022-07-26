#include "mainwindow.h"

#include <QApplication>
#include <model.h>
#include <objwriter.h>
#include <objreader.h>
#include <QVector2D>

#include <iostream>
using namespace std;
#include <QTest>
#include "test_objwriter.h"
#include "test_objreader.h"

using namespace std;

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();

    freopen("testing.log", "w", stdout);
    QApplication a(argc, argv);
    QTest::qExec(new Test_ObjWriter, argc, argv);
    QTest::qExec(new Test_ObjReader, argc, argv);


    Model model = ObjReader::read("C:\\2_kurs_proga\\practis\\far_teapot.obj");
//    model.addVerices(QVector3D(1, 2, 3));
//    model.addVerices(QVector3D(11.4862, 2, 33));
//    model.addVerices(QVector3D(1.4549, 21.45f, 3));
//    model.addVerices(QVector3D(21, 21.02, 3.0f));

//    model.addTexureVerices(QVector2D(1, 2));
//    model.addTexureVerices(QVector2D(11.4862, 2));
//    model.addTexureVerices(QVector2D(1.4549, 21.45f));
//    model.addTexureVerices(QVector2D(21, 21.02));

//    model.addNormalVerices(QVector3D(1, 2, 3));
//    model.addNormalVerices(QVector3D(11.4862, 2, 33));
//    model.addNormalVerices(QVector3D(1.4549, 21.45f, 3));
//    model.addNormalVerices(QVector3D(21, 21.02, 3.0f));

    ObjWriter::write(model, "C:\\2_kurs_proga\\practis\\Test1.obj");

    return 0;
}
