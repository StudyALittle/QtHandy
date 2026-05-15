#ifndef QHLOGGERFILEAPPENDER_P_H
#define QHLOGGERFILEAPPENDER_P_H

#include <QFile>
#include "qhloggerfileappender.h"

class QhLoggerFileAppenderPrivate: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhLoggerFileAppenderPrivate)

public:
    explicit QhLoggerFileAppenderPrivate(QhLoggerFileAppender *q);
    ~QhLoggerFileAppenderPrivate();

    QhLoggerFileAppender const *ptr;

    QList<QString> filenames; // 已经写入的日志文件
    bool bFirstFile = true;
    QFile *file = nullptr;

    int writeCnt = 0;
    qint64 lastFirstTime = 0;
    qint64 fileSize = 0;
};

#endif // QHLOGGERFILEAPPENDER_P_H
