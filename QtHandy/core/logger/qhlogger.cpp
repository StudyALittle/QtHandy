#include "qhlogger.h"
#include "qhlogger_p.h"
#include <QCoreApplication>
#include <QStandardPaths>
#include <QSettings>
#include <QLoggingCategory>
#include "qhloggerfileappender.h"

QtMessageHandler g_defaultHandler = nullptr;

QhLoggerConfig::QhLoggerConfig()
{

}

QhLoggerConfig::~QhLoggerConfig()
{

}

QString QhLoggerConfig::toAbsoluteDirectory(const QString &strPath) const
{
    QString strCacheLocation = "$$CacheLocation";
    QString strAppLocalDataLocation = "$$AppLocalDataLocation";
    QString path = strPath;
    if (path.startsWith(".")) {
        path.replace(0, 1, QCoreApplication::applicationDirPath());
    } else if (path.startsWith(strCacheLocation)) {
        path.replace(0, strCacheLocation.size(),
            QStandardPaths::writableLocation(QStandardPaths::CacheLocation));
    } else if (path.startsWith(strAppLocalDataLocation)) {
        path.replace(0, strAppLocalDataLocation.size(),
            QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation));
    }

    path = path.replace("\\", "/");
    if (!path.endsWith("/"))
        path.append("/");
    return path;
}

void QhLoggerConfig::writeToFile(const QString &fileName)
{
    writeToFile(fileName, *this);
}

QhLoggerConfig QhLoggerConfig::readFromFile(const QString &fileName, bool bWriteDefValAtNoKey, CFileType type)
{
    if (type == CFileIni)
        return readFromIniFile(fileName, bWriteDefValAtNoKey);
    return readFromXmlFile(fileName, bWriteDefValAtNoKey);
}

#define INI_GETSET(Key, ToFunc) \
    if (setting.contains(#Key)) \
        params.Key = setting.value(#Key).ToFunc(); \
    else if (bWriteDefValAtNoKey) \
        setting.setValue(#Key, params.Key);

QhLoggerConfig QhLoggerConfig::readFromIniFile(const QString &fileName, bool bWriteDefValAtNoKey)
{
    QhLoggerConfig params;

    QSettings setting(fileName, QSettings::IniFormat);
    setting.beginGroup("config");

    INI_GETSET(bStart, toBool)
    INI_GETSET(bSubThreadWrite, toBool)
    INI_GETSET(storageDirectory, toString)
    INI_GETSET(fileNameFormat, toString)
    INI_GETSET(fileNameDateTimeFormat, toString)
    INI_GETSET(nStorageFileMaxNumber, toInt)
    INI_GETSET(nStorageFileMaxDay, toInt)
    INI_GETSET(nSingleFileDataMaxCount, toInt)
    INI_GETSET(nSingleFileDataMaxSize, toInt)
    INI_GETSET(nNewFileCreateTimeSpace, toInt)
    INI_GETSET(bAppend, toBool)
    INI_GETSET(bImmediatelyFlush, toBool)
    INI_GETSET(nAppendTimeMaxSpace, toInt)
    INI_GETSET(bOutConsole, toBool)
    INI_GETSET(contentFormat, toString)

    if (setting.contains("outputlogLevels")) {
        QVector<QhLoggerLevel> outputlogLevels;
        QStringList strlists = setting.value("outputlogLevels").toString()
                .split(",", QString::SkipEmptyParts);
        foreach (auto str, strlists) {
            if (str.trimmed().toUpper() == "TRACE") {
                outputlogLevels.append(LoggerLTrace);
            } else if (str.trimmed().toUpper() == "DEBUG") {
                outputlogLevels.append(LoggerLDebug);
            } else if (str.trimmed().toUpper() == "INFO") {
                outputlogLevels.append(LoggerLInfo);
            } else if (str.trimmed().toUpper() == "WARNING") {
                outputlogLevels.append(LoggerLWarring);
            } else if (str.trimmed().toUpper() == "CRITICAL") {
                outputlogLevels.append(LoggerLCritical);
            } else if (str.trimmed().toUpper() == "FAIL") {
                outputlogLevels.append(LoggerLFail);
            }
        }
        params.outputlogLevels = outputlogLevels;
    } else {
        QStringList types;
        foreach (auto type, params.outputlogLevels) {
            switch (type) {
            case LoggerLTrace: { types.append("Trace"); break; }
            case LoggerLDebug: { types.append("Debug"); break; }
            case LoggerLInfo: { types.append("Info"); break; }
            case LoggerLWarring: { types.append("Warning"); break; }
            case LoggerLCritical: { types.append("Critical"); break; }
            case LoggerLFail: { types.append("Fail"); break; }
            default: break;
            }
        }
        setting.setValue("outputlogLevels", types.join(","));
    }

    setting.endGroup();
    return params;
}

QhLoggerConfig QhLoggerConfig::readFromXmlFile(const QString &fileName, bool bWriteDefValAtNoKey)
{
    return QhLoggerConfig();
}

QhLoggerMessage::QhLoggerMessage()
{
    dateTime = QDateTime::currentDateTime();
}

QhLoggerMessage::QhLoggerMessage(
        QhLoggerLevel level, const QString &file,
        const QString &funcname, int line, const QString &content):
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

QhLoggerAppender::QhLoggerAppender(QObject *parent):
    QObject(parent)
{

}

QhLoggerAppender::~QhLoggerAppender()
{

}

bool QhLoggerAppender::msgFilter(QhLoggerConfig *logParams, QhLoggerMessage::Ptr msg)
{
    // 写日志级别判断
    if (!logParams->outputlogLevels.contains(msg->level))
        return false;

    //    // 过滤器
    //    QVector<QRegularExpression> m_filterRegs;
    //    if (m_filterRegs.size()) {
    //        for (auto reg: m_filterRegs) {
    //            auto match = reg.match(content);
    //            if (match.hasMatch())
    //                return;
    //        }
    //    }

    return true;
}

QString QhLoggerAppender::msgItemFormat(QhLoggerMessage::Ptr msg)
{
    QString format = hlogger->loggerConfig().contentFormat;
    return format
       .arg(loggerLevelToString(msg->level))
       .arg(msg->dateTime.toString("yyyy-MM-dd HH:mm:ss.zzz "))
       .arg(msg->content)
       .arg(msg->file)
       .arg(msg->funcname)
            .arg(msg->line);
}

QString QhLoggerAppender::loggerLevelToString(QhLoggerLevel level)
{
    switch (level) {
    case LoggerLTrace:    { return QStringLiteral("TRACE"); }
    case LoggerLDebug:    { return QStringLiteral("DEBUG"); }
    case LoggerLInfo:     {return QStringLiteral("INFO"); }
    case LoggerLWarring:  { return QStringLiteral("WARRING"); }
    case LoggerLCritical: { return QStringLiteral("CRITICAL"); }
    case LoggerLFail:     { return QStringLiteral("ERROR"); }
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

void QhLoggerConfig::writeToFile(const QString &fileName, const QhLoggerConfig &params)
{
    QSettings setting(fileName, QSettings::IniFormat);
    setting.beginGroup("config");

    setting.setValue("bStart", params.bStart);
    setting.setValue("bSubThreadWrite", params.bSubThreadWrite);
    setting.setValue("storageDirectory", params.storageDirectory);
    setting.setValue("fileNameFormat", params.fileNameFormat);
    setting.setValue("fileNameDateTimeFormat", params.fileNameDateTimeFormat);
    setting.setValue("nStorageFileMaxNumber", params.nStorageFileMaxNumber);
    setting.setValue("nStorageFileMaxDay", params.nStorageFileMaxDay);
    setting.setValue("nSingleFileDataMaxCount", params.nSingleFileDataMaxCount);
    setting.setValue("nSingleFileDataMaxSize", params.nSingleFileDataMaxSize);
    setting.setValue("nNewFileCreateTimeSpace", params.nNewFileCreateTimeSpace);
    setting.setValue("bAppend", params.bAppend);
    setting.setValue("bImmediatelyFlush", params.bImmediatelyFlush);
    setting.setValue("nAppendTimeMaxSpace", params.nAppendTimeMaxSpace);
    setting.setValue("bOutConsole", params.bOutConsole);
    setting.setValue("contentFormat", params.contentFormat);

    QStringList levels;
    foreach (auto type, params.outputlogLevels) {
        switch (type) {
        case LoggerLTrace: { levels.append("ETrace"); break; }
        case LoggerLDebug: { levels.append("EDebug"); break; }
        case LoggerLInfo: { levels.append("EInfo"); break; }
        case LoggerLWarring: { levels.append("EWarring"); break; }
        case LoggerLCritical: { levels.append("ECritical"); break; }
        case LoggerLFail: { levels.append("EFail"); break; }
        default: break;
        }
    }
    setting.setValue("outputlogLevels", levels.join(","));
    setting.endGroup();
}

QhLogger::QhLogger(int moduleId):
    d(new QhLoggerPrivate(this, moduleId))
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
    d->loggerConfig = params;
    d->bAcceptQtDebug = bAcceptQtDebug;
    if (!d->appender) {
        d->appender = new QhLoggerFileAppender(this);
        d->appender->hlogger = this;
    }
    d->startLogger();
}

void QhLogger::start(QhLoggerAppender *appender, const QhLoggerConfig &params, bool bAcceptQtDebug)
{
    if (appender) {
        appender->hlogger = this;
        d->appender = appender;
    }
    start(params, bAcceptQtDebug);
}

void QhLogger::stop(bool bWaitAllWrite)
{
    d->stopLogger(bWaitAllWrite);
}

void QhLogger::write(QhLoggerLevel type, const QString &file, const QString &funcname, int line, const QString &content)
{
    write(QSharedPointer<QhLoggerMessage>::create(
        type, file, funcname, line, content));
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

QhLoggerPrivate::QhLoggerPrivate(QhLogger *q, int moduleId):
    ptr(q), moduleId(moduleId)
{

}

QhLoggerPrivate::~QhLoggerPrivate()
{

}

void QhLoggerPrivate::startLogger()
{
    if (!loggerConfig.bStart)
        return;

    bRun = true;
    bWaitAllWriteAtStop = false;

    if (bAcceptQtDebug) {
        QLoggingCategory::setFilterRules(
                    QStringLiteral("*.debug=true\nqt.*.debug=false"));
        g_defaultHandler = qInstallMessageHandler(QhLoggerPrivate::qMessageHandler);
    } else {
        g_defaultHandler = nullptr;
        qInstallMessageHandler(nullptr);
    }

    appender->initDevice();
    if (loggerConfig.bSubThreadWrite)
        this->start();
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

    if (appender)
        appender->closeDevice();
}

void QhLoggerPrivate::appendMessage(QhLoggerMessage::Ptr msg)
{
    auto writeConsole = [this](QhLoggerMessage::Ptr msgItem)
    {
        QString msg = appender ?
            appender->msgItemFormat(msgItem) :
                QString("[%1 %2] %3 [%4 : %5 : %6]")
                  .arg(msgItem->level)
                  .arg(msgItem->dateTime.toString("yyyy-MM-dd HH:mm:ss.zzz "))
                  .arg(msgItem->content)
                  .arg(msgItem->file)
                  .arg(msgItem->funcname)
                  .arg(msgItem->line);
        if (!bAcceptQtDebug) {
            qDebug() << msg;
        } else if (g_defaultHandler) {
            g_defaultHandler(QtWarningMsg, QMessageLogContext(), msg);
        }
    };

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

    if (!appender->msgFilter(&loggerConfig, msg))
        return;

    mutex.lock();
    // 防止日志内存不断变大
    if (cacheLoggers.size() > 200) {
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

void QhLoggerPrivate::writeData(QhLoggerMessage::Ptr msg)
{
    appender->writeData(msg);
}

void QhLoggerPrivate::run()
{
    while(bRun) {
        QList<QhLoggerMessage::Ptr> loggers;

        mutex.lock();
        loggers = cacheLoggers;
        cacheLoggers.clear();
        mutex.unlock();

        foreach (auto log, loggers) {
            if (bWaitAllWriteAtStop && !bRun) {
                break;
            }
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
    case QtDebugMsg:    { logType = LoggerLDebug; break; }
    case QtWarningMsg:  { logType = LoggerLWarring; break; }
    case QtCriticalMsg: { logType = LoggerLCritical; break; }
    case QtFatalMsg:    { logType = LoggerLFail; break; }
    case QtInfoMsg:     { logType = LoggerLInfo; break; }
    }

    auto *md = QhLoggers::instance()->module();
    if (md)
        md->write(logType, file, function, context.line, msg.toLocal8Bit());
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
