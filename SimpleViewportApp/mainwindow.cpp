#include "mainwindow.h"
#include "objreader.h"
#include "meshtools.h"
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressBar>
#include <QStatusBar>
#include "visualprogressnotifier.h"
#include "consoleprogressnotifier.h"
#include "colourselectionwindow.h"

MainWindow::MainWindow(Viewport *viewport, QWidget *parent)
    : QMainWindow(parent),
      m_viewport(viewport)
{
    setCentralWidget(m_viewport);

    colourVector.setX(1);
    colourVector.setY(0);
    colourVector.setZ(0);

    QMenu *fileMenu = new QMenu("File");
    fileMenu->addAction("Load mesh", this, &MainWindow::loadMesh, QKeySequence::Open);

    QMenu *colourMenu = new QMenu("Colour");
    colourMenu->addAction("Load colour for mesh", this, &MainWindow::loadColour, QKeySequence::Open);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(colourMenu);

    QProgressBar *progressBar = new QProgressBar();
    statusBar()->addPermanentWidget(progressBar);
    progressBar->hide();
    m_progressNotifier = new VisualProgressNotifier(progressBar);
    //m_progressNotifier = new ConsoleProgressNotifier();
}

MainWindow::~MainWindow()
{
    delete m_progressNotifier;
}

QSize MainWindow::sizeHint() const
{
    return QSize(1024, 768);
}

void MainWindow::loadMesh()
{
    //QString fileName = "../ObjReaderAfter/Teapot.obj";
    QString fileName = QFileDialog::getOpenFileName(this, "Select a mesh", "../ObjReaderAfter", "OBJ file (*.obj)");
    if (fileName.isEmpty())
        return;
    ObjReadingTools::ObjData objData;
    QString errorMsg;
    if (!ObjReadingTools::read(fileName, objData, errorMsg, m_progressNotifier)) {
        QMessageBox::warning(this, "Failed to load mesh", errorMsg);
        return;
    }
    bool hasNormals = !objData.m_normals.isEmpty() && !objData.m_polygonNormalIndices.isEmpty();
    if (!hasNormals) {
        QMessageBox::warning(this, "Can\'t use this mesh", "The mesh doesn\'t contain normals");
        return;
    }
    QVector<int> polygonVertexIndices = MeshTools::buildPolygonVertexIndicesVector(objData.m_polygonVertexIndices);
    QVector<int> polygonNormalIndices = MeshTools::buildPolygonVertexIndicesVector(objData.m_polygonNormalIndices);
    QVector<int> polygonStart = MeshTools::buildPolygonStartVector(objData.m_polygonVertexIndices);
    m_viewport->makeCurrent();
    m_viewport->setCameraCordinates(Viewport::fitToView(objData.m_vertices));
    if (m_drawableMesh) {
        m_viewport->removeObject(m_drawableMesh);
        delete m_drawableMesh;
    }
    m_drawableMesh = new DrawableMesh(objData.m_vertices, polygonVertexIndices, polygonStart, objData.m_normals, polygonNormalIndices, colourVector, normalMapOn);
    //m_viewport->setRotationAngles(QVector3D(90, 0, 0));
    m_viewport->addObject(m_drawableMesh);
    m_viewport->update();
}

void MainWindow::loadColour()
{
    ColourSelectionWindow csw;
    csw.setModal(true);
    csw.exec();
    normalMapOn = csw.getStateOfNormalMap();
    colourVector = csw.getColourVector();

    if(m_drawableMesh != nullptr){
        m_drawableMesh->setColour(colourVector);
        m_drawableMesh->enableNormalMap(normalMapOn);
        m_viewport->addObject(m_drawableMesh);
        m_viewport->update();
    }
}
