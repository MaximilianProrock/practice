#include "objwriterexception.h"

ObjWriterException::ObjWriterException(QString message, int newLineInd)
{
    m_error = message;
    lineInd = newLineInd;
}

const char *ObjWriterException::what() const noexcept
{
    return m_error.toStdString().c_str();
}

QString ObjWriterException::getMessage()
{
    return m_error;
}

int ObjWriterException::line()
{
    return lineInd;
}
