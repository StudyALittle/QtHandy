#ifndef QHPUSHBUTTON_P_H
#define QHPUSHBUTTON_P_H

#include <QMap>
#include <QLabel>
#include "qhpushbutton.h"
#include "qhqss.h"

class QhPushButtonPrivate : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhPushButtonPrivate)

public:
    QhPushButtonPrivate(QhPushButton *p);

    QString text;
    QString attachState;

    bool bImageMode = false;
    QWidget *labelIconLeft = nullptr;
    QhLabel *labelText = nullptr;
    QWidget *labelIconRight = nullptr;

    void init(QWidget *labelIconLeft, QWidget *labelIconRight);
    QhQss::PseudoState currentState(QStyleOptionButton &option);

private:
    QhPushButton *p = nullptr;
};

#endif // QHPUSHBUTTON_P_H
