#include "qhlogger.h"
#include "qhlogger_p.h"
#include <QCoreApplication>
#include <QStandardPaths>
#include <QSettings>
#include <QLoggingCategory>
#include "qhloggerfileappender.h"

QtMessageHandler g_defaultHandler = nullptr;
int QhLoggerPrivate::s_acceptQtDebugModuleId = -1;

QhLogger::QhLogger(int moduleId) : d(new QhLoggerPrivate(this, moduleId))
{
}

QhLogger::~QhLogger()
{
}

int QhLogger::moduleId()
{
    return d->moduleId;
}

QhLoggerAppender *QhLogger::appender()
{
    return d->appender;
}

const QhLoggerConfig &QhLogger::loggerConfig() const
{
    return d->loggerConfig;
}

void QhLogger::start(const QhLoggerConfig &params, bool bAcceptQtDebug)
{
    start(new QhLoggerFileAppender, params, bAcceptQtDebug);
}

void QhLogger::start(QhLoggerAppender *appender, const QhLoggerConfig &params, bool bAcceptQtDebug)
{
    d->loggerConfig = params;
    d->bAcceptQtDebug = bAcceptQtDebug;

    d->appender = appender;
    d->appender->setParent(this);
    d->appender->hlogger = this;

    d->startLogger();
}

void QhLogger::stop(bool bWaitAllWrite)
{
    d->stopLogger(bWaitAllWrite);
}

void QhLogger::write(QhLoggerLevel type, const QString &file,
    const QString &funcname, int line, const QString &content)
{
    write(QSharedPointer<QhLoggerMessage>::create(type, file, funcname, line, content));
}

void QhLogger::write(QhLoggerMessage::Ptr msg)
{
    d->appendMessage(msg);
}

void QhLogger::forceCreateNewFile()
{
    auto msg = QSharedPointer<QhLoggerMessage>::create();
    msg->bForceNewFile = true;
    write(msg);
}

QhLoggerPrivate::QhLoggerPrivate(QhLogger *log, int moduleId) :
    logger(log), moduleId(moduleId)
{
}

QhLoggerPrivate::~QhLoggerPrivate()
{
    if (appender)
        appender->closeDevice();
}

void QhLoggerPrivate::startLogger()
{
    // 可通过配置是否开启日志
    if (!loggerConfig.bStart)
        return;

    bRun = true;
    bWaitAllWriteAtStop = false;

    if (bAcceptQtDebug) {
        // 注册QT debug日志句柄
        s_acceptQtDebugModuleId = moduleId;
        QLoggingCategory::setFilterRules(QStringLiteral("*.debug=true\nqt.*.debug=false"));
        g_defaultHandler = qInstallMessageHandler(QhLoggerPrivate::qMessageHandler);
    } else {
        g_defaultHandler = nullptr;
        qInstallMessageHandler(nullptr);
    }

    appender->initDevice();
    if (loggerConfig.bSubThreadWrite) {
        this->start();
    }
}

void QhLoggerPrivate::stopLogger(bool bWaitAllWrite)
{
    mutex.lock();
    bWaitAllWriteAtStop = bWaitAllWrite;
    bRun = false;
    condition.wakeAll();
    mutex.unlock();

    this->quit();
    this->wait();

    if (appender) {
        appender->closeDevice();
    }
}

void QhLoggerPrivate::appendMessage(QhLoggerMessage::Ptr msg)
{
#ifdef QT_DEBUG
    // DEBUG模式同时打印日志到控制台
    writeConsole(msg);
#else
    if (loggerConfig.bOutConsole) {
        writeConsole(msg);
    }
#endif

    if (!bRun)
        return;

    if (!appender->msgFilter(msg))
        return;

    mutex.lock();
    if (cacheLoggers.size() > loggerConfig.maxCacheCount) {
        mutex.unlock();
        return;
    }

    if (loggerConfig.bSubThreadWrite) {
        // sub thread list append
        cacheLoggers.append(msg);
        condition.wakeOne();
    } else {
        writeData(msg);
    }
    mutex.unlock();
}

void QhLoggerPrivate::writeConsole(QhLoggerMessage::Ptr msg)
{
    QString text = appender
        ? appender->msgItemFormat(msg)
            : QString("[%1 %2] %3 [%4 : %5 : %6]")
                .arg(msg->level)
                .arg(msg->dateTime.toString("yyyy-MM-dd HH:mm:ss.zzz "), msg->content,  msg->file, msg->funcname)
                .arg(msg->line);
    if (!bAcceptQtDebug) {
        qDebug() << msg;
    } else if (g_defaultHandler) {
        g_defaultHandler(QtWarningMsg, QMessageLogContext(), text);
    }
}

void QhLoggerPrivate::writeData(QhLoggerMessage::Ptr msg)
{
    appender->writeData(msg);
}

void QhLoggerPrivate::run()
{
    while (bRun) {
        QList<QhLoggerMessage::Ptr> loggers;

        mutex.lock();
        loggers = cacheLoggers;
        cacheLoggers.clear();
        mutex.unlock();

        foreach (auto log, loggers) {
            if (!bWaitAllWriteAtStop && !bRun)
                break;
            writeData(log);
        }

        mutex.lock();
        if (!bRun) {
            mutex.unlock();
            break;
        }

        if (cacheLoggers.size()) {
            mutex.unlock();
            continue;
        }

        condition.wait(&mutex);
        mutex.unlock();
    }

    // 写完全部日志
    if (bWaitAllWriteAtStop) {
        QList<QhLoggerMessage::Ptr> loggers = cacheLoggers;
        foreach (auto log, loggers) {
            writeData(log);
        }
    }
    cacheLoggers.clear();
}

void QhLoggerPrivate::qMessageHandler(QtMsgType msgType, const QMessageLogContext &context, const QString &msg)
{
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";

    QhLoggerLevel logType;
    switch (msgType) {
    case QtDebugMsg: {
        logType = LoggerLDebug;
        break;
    }
    case QtWarningMsg: {
        logType = LoggerLWarring;
        break;
    }
    case QtCriticalMsg: {
        logType = LoggerLCritical;
        break;
    }
    case QtFatalMsg: {
        logType = LoggerLFail;
        break;
    }
    case QtInfoMsg: {
        logType = LoggerLInfo;
        break;
    }
    }

    auto *md = QhLoggers::instance()->module(s_acceptQtDebugModuleId);
    if (md) {
        md->write(logType, file, function, context.line, msg);
    }
}

QhLoggers *QhLoggers::instance()
{
    static QhLoggers s_instance;
    return &s_instance;
}

QhLoggers::~QhLoggers()
{
    deleteAllModules();
}

QhLogger *QhLoggers::addModule(int module)
{
    auto *slog = new QhLogger(module);
    modules.insert(module, slog);
    return slog;
}

void QhLoggers::deleteModule(int md, bool bWaitAllWrite)
{
    auto *slog = module(md);
    if (slog) {
        modules.remove(md);
        slog->stop(bWaitAllWrite);
        delete slog;
    }
}

void QhLoggers::deleteAllModules(bool bWaitAllWrite)
{
    foreach (auto *slog, modules) {
        slog->stop(bWaitAllWrite);
        delete slog;
    }
    modules.clear();
}

QhLogger *QhLoggers::module(int module)
{
    if (modules.contains(module))
        return modules.value(module);
    return nullptr;
}

QhLoggers::QhLoggers()
{
}
