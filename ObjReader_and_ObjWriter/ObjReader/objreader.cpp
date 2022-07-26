#include "objreader.h"
#include "objreader.h"
#include "objreaderexception.h"
#include <model.h>

#include <iostream>

using namespace std;

ObjReader::ObjReader()
{

}



Model ObjReader::read(QString fileName)
{
    QFile file(fileName);
    file.open(QFile::ReadOnly| QIODevice::Text);

    if(!file.isOpen())
        throw ObjReaderException("The file cannot be opened.", -1);

    QTextStream stream(&file);

    Model model;
    int lineInd = 0;

    while (!stream.atEnd()) {
        QString line = stream.readLine();
        int firstSpaseInd = line.indexOf(" ");
        if((firstSpaseInd == -1) || (firstSpaseInd == 0)){
            continue;
        }
        QString token = line.left(firstSpaseInd);
        QString body = line.mid(firstSpaseInd + 1);

        lineInd++;

        if(token == "v"){
            model.addVerices(parseVector3D(body, lineInd));
        } else if(token == "vt"){
            model.addTexureVerices(parseVector2D(body, lineInd));
        } else if(token == "vn"){
            model.addNormalVerices(parseVector3D(body,lineInd));
        } else if(token == "f"){
            Polygon polygon = parseFace(body, lineInd);
            model.addPoligonVertexIndices(polygon.getPoligonVertexIndices().last());
            model.addPoligonTextureVertexIndices(polygon.getPoligonTextureVertexIndices().last());
            model.addPoligonNormalVertexIndices(polygon.getPoligonNormalVertexIndices().last());
        }
    }
    return model;
}

QVector3D ObjReader::parseVector3D(QString body, int lineInd)
{
    body.remove("\n");
    QStringList blocks = body.split(" ", QString::SkipEmptyParts);

    if(blocks.size() < 3){
        throw ObjReaderException("Too few vertex arguments.", lineInd);
    }

//    if(!isNumber(blocks[0]) || !isNumber(blocks[1]) || !isNumber(blocks[2])){
//        throw ObjReaderException("Failed to parse float value.", lineInd);
//    }

    try {
        return QVector3D(blocks[0].toFloat(), blocks[1].toFloat(), blocks[2].toFloat());
    }  catch (const exception &e) {
        throw ObjReaderException(e.what(), lineInd);
    }
}

QVector2D ObjReader::parseVector2D(QString body, int lineInd)
{
    body.remove("\n");
    QStringList blocks = body.split(" ", QString::SkipEmptyParts);
    if(blocks.size() < 2){
        throw ObjReaderException("Too few texture vertex arguments.", lineInd);
    }

//    if(!isNumber(blocks[0]) || !isNumber(blocks[1])){
//        throw ObjReaderException("Failed to parse float value.", lineInd);
//    }

    try {
        return QVector2D(blocks[0].toFloat(), blocks[1].toFloat());
    }  catch (const exception &e) {
        throw ObjReaderException(e.what(), lineInd);
    }
}

Polygon ObjReader::parseFace(QString body, int lineInd)
{
    Polygon polygon;
    body.remove("\n");
    QStringList blocks = body.split(" ", QString::SkipEmptyParts);

    if(blocks.size() < 2){
        throw ObjReaderException("Too few arguments.", lineInd);
    }

    int nVertices = blocks.size();

    QVector<int> vertexInd;
    QVector<int> texVerInd;
    QVector<int> normVerInd;

    for(int i = 0; i < nVertices; i++){
//        QString block = blocks[i];
//        int firstSlashInd = block.indexOf("/");
//        if(firstSlashInd == -1){
//            vertexInd.append(block.toInt() - 1);
//            continue;
//        } else{
//            vertexInd.append(block.left(firstSlashInd).toInt() - 1);
//            QString otherPartOfBlock = block.mid(firstSlashInd + 1);

//            int secoundSlashInd = otherPartOfBlock.indexOf("/");
//            if(secoundSlashInd == -1){
//                texVerInd.append(otherPartOfBlock.toInt() - 1);
//                continue;
//            }
//            if(secoundSlashInd == 0){
//                normVerInd.append(otherPartOfBlock.mid(secoundSlashInd + 1).toInt() - 1);
//                continue;
//            }else {
//                texVerInd.append(otherPartOfBlock.left(secoundSlashInd).toInt() - 1);
//                normVerInd.append(otherPartOfBlock.mid(secoundSlashInd + 1).toInt() - 1);
//            }

//        }
        QStringList polygonBlocks = blocks[i].split("/");
        switch (polygonBlocks.size()) {
        case 1:
            vertexInd.append(polygonBlocks[0].toInt() - 1);
            break;
        case 2:
            vertexInd.append(polygonBlocks[0].toInt() - 1);
            if(body.indexOf("//") == -1){
                texVerInd.append(polygonBlocks[1].toInt() - 1);
            }else {
                normVerInd.append(polygonBlocks[1].toInt() - 1);
            }
            break;
        case 3:
            vertexInd.append(polygonBlocks[0].toInt() - 1);
            texVerInd.append(polygonBlocks[1].toInt() - 1);
            normVerInd.append(polygonBlocks[2].toInt() - 1);
            break;
        default:
            throw ObjReaderException("Invalid element size.", 0);
            break;
        }
    }

    polygon.addPoligonVertexIndices(vertexInd);
    polygon.addPoligonTextureVertexIndices(texVerInd);
    polygon.addPoligonNormalVertexIndices(normVerInd);
    return polygon;
}


bool ObjReader::isNumber(QString str)
{
    string s = str.toStdString();
    std::size_t char_pos(0);

    // skip the whilespaces
    char_pos = s.find_first_not_of(' ');
    if (char_pos == s.size()) return false;


    // check the significand
    if (s[char_pos] == '+' || s[char_pos] == '-') ++char_pos; // skip the sign if exist

    int n_nm, n_pt;
    for (n_nm = 0, n_pt = 0; std::isdigit(s[char_pos]) || s[char_pos] == '.'; ++char_pos) {
        s[char_pos] == '.' ? ++n_pt : ++n_nm;
    }
    if (n_pt>1 || n_nm<1) // no more than one point, at least one digit
        return false;

    // skip the trailing whitespaces
    while (s[char_pos] == ' ') {
        ++ char_pos;
    }

    return char_pos == s.size();  // must reach the ending 0 of the string
}
