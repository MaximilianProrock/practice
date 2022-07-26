#ifndef DRAWABLEOBJECTTOOLS_H
#define DRAWABLEOBJECTTOOLS_H

#include <QOpenGLShaderProgram>

namespace DrawableObjectTools {

QOpenGLShaderProgram *createShaderProgram(QString vertexShaderFileName, QString fragmentShaderFileName);

}

#endif // DRAWABLEOBJECTTOOLS_H

