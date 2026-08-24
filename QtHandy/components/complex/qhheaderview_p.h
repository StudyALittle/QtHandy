#ifndef QHHEADERVIEW_P_H
#define QHHEADERVIEW_P_H

#include "qhheaderview.h"
#include "qhheaderviewitem.h"

class QhHeaderViewPrivate : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhHeaderViewPrivate)

public:
    QhHeaderViewPrivate(QhHeaderView *hview);
    ~QhHeaderViewPrivate();

    void init();

    QhHeaderView *headerView;
    QMap<int, QhHeaderViewItem *> items;
};

class QhHeaderViewItemPrivate : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhHeaderViewItemPrivate)

public:
    QhHeaderViewItemPrivate(QhHeaderViewItem *hviewitem);
    ~QhHeaderViewItemPrivate();

    void init(int wtype);

    QhHeaderViewItem *headerViewItem;
    int wType;

    QString name;
    int index = -1;
    QCheckBox *checkBox = nullptr;
};

#endif // QHHEADERVIEW_P_H
