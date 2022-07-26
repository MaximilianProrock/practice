!DRAWABLE_MESH_PRI {

CONFIG += DRAWABLE_MESH_PRI

INCLUDEPATH += $$PWD

include($$PWD/../DrawableObject/DrawableObject.pri)
include($$PWD/../DrawableObjectTools/DrawableObjectTools.pri)

HEADERS += \
    $$PWD/drawablemesh.h

SOURCES += \
    $$PWD/drawablemesh.cpp

DISTFILES += \
    $$PWD/FragmentShader.frag \
    $$PWD/VertexShader.vert

RESOURCES += \
    $$PWD/DrawableMesh.qrc

}

