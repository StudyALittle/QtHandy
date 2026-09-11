#include "qhloggermessage.h"

QhLoggerMessage::QhLoggerMessage()
{
    dateTime = QDateTime::currentDateTime();
}

QhLoggerMessage::QhLoggerMessage(
    QhLoggerLevel level, const QString &file, const QString &funcname, int line, const QString &content) :
    level(level), line(line)
{
    this->file = std::move(file);
    this->funcname = std::move(funcname);
    this->content = std::move(content);
    dateTime = QDateTime::currentDateTime();
}

QhLoggerMessage::~QhLoggerMessage()
{
}

bool QhLoggerMessage::isForceNewFile() const
{
    return bForceNewFile;
}
