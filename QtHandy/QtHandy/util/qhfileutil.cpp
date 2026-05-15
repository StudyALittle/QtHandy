#include "qhfileutil.h"
#include <QFile>
#include <QDebug>

QString QhFileUtil::readFileText(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "File \"" << fileName << "\" open error: " << file.errorString();
        return QString();
    }

    return QString::fromStdString(file.readAll().toStdString());
}
