#include "qhfileutil.h"
#include <QFile>
#include <QDebug>

QString QhFileUtil::generateFileName(const QString &baseName, const QString &suffix)
{
    QString format, format2;
    if (suffix.isEmpty()) {
        format = "%1%2";
        format2 = "%1(%2)%3";
    } else {
        format = "%1.%2";
        format2 = "%1(%2).%3";
    }

    QString fileName = format.arg(baseName, suffix);
    int i = 1;
    while (QFile::exists(fileName)) {
        fileName = format2.arg(baseName).arg(i).arg(suffix);
        i++;
    }
    return fileName;
}

QString QhFileUtil::readFileText(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "File \"" << fileName << "\" open error: " << file.errorString();
        return QString();
    }

    return QString::fromStdString(file.readAll().toStdString());
}
