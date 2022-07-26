#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "viewport.h"
#include "progressnotifier.h"
#include "drawablemesh.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Viewport *viewport, QWidget *parent = nullptr);
    ~MainWindow() override;
    QSize sizeHint() const override;
protected:
    DrawableMesh *m_drawableMesh = nullptr;
    Camera *m_camera = nullptr;
    Viewport *m_viewport = nullptr;
    AbstractProgressNotifier *m_progressNotifier = nullptr;

    QVector3D colourVector;
    bool normalMapOn = false;
protected slots:
    void loadMesh();
    void loadColour();
};

#endif // MAINWINDOW_H
