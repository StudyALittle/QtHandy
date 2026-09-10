#ifndef QHCUSTOMMENU_P_H
#define QHCUSTOMMENU_P_H

#include <QList>
#include <QPair>
#include <QVBoxLayout>
#include "qhcustommenu.h"

class QhCustomMenuPrivate: public QObject
{
    Q_OBJECT

public:
    QhCustomMenuPrivate(QhCustomMenu *pCustomMenu);
    ~QhCustomMenuPrivate();

    void init();

    QhCustomMenu *customMenu;
    QVBoxLayout *layout;

    QList<QPair<QAbstractButton*, int> > buttons;
};

#endif // QHCUSTOMMENU_P_H
