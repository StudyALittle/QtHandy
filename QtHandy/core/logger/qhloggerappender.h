#ifndef QHLOGGERAPPENDER_H
#define QHLOGGERAPPENDER_H

/**
 * @file       qhloggerappender.h
 * @brief      日志设备操作
 *
 * @author     wmz
 * @date       2026/09/10
 * @history
 */

#include <QObject>
#include "qhloggerconfig.h"
#include "qhloggermessage.h"
#include "QH_global.h"

class QTHANDY_EXPORT QhLoggerAppender : public QObject
{
    Q_OBJECT
    friend class QhLogger;
    friend class QhLoggerPrivate;

public:
    QhLoggerAppender(QObject *parent = nullptr);
    ~QhLoggerAppender();

protected:
    /// @brief 初始化设备（必须）
    virtual void initDevice() = 0;
    /// @brief 打开设备
    virtual void openDevice() = 0;
    /// @brief 关闭设备（必须）
    virtual void closeDevice() = 0;
    /// @brief 清理设备数据
    virtual void cleanDeviceData() = 0;
    /// @brief 写数据（必须）
    virtual void writeData(QhLoggerMessage::Ptr msg) = 0;

    /// @brief 生成文件名称
    virtual QString generateFileName(const QhLoggerConfig &logParams);

    //// @brief 消息过滤，返回: true：写消息，false：不写消息
    virtual bool msgFilter(QhLoggerMessage::Ptr msg);

    /// @brief 消息格式化
    virtual QString msgItemFormat(QhLoggerMessage::Ptr msg);

    /// @brief 日志级别转字符串
    virtual QString loggerLevelToString(QhLoggerLevel level);
    /// @brief 写消息前的处理，返回false不写入文件
    virtual bool beforeWriteMsgItem(QhLoggerMessage::Ptr msg);
    /// @brief 写消息后的处理
    virtual void afterWriteMsgItem(QhLoggerMessage::Ptr msg);

    QhLogger *hlogger = nullptr;
};

#endif // QHLOGGERAPPENDER_H
