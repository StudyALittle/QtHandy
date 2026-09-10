#include "qhloggermessage.h"

QhLoggerMessage::QhLoggerMessage()
{
    dateTime = QDateTime::currentDateTime();
}

QhLoggerMessage::QhLoggerMessage(
    QhLoggerLevel level, const QString &file, const QString &funcname, int line, const QString &content) :
    level(level), file(file), funcname(funcname), line(line), content(content)
{
    dateTime = QDateTime::currentDateTime();
}

QhLoggerMessage::~QhLoggerMessage()
{
}

bool QhLoggerMessage::isForceNewFile() const
{
    return bForceNewFile;
}
