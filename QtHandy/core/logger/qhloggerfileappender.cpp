#include "qhloggerfileappender.h"
#include "qhloggerfileappender_p.h"
#include <QFileInfo>
#include <QDir>
#include <QDateTime>

QhLoggerFileAppender::QhLoggerFileAppender(QObject *parent):
    QhLoggerAppender(parent),
    d(new QhLoggerFileAppenderPrivate(this))
{

}

QhLoggerFileAppender::~QhLoggerFileAppender()
{
    this->closeDevice();
}

QString QhLoggerFileAppender::generateFileName(const QhLoggerConfig &logParams)
{
    QString baseDir = logParams.storageDirectory;
    QDir dir(baseDir);
    if (!dir.exists())
        dir.mkpath(baseDir);

    QString baseFilename = logParams.fileNameFormat
        .arg(QDateTime::currentDateTime().toString(logParams.fileNameDateTimeFormat));

    if (!baseDir.endsWith("/") || !baseDir.endsWith("\\"))
        baseDir.append("/");
    return newNotExistsFilename(baseDir + baseFilename);
}

QString QhLoggerFileAppender::newNotExistsFilename(const QString &filename)
{
    if (!QFile::exists(filename))
        return filename;

    QString newFilename;

    QFileInfo fInfo(filename);
    QString filePath = fInfo.dir().path();
    QString baseName = fInfo.baseName();
    QString ext = fInfo.completeSuffix();

    for (int n = 1; n <= 50; ++n) {
        if (ext.isEmpty()) { // 文件无后缀
            newFilename = QString("%1/%2(%3)").arg(filePath).arg(baseName).arg(n);
        } else {
            newFilename = QString("%1/%2(%3).%4").arg(filePath).arg(baseName).arg(n).arg(ext);
        }

        if (!QFile::exists(newFilename))
            break;
    }
    return newFilename;
}

void QhLoggerFileAppender::initDevice()
{
    const static QString s_tmp = "%1";

    const auto &params = this->hlogger->loggerConfig();
    QString baseDir = params.storageDirectory;

    QDir dir(baseDir);
    if (!dir.exists(baseDir))
        return;

    QString fileNameFormat = params.fileNameFormat;

    int indexFd = fileNameFormat.indexOf(s_tmp);
    QString strBg, strEd;
    if (indexFd > 0)
        strBg = fileNameFormat.left(indexFd);
    if (indexFd + s_tmp.size() < fileNameFormat.size())
        strEd = fileNameFormat.mid(indexFd + s_tmp.size());

    QVector<qint64> filetimes;
    QMap<qint64, QString> filenames;
    auto fileInfos = dir.entryInfoList(QDir::Files);
    foreach (auto fileInfo, fileInfos) {
        QString filename = fileInfo.fileName();
        if (filename.isEmpty() || filename == "." || filename == "..")
            continue;

        if (filename.startsWith(strBg) && filename.endsWith(strEd)) {
            QDateTime datetime = fileInfo.birthTime();
            if (!datetime.isValid())
                datetime = fileInfo.lastModified();

            filetimes.append(datetime.toMSecsSinceEpoch());
            filenames.insert(datetime.toMSecsSinceEpoch(), fileInfo.filePath());
        }
    }

    // 排序，删除更早之前的日志（升序）
    std::sort(filetimes.begin(), filetimes.end());

    for (int n = 0, index = 0; n < filetimes.size(); ++n, ++index) {
        QString filename = filenames.value(filetimes.at(n));
        d->filenames.append(filename);
    }

    cleanDeviceData();
}

void QhLoggerFileAppender::openDevice()
{
    if (!d->file) {
        d->file = new QFile;
    }

    if (d->file->isOpen()) {
        QString fileName = d->file->fileName();
        d->file->close();
        emit logFileClosed(fileName);
    }

    const auto &params = this->hlogger->loggerConfig();
    if (d->bFirstFile
            && params.bAppend
            && d->filenames.size() > 0) {
        d->bFirstFile = false;
        // 追加模式，打开上一次的文件写入
        QString filename = d->filenames.last();
        QFileInfo ff(filename);
        auto ft = ff.lastModified();

        int timeSpace = QDateTime::currentSecsSinceEpoch() - ft.toSecsSinceEpoch();
        if (params.nAppendTimeMaxSpace <= 0
                || !ft.isValid()
                || timeSpace < params.nAppendTimeMaxSpace * 60) {
            d->file->setFileName(filename);
            if (d->file->open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Text)) {
                return;
            }
        }
    }

    d->bFirstFile = false;
    QString filename = generateFileName(params);
    d->file->setFileName(filename);
    if (!d->file->open(QIODevice::NewOnly | QIODevice::WriteOnly
                      | QIODevice::Text | QIODevice::Append)) {
        // qDebug() << "File Create Error: " << filename;
    } else {
        emit logFileCreated(filename);
    }
    d->filenames.append(filename);

    cleanDeviceData();
}

void QhLoggerFileAppender::closeDevice()
{
    if (d->file) {
        delete d->file;
        d->file = nullptr;
    }
}

void QhLoggerFileAppender::cleanDeviceData()
{
    const auto &params = this->hlogger->loggerConfig();

    // 通过日志文件数量删除日志文件
    int maxNumber = params.nStorageFileMaxNumber;
    if (maxNumber > 0 && d->filenames.size() > maxNumber) {
        int size = d->filenames.size() - maxNumber;
        for (int n = size - 1; n >= 0; --n) {
            QString fileName = d->filenames.at(n);
            bool ret = QFile::remove(d->filenames.takeAt(n));
            if (ret)
                emit logFileDeleted(fileName);
        }
    }

    // 通过日志文件天数量删除日志文件
    int maxDay = params.nStorageFileMaxDay;
    if (maxDay > 0) {
        auto ctm = QDateTime::currentSecsSinceEpoch();

        int size = d->filenames.size();
        for (int n = size - 1; n >= 0; --n) {
            QFileInfo ff(d->filenames.at(n));
            auto ftime = ff.lastModified();
            if (!ftime.isValid())
                continue;
            auto ftm = ftime.toSecsSinceEpoch();
            if ((ftm - ctm) > maxDay * 24 * 60 * 60) {
                QString fileName = d->filenames.at(n);
                QFile::remove(d->filenames.takeAt(n));
                emit logFileDeleted(fileName);
            }
        }
    }
}

void QhLoggerFileAppender::writeData(QhLoggerMessage::Ptr msg)
{
    if (!beforeWriteMsgItem(msg))
        return;

    const auto &params = this->hlogger->loggerConfig();

    int sigMaxCount = params.nSingleFileDataMaxCount;
    int sigMaxSize = params.nSingleFileDataMaxSize;
    int sigMaxTime = params.nNewFileCreateTimeSpace;

    // 满足条件创建新文件
    if (!d->file || !d->file->isOpen() ||
        msg->isForceNewFile() ||
        (sigMaxCount > 0 && d->writeCnt >= sigMaxCount) ||
        (sigMaxTime > 0 && msg->dateTime.toSecsSinceEpoch() - d->lastFirstTime > sigMaxTime) ||
        (sigMaxSize > 0 && d->fileSize > sigMaxSize)) {

        // 创建新文件
        openDevice();

        d->writeCnt = 0;
        d->lastFirstTime = msg->dateTime.toMSecsSinceEpoch();
        d->fileSize = 0;
    }

    if (msg->isForceNewFile())
        return;

    QString data = msgItemFormat(msg);
    data.append("\n");

    d->fileSize += data.size();
    d->writeCnt ++;

    d->file->write(QByteArray::fromStdString(data.toStdString()));
    if (params.bImmediatelyFlush)
        d->file->flush();

    afterWriteMsgItem(msg);
}

QhLoggerFileAppenderPrivate::QhLoggerFileAppenderPrivate(QhLoggerFileAppender *q):
    ptr(q)
{

}

QhLoggerFileAppenderPrivate::~QhLoggerFileAppenderPrivate()
{

}
