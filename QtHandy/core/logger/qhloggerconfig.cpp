#include "qhloggerconfig.h"
#include <QCoreApplication>
#include <QStandardPaths>
#include <QSettings>
#include <QLoggingCategory>
#include <QDir>

QhLoggerConfig::QhLoggerConfig()
{
}

QhLoggerConfig::~QhLoggerConfig()
{
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
    setting.setValue("bAppendAtNewDay", params.bAppendAtNewDay);
    setting.setValue("bOutConsole", params.bOutConsole);
    setting.setValue("maxCacheCount", params.maxCacheCount);
    setting.setValue("contentFormat", params.contentFormat);

    QStringList levels;
    foreach (auto type, params.outputlogLevels) {
        switch (type) {
        case LoggerLTrace: {
            levels.append("ETrace");
            break;
        }
        case LoggerLDebug: {
            levels.append("EDebug");
            break;
        }
        case LoggerLInfo: {
            levels.append("EInfo");
            break;
        }
        case LoggerLWarring: {
            levels.append("EWarring");
            break;
        }
        case LoggerLCritical: {
            levels.append("ECritical");
            break;
        }
        case LoggerLFail: {
            levels.append("EFail");
            break;
        }
        default:
            break;
        }
    }
    setting.setValue("outputlogLevels", levels.join(","));
    setting.endGroup();
}

QString QhLoggerConfig::toAbsoluteDirectory(const QString &strPath)
{
    static QString strCacheLocation = "$$CacheLocation";
    static QString strAppLocalDataLocation = "$$AppLocalDataLocation";

    QString path = strPath;
    if (path.isEmpty()) {
        path = "$$AppLocalDataLocation/logger";
    } else if (path.startsWith("..")) {
        QString apath = QCoreApplication::applicationDirPath();
        QDir dir(apath);
        if (dir.cdUp()) {
            apath = dir.path();
        }
        path.replace(0, 2, apath);
    } else if (path.startsWith(".")) {
        path.replace(0, 1, QCoreApplication::applicationDirPath());
    } else if (path.startsWith(strCacheLocation)) {
        path.replace(0, strCacheLocation.size(),
            QStandardPaths::writableLocation(QStandardPaths::CacheLocation));
    } else if (path.startsWith(strAppLocalDataLocation)) {
        path.replace(
            0, strAppLocalDataLocation.size(),
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

#define INI_GETSET(Key, ToFunc)                    \
    if (setting.contains(#Key))                    \
        params.Key = setting.value(#Key).ToFunc(); \
    else if (bWriteDefValAtNoKey)                  \
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
    INI_GETSET(bAppendAtNewDay, toBool)
    INI_GETSET(bOutConsole, toBool)
    INI_GETSET(maxCacheCount, toInt)
    INI_GETSET(contentFormat, toString)

    if (setting.contains("outputlogLevels")) {
        QVector<QhLoggerLevel> outputlogLevels;
        QStringList strlists = setting.value("outputlogLevels").toString().split(",", QString::SkipEmptyParts);
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
            case LoggerLTrace: {
                types.append("Trace");
                break;
            }
            case LoggerLDebug: {
                types.append("Debug");
                break;
            }
            case LoggerLInfo: {
                types.append("Info");
                break;
            }
            case LoggerLWarring: {
                types.append("Warning");
                break;
            }
            case LoggerLCritical: {
                types.append("Critical");
                break;
            }
            case LoggerLFail: {
                types.append("Fail");
                break;
            }
            default:
                break;
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
