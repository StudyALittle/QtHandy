#ifndef QHPAGE_P_H
#define QHPAGE_P_H

#include "qhpage.h"

class QhPagePrivate: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhPagePrivate)

public:
    explicit QhPagePrivate();
    ~QhPagePrivate();

    bool bFirstEnter = true;
    qint64 enterTime = 0;
    qint64 leaveTime = 0;
};

#endif // QHPAGE_P_H
