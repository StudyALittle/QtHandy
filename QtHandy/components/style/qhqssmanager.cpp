#include "qhqssmanager.h"
#include "qhfileutil.h"
#include <QDebug>

#define QSS_PATH(FileName) QString(":/QhResource/qss/%1.css").arg(FileName)

QhQssManager::QhQssManager()
{

}

QString QhQssManager::qssFilePath(int type)
{
    switch (type) {
    case FQSS_Button:   { return QSS_PATH("Button"); }
    case FQSS_Text:     { return QSS_PATH("Text"); }
    case FQSS_Edit:     { return QSS_PATH("Edit"); }
    case FQSS_ComboBox: { return QSS_PATH("ComboBox"); }
    case FQSS_DateTime: { return QSS_PATH("DateTime"); }
    case FQSS_Progress: { return QSS_PATH("Progress"); }
    case FQSS_Scroll:   { return QSS_PATH("Scroll"); }
    case FQSS_Popup:    { return QSS_PATH("Popup"); }
    default: return QString();
    }
}

QStringList QhQssManager::qssFilePaths()
{
    return {
        qssFilePath(FQSS_Button),
        qssFilePath(FQSS_Text),
        qssFilePath(FQSS_Edit),
        qssFilePath(FQSS_ComboBox),
        qssFilePath(FQSS_DateTime),
        qssFilePath(FQSS_Progress),
        qssFilePath(FQSS_Scroll),
        qssFilePath(FQSS_Popup)
    };
}

void QhQssManager::setQss(const QStringList &qssFiles)
{
    QString qss;
    for (auto fileName: qssFiles)
        qss.append(QhFileUtil::readFileText(fileName));

    // qDebug() << qss;
    qApp->setStyleSheet(qss);
}

void QhQssManager::setQss(QWidget *w, const QStringList &qssFiles)
{
    QString qss;
    for (auto fileName: qssFiles)
        qss.append(QhFileUtil::readFileText(fileName));
    w->setStyleSheet(qss);
}
