#ifndef QHFLOWLAYOUT_P_H
#define QHFLOWLAYOUT_P_H

#include "qhflowlayout.h"

class QhFlowLayoutPrivate : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhFlowLayoutPrivate)

public:
    QhFlowLayoutPrivate();
    ~QhFlowLayoutPrivate();

    QList<QLayoutItem *> items;
    int hSpace;
    int vSpace;
};

#endif // QHFLOWLAYOUT_P_H
