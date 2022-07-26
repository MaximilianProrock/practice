!DRAWABLE_GRID_PRI {

CONFIG += DRAWABLE_GRID_PRI

INCLUDEPATH += $$PWD

include($$PWD/../DrawableObject/DrawableObject.pri)

HEADERS += \
    $$PWD/drawablegrid.h

SOURCES += \
    $$PWD/drawablegrid.cpp

}
