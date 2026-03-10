#ifndef QHFLOATING_P_H
#define QHFLOATING_P_H

#include "qhfloating.h"

class QhFloatingPrivate: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhFloatingPrivate)

public:
    explicit QhFloatingPrivate();
    ~QhFloatingPrivate();

    bool bCloseAtFocusOut = true;
    QPoint pos;
    QVector<QWidget*> ignoreWidgets;
};

#endif // QHFLOATING_P_H
