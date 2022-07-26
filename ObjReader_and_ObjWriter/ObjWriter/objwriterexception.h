#ifndef OBJWRITEREXCEPTION_H
#define OBJWRITEREXCEPTION_H

#include <iostream>
#include <QString>

class ObjWriterException: public std::exception
{
private:
    QString m_error;
    int lineInd;

public:
    ObjWriterException(QString message, int newLineInd);

    const char* what() const noexcept;
    QString getMessage();
    int line();
};

#endif // OBJWRITEREXCEPTION_H
