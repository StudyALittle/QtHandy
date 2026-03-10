#ifndef QHLOGGER_P_H
#define QHLOGGER_P_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include "qhlogger.h"

class QhLoggerPrivate: public QThread
{
    Q_OBJECT
    Q_DISABLE_COPY(QhLoggerPrivate)

public:
    explicit QhLoggerPrivate(QhLogger *q, int moduleId);
    ~QhLoggerPrivate();

    QhLogger const *ptr;

    int moduleId;
    QhLoggerAppender *appender = nullptr;
    QhLoggerConfig loggerConfig;
    bool bAcceptQtDebug = false;
    bool bRun = false;
    bool bWaitAllWriteAtStop = false;

public:
    void startLogger();
    void stopLogger(bool bWaitAllWrite);

    void appendMessage(QhLoggerMessage::Ptr msg);

    void writeData(QhLoggerMessage::Ptr msg);
    void run() override;
    static void qMessageHandler(QtMsgType msgType, const QMessageLogContext &context, const QString &msg);

    QMutex mutex;
    QWaitCondition condition;
    QList<QhLoggerMessage::Ptr> cacheLoggers;
};

#endif // QHLOGGER_P_H
