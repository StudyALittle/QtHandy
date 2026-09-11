#include "qhloggerappender.h"
#include "qhlogger.h"
#include <QFileInfo>
#include <QDir>
#include <qhfileutil.h>

QhLoggerAppender::QhLoggerAppender(QObject *parent) : QObject(parent)
{
}

QhLoggerAppender::~QhLoggerAppender()
{
}

QString QhLoggerAppender::generateFileName(const QhLoggerConfig &logParams)
{
    QString baseDir = QhLoggerConfig::toAbsoluteDirectory(logParams.storageDirectory);
    QDir dir(baseDir);
    if (!dir.exists())
        dir.mkpath(baseDir);

    QString baseFilename = logParams.fileNameFormat
        .arg(QDateTime::currentDateTime().toString(logParams.fileNameDateTimeFormat));

    if (!baseDir.endsWith("/") || !baseDir.endsWith("\\"))
        baseDir.append("/");

    QString filename = baseDir + baseFilename;
    QFileInfo fInfo(filename);
    QString filePath = fInfo.dir().path();
    QString baseName = fInfo.baseName();
    QString suffix = fInfo.completeSuffix();

    return QhFileUtil::generateFileName(QString("%1/%2").arg(filePath, baseName), suffix);
}

bool QhLoggerAppender::msgFilter(QhLoggerMessage::Ptr msg)
{
    // 写日志级别判断
    if (!hlogger->loggerConfig().outputlogLevels.contains(msg->level))
        return false;
    return true;
}

QString QhLoggerAppender::msgItemFormat(QhLoggerMessage::Ptr msg)
{
    QString format = hlogger->loggerConfig().contentFormat;
    return format.arg(
            loggerLevelToString(msg->level),
            msg->dateTime.toString("yyyy-MM-dd HH:mm:ss.zzz "),
            msg->content,
            msg->file,
            msg->funcname)
        .arg(msg->line);
}

QString QhLoggerAppender::loggerLevelToString(QhLoggerLevel level)
{
    switch (level) {
    case LoggerLTrace: {
        return QStringLiteral("TRACE");
    }
    case LoggerLDebug: {
        return QStringLiteral("DEBUG");
    }
    case LoggerLInfo: {
        return QStringLiteral("INFO");
    }
    case LoggerLWarring: {
        return QStringLiteral("WARRING");
    }
    case LoggerLCritical: {
        return QStringLiteral("CRITICAL");
    }
    case LoggerLFail: {
        return QStringLiteral("ERROR");
    }
    }
    return QString();
}

bool QhLoggerAppender::beforeWriteMsgItem(QhLoggerMessage::Ptr msg)
{
    Q_UNUSED(msg)
    return true;
}

void QhLoggerAppender::afterWriteMsgItem(QhLoggerMessage::Ptr msg)
{
    Q_UNUSED(msg)
}
