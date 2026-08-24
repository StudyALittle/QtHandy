#include "qhheaderviewitem.h"
#include "qhheaderview_p.h"
#include <QHBoxLayout>

QhHeaderViewItem::QhHeaderViewItem(int wtype, QWidget *parent) : QWidget(parent), d(new QhHeaderViewItemPrivate(this))
{
    d->init(wtype);
}

QhHeaderViewItem::~QhHeaderViewItem()
{
}

void QhHeaderViewItem::setName(const QString &name)
{
    d->name = name;
}

QCheckBox *QhHeaderViewItem::checkBox()
{
    return d->checkBox;
}

void QhHeaderViewItem::setIndex(int index)
{
    d->index = index;
}

QhHeaderViewItemPrivate::QhHeaderViewItemPrivate(QhHeaderViewItem *hviewitem) : headerViewItem(hviewitem)
{
}

QhHeaderViewItemPrivate::~QhHeaderViewItemPrivate()
{
}

void QhHeaderViewItemPrivate::init(int wtype)
{
    this->wType = wtype;
    switch (wType) {
    case QhHeaderViewItem::WT_CheckBox: {
        checkBox = new QCheckBox;
        auto *hly = new QHBoxLayout(headerViewItem);
        hly->addStretch(1);
        hly->addWidget(checkBox);
        hly->addStretch(1);
        hly->setSpacing(0);
        hly->setContentsMargins(0, 0, 0, 0);
        connect(checkBox, &QCheckBox::stateChanged, this,
            [this](int state) { emit headerViewItem->checkStateChanged(index, state); });
        break;
    }
    default:
        break;
    }
}
