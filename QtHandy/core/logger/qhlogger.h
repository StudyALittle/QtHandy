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
#include "qhloggerdefine.h"
#include "qhloggerconfig.h"
#include "qhloggermessage.h"
#include "qhloggerappender.h"
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

class QhLoggerPrivate;

class QTHANDY_EXPORT QhLogger : public QObject
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhLogger)

public:
    QhLogger(int moduleId = LoggerMMain);
    ~QhLogger();

    /// @brief 日志模块ID
    int moduleId();

    /// @brief 日志设备操作对象
    QhLoggerAppender *appender();

    /// @brief 日志配置
    const QhLoggerConfig &loggerConfig() const;

    /// @brief 开启日志记录
    /// @param params：日志配置参数
    /// @param bAcceptQtDebug：是否记录Qt debug日志（只有一个日志模块生效）
    void start(const QhLoggerConfig &params, bool bAcceptQtDebug = true);

    /// @brief 开启日志记录
    /// @param appender：自定义日志设备操作对象
    /// @param params：日志配置参数
    /// @param bAcceptQtDebug：是否记录Qt debug日志（只有一个日志模块生效）
    void start(QhLoggerAppender *appender, const QhLoggerConfig &params, bool bAcceptQtDebug = true);

    /// @brief 停止写日志
    /// @param bWaitAllWrite：是否等待全部日志写完
    void stop(bool bWaitAllWrite = false);

    /// @brief 写日志
    void write(QhLoggerLevel type, const QString &file, const QString &funcname, int line, const QString &content);

    /// @brief 写日志
    void write(QhLoggerMessage::Ptr msg);

    /// @brief 强制创建新的日志设备
    void forceCreateNewFile();
};

class QTHANDY_EXPORT QhLoggers : public QObject
{
    Q_OBJECT

public:
    static QhLoggers *instance();
    ~QhLoggers();

    /// @brief 添加日志模块
    QhLogger *addModule(int module = LoggerMMain);

    /// @brief 删除日志模块
    void deleteModule(int module = LoggerMMain, bool bWaitAllWrite = false);

    /// @brief 删除所有日志模块
    void deleteAllModules(bool bWaitAllWrite = false);

    /// @brief 日志模块
    QhLogger *module(int module = LoggerMMain);

protected:
    QhLoggers();

    QMap<int, QhLogger *> modules;
};

#define gHLOGgers QhLoggers::instance()

#endif // QHLOGGER_H
