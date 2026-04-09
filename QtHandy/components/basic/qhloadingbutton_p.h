#ifndef QHLOADINGBUTTON_P_H
#define QHLOADINGBUTTON_P_H

#include "qhloadingbutton.h"

class QhLoadingButtonPrivate : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhLoadingButtonPrivate)

public:
    QhLoadingButtonPrivate(QhLoadingButton *p);
    ~QhLoadingButtonPrivate();

    void init();

private:
    QhLoadingButton *p = nullptr;
};

#endif // QHLOADINGBUTTON_P_H
