#include "objwriter.h"
#include <QString>
#include <QFile>
#include <fstream>
#include <iostream>

#include <objwriterexception.h>

using namespace std;

ObjWriter::ObjWriter()
{

}

void ObjWriter::write(Model model, QString fileName)
{
    QFile file(fileName);
    file.open(QFile::WriteOnly);

    if(!file.isOpen())
        throw ObjWriterException("The file cannot be opened.", -1);

    try {
        isModelReadyForRecording(model);

        QVector<QString> verStr = ObjWriter::convert3DVectorsToStringVectors(model.getVerices());;
        QVector<QString> texStr = ObjWriter::convert2DVectorsToStringVectors(model.getTexureVerices());
        QVector<QString> normStr = ObjWriter::convert3DVectorsToStringVectors(model.getNormalVerices());;

        file.write(writeVertices(verStr, "v").toStdString().c_str());
        file.flush();
        file.write(writeVertices(texStr, "vt").toStdString().c_str());
        file.flush();
        file.write(writeVertices(normStr, "vn").toStdString().c_str());
        file.flush();
        file.write(writeFace(model.getPoligonVertexIndices(),
                             model.getPoligonTextureVertexIndices(),
                             model.getPoligonNormalVertexIndices(),
                             "f").toStdString().c_str()
                   );
        file.flush();
    }  catch (ObjWriterException exp) {
        throw ObjWriterException(exp.getMessage(), exp.line());
    }
}

QString ObjWriter::writeVertices(QVector<QString> vertices, QString token)
{
    QString result = "";
    for(int i = 0; i < vertices.size(); i++)
    {
        result.append(token).append(" ").append(vertices.at(i)).append("\n");
    }
    return result;
}

QVector<QString> ObjWriter::convert3DVectorsToStringVectors(QVector<QVector3D> vertices)
{
    QVector<QString> verStr;
    for(int i = 0; i < vertices.size(); i++)
    {
        verStr.append(QString("%1 %2 %3").arg(QString::number(vertices.at(i).x()),
                                              QString::number(vertices.at(i).y()),
                                              QString::number(vertices.at(i).z())
                                              ));
    }
    return verStr;
}

QVector<QString> ObjWriter::convert2DVectorsToStringVectors(QVector<QVector2D> vertices)
{
    QVector<QString> verStr;
    for(int i = 0; i < vertices.size(); i++)
    {
        verStr.append(QString("%1 %2").arg(QString::number(vertices.at(i).x()),
                                              QString::number(vertices.at(i).y())
                                              ));
    }
    return verStr;
}



QString ObjWriter::writeFace(QVector<QVector<int> > m_polygonVertexIndices,
                             QVector<QVector<int> > m_polygonTextureVertexIndices,
                             QVector<QVector<int> > m_polygonNormalVertexIndices,
                             QString token)
{
    QString result = "";

    if(m_polygonTextureVertexIndices.isEmpty() && m_polygonNormalVertexIndices.isEmpty()){
        for(int i = 0; i < m_polygonVertexIndices.size(); i++){
            result.append(token).append(" ");
            result.append(writeFacePolygonWithoutTexturesAndNormals(m_polygonVertexIndices.at(i)));
            result.append("\n");

        }
    }else if (m_polygonTextureVertexIndices.isEmpty()) {
        for(int i = 0; i < m_polygonVertexIndices.size(); i++){
            result.append(token).append(" ");
            result.append(writeFacePolygonWithoutTextures(m_polygonVertexIndices.at(i), m_polygonNormalVertexIndices.at(i)));
            result.append("\n");

        }
    }else if(m_polygonNormalVertexIndices.isEmpty()){
        for(int i = 0; i < m_polygonVertexIndices.size(); i++){
            result.append(token).append(" ");
            result.append(writeFacePolygonWithoutNormals(m_polygonVertexIndices.at(i), m_polygonTextureVertexIndices.at(i)));
            result.append("\n");

        }
    }else {
        for(int i = 0; i < m_polygonVertexIndices.size(); i++){
            result.append(token).append(" ");
            result.append(writeFacePolygon(m_polygonVertexIndices.at(i), m_polygonTextureVertexIndices.at(i), m_polygonNormalVertexIndices.at(i)));
            result.append("\n");

        }
    }

    return result;
}

QString ObjWriter::writeFacePolygon(QVector<int> vertexIndPol, QVector<int> textureVertexIndPol, QVector<int> normalVertexIndPol)
{
    QString result = "";

    for(int j = 0; j < vertexIndPol.size(); j++)
    {
        result.append(QString::number(vertexIndPol.at(j) + 1));//счет идет с 1, а не с 0
        if(textureVertexIndPol.isEmpty() && normalVertexIndPol.isEmpty())
        {
            result.append(" ");
            continue;
        }
        result.append("/");
        if(!textureVertexIndPol.isEmpty()){
            result.append(QString::number(textureVertexIndPol.at(j) + 1)); //счет идет с 1, а не с 0
        }

        if(!normalVertexIndPol.isEmpty()){
            result.append("/");
            result.append(QString::number(normalVertexIndPol.at(j) + 1));//счет идет с 1, а не с 0
        }
        result.append(" ");
    }

    return result;
}

QString ObjWriter::writeFacePolygonWithoutTextures(QVector<int> vertexIndPol, QVector<int> normalVertexIndPol)
{
    QString result = "";

    for(int j = 0; j < vertexIndPol.size(); j++)
    {
        result.append(QString::number(vertexIndPol.at(j) + 1));//счет идет с 1, а не с 0
        if(normalVertexIndPol.isEmpty())
        {
            result.append(" ");
            continue;
        }
        result.append("//");
        result.append(QString::number(normalVertexIndPol.at(j) + 1));//счет идет с 1, а не с 0
        result.append(" ");
    }

    return result;
}

QString ObjWriter::writeFacePolygonWithoutNormals(QVector<int> vertexIndPol, QVector<int> textureVertexIndPol)
{
    QString result = "";

    for(int j = 0; j < vertexIndPol.size(); j++)
    {
        result.append(QString::number(vertexIndPol.at(j) + 1));//счет идет с 1, а не с 0
        if(textureVertexIndPol.isEmpty())
        {
            result.append(" ");
            continue;
        }
        result.append("/");
        result.append(QString::number(textureVertexIndPol.at(j) + 1)); //счет идет с 1, а не с 0
        result.append(" ");
    }

    return result;
}

QString ObjWriter::writeFacePolygonWithoutTexturesAndNormals(QVector<int> vertexIndPol)
{
    QString result = "";

    for(int j = 0; j < vertexIndPol.size(); j++)
    {
        result.append(QString::number(vertexIndPol.at(j) + 1));//счет идет с 1, а не с 0
        result.append(" ");
    }

    return result;
}

bool ObjWriter::isModelReadyForRecording(Model model)
{
    try {
        //bool position1 = isPolygonReadyForRecording(model.getPoligonVertexIndices());
        //bool position2 = isPolygonReadyForRecording(model.getPoligonTextureVertexIndices());
        bool position3 = isPolygonReadyForRecording(model.getPoligonNormalVertexIndices());
        return true;
    }  catch (ObjWriterException exp) {
        throw ObjWriterException(exp.getMessage(), exp.line());
    };

}

bool ObjWriter::isPolygonReadyForRecording(QVector<QVector<int> > polygon)
{
    for(int lineInd = 0; lineInd < polygon.size(); lineInd++){
        if(polygon.at(lineInd).size() < 3 && polygon.at(lineInd).size() != 0){
            throw ObjWriterException("Error in the construction of a vector polygon.", lineInd + 1);
        }
        for(int j = 0; j < polygon.at(lineInd).size(); j++){
            if(polygon.at(lineInd).at(j) < 0){
                throw ObjWriterException("Data entered incorrectly.", lineInd + 1);
            }
        }
    }
    return true;
}




