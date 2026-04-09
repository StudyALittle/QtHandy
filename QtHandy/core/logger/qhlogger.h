#ifndef QHLOGGER_H
#define QHLOGGER_H

/**
 * @file       Qhlogger.h
 * @brief      {文件说明}
 *
 * @author     wmz
 * @date       2026/02/28
 * @history
 */

#include <QDateTime>
#include <QMap>
#include <QVector>
#include <QSharedPointer>
#include "QH_global.h"

// # .pro文件，添加预处理，防止qDebug在release模式下，输出的日志信息不显示文件名，行号等信息
// DEFINES += QT_MESSAGELOGCONTEXT

#ifdef _MSC_VER
#define HLOG_WRITE(Md, Level, Msg) \
    QhLoggers::instance()->module(Md)->write(Level, __FILE__, __FUNCTION__, __LINE__, Msg)
#else
#define HLOG_WRITE(Md, Level, Msg) \
    QhLoggers::instance()->module(Md)->write(Level, __FILE__, __PRETTY_FUNCTION__, __LINE__, Msg);
#endif

#define HLOG_TRACE(Msg) HLOG_WRITE(LoggerMMain, LoggerLTrace, Msg)
#define HLOG_DEBUG(Msg) HLOG_WRITE(LoggerMMain, LoggerLDebug, Msg)
#define HLOG_INFO(Msg) HLOG_WRITE(LoggerMMain, LoggerLInfo, Msg)
#define HLOG_WARRING(Msg) HLOG_WRITE(LoggerMMain, LoggerLWarring, Msg)
#define HLOG_CRITICAL(Msg) HLOG_WRITE(LoggerMMain, LoggerLCritical, Msg)
#define HLOG_FATAL(Msg) HLOG_WRITE(LoggerMMain, LoggerLFail, Msg)

#define HLOGMD_TRACE(Md, Msg) HLOG_WRITE(Md, LoggerLTrace, Msg)
#define HLOGMD_DEBUG(Md, Msg) HLOG_WRITE(Md, LoggerLDebug, Msg)
#define HLOGMD_INFO(Md, Msg) HLOG_WRITE(Md, LoggerLInfo, Msg)
#define HLOGMD_WARRING(Md, Msg) HLOG_WRITE(Md, LoggerLWarring, Msg)
#define HLOGMD_CRITICAL(Md, Msg) HLOG_WRITE(Md, LoggerLCritical, Msg)
#define HLOGMD_FATAL(Md, Msg) HLOG_WRITE(Md, LoggerLFail, Msg)

class QhLogger;
class QhLoggerAppender;
class QhLoggerPrivate;

/// Logging module (multiple modules can write logs to different files)
enum QhLoggerModule {
    LoggerMMain = 0,   // 默认模块
    LoggerMCustom = 10 // 自定义模块
};

/// @brief logger level（追踪，调试、信息、警告、严重、错误）
enum QhLoggerLevel {
    LoggerLTrace = 0,
    LoggerLDebug = 1,
    LoggerLInfo = 2,
    LoggerLWarring = 3,
    LoggerLCritical = 4,
    LoggerLFail = 5
};

/// @brief Log configuration file
class QTHANDY_EXPORT QhLoggerConfig
{
public:
    /// @brief Configuration file type
    enum CFileType { CFileIni, CFileXml };

    QhLoggerConfig();
    ~QhLoggerConfig();

    /// @brief storage path:
    ///   "$$CacheLocation"开始：替换为用户缓存目录；
    ///   "$$AppLocalDataLocation"开始：替换为用户数据目录；
    ///   "."开始：替换为当前可执行程序目录；
    ///   其它表示为绝对路径；
    QString toAbsoluteDirectory(const QString &path = "$$CacheLocation/hlogger") const;

    /// @brief Whether to enable logging
    bool bStart = true;
    /// @brief Is the log written by a sub-thread
    bool bSubThreadWrite = true;

    /// @brief storage path
    QString storageDirectory;

    /// @brief Log file name format
    /// example: "logger_%1.log" (%1 is a placeholder for date and time)
    QString fileNameFormat = "logger_%1.log";
    /// @brief Log file name date time format
    /// example: "yyyy_MM_dd_hhmmss" (fileNameFormat %1)
    QString fileNameDateTimeFormat = "yyyy_MM_dd_hhmmss";

    /// @brief Maximum number of stored log files (0 or less indicates no limit)
    int nStorageFileMaxNumber = 6;
    /// @brief Maximum storage days for logs (0 or less indicates no limit)
    int nStorageFileMaxDay = 0;

    /// @brief 单个日志文件最大存储数据条数（小于等于0，表示不限制）
    int nSingleFileDataMaxCount = 0;
    /// @brief 单个日志文件最大存储数据大小（字节）（小于等于0，表示不限制）
    int nSingleFileDataMaxSize = 5 * 1024 * 1024;
    /// @brief 超过时间新建日志文件（小于等于0表示不做时间判断 s）
    int nNewFileCreateTimeSpace = 0;

    /// @brief 是否追加到文件
    bool bAppend = true;
    /// @brief 写入文件是否立即刷新
    bool bImmediatelyFlush = true;
    /// @brief 追加到文件时，上一次文件修改时间大于值，重新创建，小于等于0不判断(分钟)
    int nAppendTimeMaxSpace = 1440;

    /// @brief 是否输出日志到控制台
    bool bOutConsole;

    /// @brief 输出日志类型
    QVector<QhLoggerLevel> outputlogLevels = {
        LoggerLTrace, LoggerLDebug, LoggerLInfo, LoggerLWarring, LoggerLCritical, LoggerLFail};

    /// @brief 输出日志内容格式（可调整顺序）
    /// 示例：[%1 %2] %3 [%4 : %5 : %6]
    /// %1-日志类型；%2-时间；%3-内容；%4-文件；%5-函数；%6-行号
    QString contentFormat = "[%1 %2] %3 [%4 : %5 : %6]";

    /// @brief Save configuration file
    void writeToFile(const QString &fileName);

    /// @brief Read configuration from file
    static QhLoggerConfig readFromFile(
        const QString &fileName, bool bWriteDefValAtNoKey = true, CFileType type = CFileIni);
    static QhLoggerConfig readFromIniFile(const QString &fileName, bool bWriteDefValAtNoKey = true);
    static QhLoggerConfig readFromXmlFile(const QString &fileName, bool bWriteDefValAtNoKey = true);

    /// @brief Save configuration file
    static void writeToFile(const QString &fileName, const QhLoggerConfig &params);
};

/// @brief A single log message
class QTHANDY_EXPORT QhLoggerMessage
{
    friend class QhLogger;

public:
    using Ptr = QSharedPointer<QhLoggerMessage>;

    QhLoggerMessage();
    QhLoggerMessage(
        QhLoggerLevel level, const QString &file, const QString &funcname, int line, const QString &content);
    ~QhLoggerMessage();

    QDateTime dateTime;
    QhLoggerLevel level;
    QString file;
    QString funcname;
    int line;
    QString content;

    bool isForceNewFile() const;

protected:
    bool bForceNewFile = false;
};

class QTHANDY_EXPORT QhLoggerAppender : public QObject
{
    Q_OBJECT
    friend class QhLogger;
    friend class QhLoggerPrivate;

public:
    QhLoggerAppender(QObject *parent = nullptr);
    ~QhLoggerAppender();

protected:
    /// 初始化设备
    virtual void initDevice() = 0;
    /// 打开设备
    virtual void openDevice() = 0;
    /// 关闭设备
    virtual void closeDevice() = 0;
    /// 清理设备数据
    virtual void cleanDeviceData() = 0;
    /// 写数据
    virtual void writeData(QhLoggerMessage::Ptr msg) = 0;

    //// 消息过滤，返回: true：写消息，false：不写消息
    virtual bool msgFilter(QhLoggerConfig *logParams, QhLoggerMessage::Ptr msg);

    /// 消息格式化
    virtual QString msgItemFormat(QhLoggerMessage::Ptr msg);

    /// 日志级别转字符串
    virtual QString loggerLevelToString(QhLoggerLevel level);
    /// 写消息前的处理，返回false不写入文件
    virtual bool beforeWriteMsgItem(QhLoggerMessage::Ptr msg);
    /// 写消息后的处理
    virtual void afterWriteMsgItem(QhLoggerMessage::Ptr msg);

    QhLogger *hlogger = nullptr;
};

class QTHANDY_EXPORT QhLogger : public QObject
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhLogger)

public:
    QhLogger(int moduleId = LoggerMMain);
    ~QhLogger();

    int moduleId();

    QhLoggerAppender *appender();

    const QhLoggerConfig &loggerConfig() const;

    void start(const QhLoggerConfig &params, bool bAcceptQtDebug = true);
    void start(QhLoggerAppender *appender, const QhLoggerConfig &params, bool bAcceptQtDebug = true);

    void stop(bool bWaitAllWrite = false);

    void write(QhLoggerLevel type, const QString &file, const QString &funcname, int line, const QString &content);
    void write(QhLoggerMessage::Ptr msg);

    void forceCreateNewFile();
};

class QTHANDY_EXPORT QhLoggers : public QObject
{
    Q_OBJECT

public:
    static QhLoggers *instance();
    ~QhLoggers();

    QhLogger *addModule(int module = LoggerMMain);
    void deleteModule(int module = LoggerMMain, bool bWaitAllWrite = false);
    void deleteAllModules(bool bWaitAllWrite = false);

    QhLogger *module(int module = LoggerMMain);

protected:
    QhLoggers();

    QMap<int, QhLogger *> modules;
};

#define gHLOGgers QhLoggers::instance()

#endif // QHLOGGER_H
