#ifndef QHPAGEMANAGER_P_H
#define QHPAGEMANAGER_P_H

#include <QMap>
#include "qhpagemanager.h"

class QhPageManagerPrivate: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhPageManagerPrivate)

public:
    explicit QhPageManagerPrivate();
    ~QhPageManagerPrivate();

    QStackedWidget *stackedWidget = nullptr;
    QWidget *lastWidget = nullptr;
    QMap<qint64, QWidget*> pages;
};

#endif // QHPAGEMANAGER_P_H
