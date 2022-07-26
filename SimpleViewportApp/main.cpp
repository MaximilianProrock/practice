#include "mainwindow.h"

#include <QApplication>
#include <QProgressBar>
#include <QOpenGLContext>
#include <QOffscreenSurface>
#include "objreader.h"
#include "visualprogressnotifier.h"
#include "drawablegrid.h"

void test()
{
    ObjReadingTools::ObjData objData;
    QString errorMsg;

    QProgressBar progressBar2;
    VisualProgressNotifier progressNotifier2(&progressBar2);
    QString objFileText2 = "v 1 2 3";
    QTextStream textStream2(&objFileText2);
    ObjReadingTools::read(textStream2, objData, errorMsg, &progressNotifier2);

    QProgressBar progressBar;
    VisualProgressNotifier progressNotifier(&progressBar);
    QString objFileText = "v 1 2";
    QTextStream textStream(&objFileText);
    ObjReadingTools::read(textStream, objData, errorMsg, &progressNotifier);
}

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QApplication a(argc, argv);

    test();

    QOpenGLContext *globalContext = QOpenGLContext::globalShareContext();
    Q_ASSERT(globalContext);
    QOffscreenSurface *surface = new QOffscreenSurface();
    surface->create();
    QOpenGLContext *glContext = new QOpenGLContext();
    glContext->setShareContext(globalContext);
    if (!glContext->create())
        qFatal("Can\'t create OpenGL context");

    glContext->makeCurrent(surface);
    DrawableGrid grid(1, 10, Qt::gray);

    Camera m_camera;
    Viewport m_viewport(&m_camera);
    m_viewport.addObject(&grid);

    MainWindow w(&m_viewport);
    w.show();
    int res = a.exec();
    m_viewport.setParent(nullptr);
    return res;
}
