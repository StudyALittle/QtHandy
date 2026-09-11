#ifndef QHLOGGERCONFIG_H
#define QHLOGGERCONFIG_H

/**
 * @file       qhloggerconfig.h
 * @brief      日志配置（Log configuration file）
 *
 * @author     wmz
 * @date       2026/09/10
 * @history
 */

#include <QObject>
#include "qhloggerdefine.h"
#include "QH_global.h"

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
    ///   ".."开始：替换为当前可执行程序目录的上一级；
    ///   其它表示为绝对路径；
    static QString toAbsoluteDirectory(const QString &path = "$$CacheLocation/hlogger");

    /// @brief Whether to enable logging
    bool bStart = true;
    /// @brief Is the log written by a sub-thread
    bool bSubThreadWrite = true;

    /// @brief storage path
    QString storageDirectory = "$$AppLocalDataLocation/logger";

    /// @brief Log file name format
    /// example: "logger_%1.log" (%1 is a placeholder for date and time)
    QString fileNameFormat = "logger_%1.log";
    /// @brief Log file name date time format
    /// example: "yyyy_MM_dd_hhmmss" (fileNameFormat %1)
    QString fileNameDateTimeFormat = "yyyy_MM_dd_hhmmss_zzz";

    /// @brief Maximum number of stored log files (0 or less indicates no limit)
    int nStorageFileMaxNumber = 30;
    /// @brief Maximum storage days for logs (0 or less indicates no limit)
    int nStorageFileMaxDay = 0;

    /// @brief 单个日志文件最大存储数据条数（小于等于0，表示不限制）
    int nSingleFileDataMaxCount = 0;
    /// @brief 单个日志文件最大存储数据大小（字节）（小于等于0，表示不限制）
    int nSingleFileDataMaxSize = 10 * 1024 * 1024;
    /// @brief 超过时间新建日志文件（小于等于0表示不做时间判断 s）
    int nNewFileCreateTimeSpace = 0;

    /// @brief 是否追加到文件
    bool bAppend = true;
    /// @brief 写入文件是否立即刷新
    bool bImmediatelyFlush = true;
    /// @brief 追加到文件时，上一次文件修改时间大于值，重新创建，小于等于0不判断(分钟)
    int nAppendTimeMaxSpace = 1440;
    /// @brief 新的一天是否追加到文件
    bool bAppendAtNewDay = false;

    /// @brief 是否输出日志到控制台
    bool bOutConsole = false;

    /// @brief 在内存中缓存的日志最大条数，小于0时不做限制
    int maxCacheCount = 2000;

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

#endif // QHLOGGERCONFIG_H
