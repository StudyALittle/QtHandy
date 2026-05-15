#ifndef QHLOADINGBUTTON_H
#define QHLOADINGBUTTON_H

#include "customized/qhspin.h"
#include "qhpushbutton.h"
#include "QH_global.h"

class QhLoadingButtonPrivate;

class QTHANDY_EXPORT QhLoadingButton : public QhPushButton
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhLoadingButton)

public:
    QhLoadingButton(QWidget *parent = nullptr);
    QhLoadingButton(const QString &text, QWidget *parent = nullptr);
    ~QhLoadingButton();

    QhSpin *spinLeft();

    void start(int ms = 200);
    void stop();
};

#endif // QHLOADINGBUTTON_H
