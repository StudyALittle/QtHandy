#ifndef QHLOGGERFILEAPPENDER_H
#define QHLOGGERFILEAPPENDER_H

#include <QMap>
#include <QDateTime>
#include <QSharedPointer>
#include "qhlogger.h"
#include "QH_global.h"

class QhLoggerFileAppenderPrivate;

class QTHANDY_EXPORT QhLoggerFileAppender: public QhLoggerAppender
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhLoggerFileAppender)

public:
    QhLoggerFileAppender(QObject *parent = nullptr);
    virtual ~QhLoggerFileAppender();

    /// @brief 创建文件名称
    virtual QString generateFileName(const QhLoggerConfig &logParams);
    static QString newNotExistsFilename(const QString &filename);

    void initDevice() override;
    void openDevice() override;
    void closeDevice() override;
    void cleanDeviceData() override;
    void writeData(QhLoggerMessage::Ptr msg) override;

signals:
    /// 日志文件被创建
    void logFileCreated(const QString &fileName);
    /// 日志文件被关闭
    void logFileClosed(const QString &fileName);
    /// 日志文件被删除
    void logFileDeleted(const QString &fileName);
};

#endif // QHLOGGERFILEAPPENDER_H
