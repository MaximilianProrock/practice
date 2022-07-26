#include "objreaderexception.h"

ObjReaderException::ObjReaderException(QString message, int newLineInd)
{
    m_error = message;
    lineInd = newLineInd;
}

const char *ObjReaderException::what() const noexcept
{
    return m_error.toStdString().c_str();
}

QString ObjReaderException::getMessage()
{
    return m_error;
}

int ObjReaderException::line()
{
    return lineInd;
}
