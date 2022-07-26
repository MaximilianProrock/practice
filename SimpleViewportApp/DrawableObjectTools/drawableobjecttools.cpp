#include "drawableobjecttools.h"

QOpenGLShaderProgram *DrawableObjectTools::createShaderProgram(QString vertexShaderFileName, QString fragmentShaderFileName)
{
    QOpenGLShaderProgram *shader = new QOpenGLShaderProgram();
    if (!shader->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShaderFileName)) {
        delete shader;
        return nullptr;
    }
    if (!shader->addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShaderFileName)) {
        delete shader;
        return nullptr;
    }
    if (!shader->link()) {
        delete shader;
        return nullptr;
    }
    return shader;
}
