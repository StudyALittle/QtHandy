#ifndef QHQSSMANAGER_H
#define QHQSSMANAGER_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QApplication>
#include <QWidget>
#include "QH_global.h"

class QTHANDY_EXPORT QhQssManager
{
public:
    enum QssFileType
    {
        FQSS_Button = 0,
        FQSS_Text,
        FQSS_Edit,
        FQSS_ComboBox,
        FQSS_DateTime,
        FQSS_Progress,
        FQSS_Scroll,
        FQSS_Popup,
        FQSS_Custom = 100
    };

    QhQssManager();

    virtual QString qssFilePath(int type);
    virtual QStringList qssFilePaths();

    static void setQss(const QStringList &qssFiles);
    static void setQss(QWidget *w, const QStringList &qssFiles);
};

#endif // QHQSSMANAGER_H
