#ifndef QHLOGGERMESSAGE_H
#define QHLOGGERMESSAGE_H

/**
 * @file       qhloggermessage.h
 * @brief      日志消息
 *
 * @author     wmz
 * @date       2026/09/10
 * @history
 */

#include <QObject>
#include <QDateTime>
#include "qhloggerdefine.h"
#include "QH_global.h"

class QTHANDY_EXPORT QhLoggerMessage
{
    friend class QhLogger;

public:
    using Ptr = QSharedPointer<QhLoggerMessage>;

    QhLoggerMessage();
    QhLoggerMessage(QhLoggerLevel level, const QString &file,
        const QString &funcname, int line, const QString &content);
    ~QhLoggerMessage();

    bool isForceNewFile() const;

    QDateTime dateTime;
    QhLoggerLevel level;
    QString file;
    QString funcname;
    int line;
    QString content;

protected:
    bool bForceNewFile = false;
};

#endif // QHLOGGERMESSAGE_H
