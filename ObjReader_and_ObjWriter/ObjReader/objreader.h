#ifndef OBJREADER_H
#define OBJREADER_H

#include <QString>
#include <QTextStream>
#include <QFile>
#include <polygon.h>
#include <model.h>

class ObjReader
{
public:
    static Model read(QString fileName);
    static QVector3D parseVector3D(QString body, int lineInd);
    static QVector2D parseVector2D(QString body, int lineInd);
    static Polygon parseFace(QString body, int lineInd);

protected:
    ObjReader();
private:
    static bool isNumber(QString str);
};

#endif // OBJREADER_H
