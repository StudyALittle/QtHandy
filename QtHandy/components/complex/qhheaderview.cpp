#include "qhheaderview.h"
#include "qhheaderview_p.h"
#include "qhheaderviewitem.h"

QhHeaderView::QhHeaderView(Qt::Orientation orientation, QWidget *parent) :
    QHeaderView(orientation, parent), d(new QhHeaderViewPrivate(this))
{
    d->init();
}

QhHeaderView::~QhHeaderView()
{
    clearItems(false);
}

QhHeaderViewItem *QhHeaderView::itemAt(int index)
{
    if (d->items.contains(index))
        return d->items.value(index);
    return nullptr;
}

void QhHeaderView::setItem(int index, QhHeaderViewItem *item)
{
    if (d->items.contains(index))
        delete d->items.take(index);
    d->items.insert(index, item);
    this->update();
}

void QhHeaderView::removeItem(int index)
{
    auto *item = takeItem(index);
    if (item) {
        delete item;
    }
}

QhHeaderViewItem *QhHeaderView::takeItem(int index)
{
    if (d->items.contains(index)) {
        auto *item = d->items.take(index);
        this->update();
        return item;
    }
    return nullptr;
}

void QhHeaderView::clearItems(bool bUpdate)
{
    for (auto it = d->items.begin(); it != d->items.end(); ++it) {
        delete it.value();
    }
    d->items.clear();
    if (bUpdate)
        this->update();
}

void QhHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    if (d->items.contains(logicalIndex)) {
        auto *item = d->items.value(logicalIndex);
        // item->setName(widget->name() /*model->headerData(logicalIndex, Qt::Horizontal).toString()*/);
        item->setIndex(logicalIndex);
        if (item->parent() != this->viewport())
            item->setParent(this->viewport());
        item->setGeometry(rect);
        item->show();
        return;
    }

    QHeaderView::paintSection(painter, rect, logicalIndex);
}

void QhHeaderView::mouseMoveEvent(QMouseEvent *e)
{
    QHeaderView::mouseMoveEvent(e);
    if (!d->items.isEmpty())
        this->update();
}

QhHeaderViewPrivate::QhHeaderViewPrivate(QhHeaderView *hview) : headerView(hview)
{
}

QhHeaderViewPrivate::~QhHeaderViewPrivate()
{
}

void QhHeaderViewPrivate::init()
{
}
