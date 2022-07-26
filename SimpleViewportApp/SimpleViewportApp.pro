QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

include(../ObjReaderAfter/ObjReader/ObjReader.pri)
include(../ObjReaderAfter/MeshTools/MeshTools.pri)
include(DrawableMesh/DrawableMesh.pri)
include(DrawableGrid/DrawableGrid.pri)
include(Viewport/Viewport.pri)

SOURCES += \
    colourselectionwindow.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    colourselectionwindow.h \
    mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    colourselectionwindow.ui
