#ifndef QHPUSHBUTTON_P_H
#define QHPUSHBUTTON_P_H

#include <QMap>
#include "qhpushbutton.h"
#include "qhqss.h"

class QhPushButtonPrivate: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhPushButtonPrivate)

public:
    explicit QhPushButtonPrivate(QhPushButton *p);

    /// Is it image mode.
    /// When it is false, all the following parameters are invalid
    bool bImageMode = false;

    /// Qss style parse
    QhQss *handyQss = nullptr;

    /// text
    QString text;

    void init();
    void qssReloaded();

    QhQss::PseudoState currentState(QStyleOptionButton &option);
    void resize(QStyleOptionButton &option);
    void draw(QPainter *p, QStyleOptionButton &option);

private:
    QhPushButton *ptr;
};

#endif // QHPUSHBUTTON_P_H
