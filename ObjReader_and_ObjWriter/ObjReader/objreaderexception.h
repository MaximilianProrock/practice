#ifndef OBJREADEREXCEPTION_H
#define OBJREADEREXCEPTION_H

#include <exception>
#include <QString>


class ObjReaderException: public std::exception
{
private:
    QString m_error;
    int lineInd;
public:
    ObjReaderException(QString message, int newLineInd);

    const char* what() const noexcept;
    QString getMessage();
    int line();
};

#endif // OBJREADEREXCEPTION_H
