#include "qhtablewidgetitem.h"
#include "qhtablewidget_p.h"

QhTableWidgetItem::QhTableWidgetItem() : d(new QhTableWidgetItemPrivate)
{
}

QhTableWidgetItem::QhTableWidgetItem(const QString &name, int size, bool bFillRemaiSize) :
    d(new QhTableWidgetItemPrivate)
{
    d->name = name;
    d->size = size;
    d->bFillRemaiSize = bFillRemaiSize;
}

QhTableWidgetItem::QhTableWidgetItem(const QString &name, int size, QTableWidgetItem *item, bool bFillRemaiSize) :
    d(new QhTableWidgetItemPrivate)
{
    d->name = name;
    d->size = size;
    d->bFillRemaiSize = bFillRemaiSize;
    d->item = item;
}

QhTableWidgetItem::QhTableWidgetItem(const QString &name, int size, QhHeaderViewItem *item, bool bFillRemaiSize) :
    d(new QhTableWidgetItemPrivate)
{
    d->name = name;
    d->size = size;
    d->bFillRemaiSize = bFillRemaiSize;
    d->hitem = item;
}

QhTableWidgetItem::~QhTableWidgetItem()
{
}

int QhTableWidgetItem::index() const
{
    return d->index;
}

QString QhTableWidgetItem::name() const
{
    return d->name;
}

int QhTableWidgetItem::size() const
{
    return d->size;
}

bool QhTableWidgetItem::isFillRemaiSize() const
{
    return d->bFillRemaiSize;
}

QTableWidgetItem *QhTableWidgetItem::item() const
{
    return d->item;
}

QhHeaderViewItem *QhTableWidgetItem::hitem() const
{
    return d->hitem;
}

void QhTableWidgetItem::setIndex(int index)
{
    d->index = index;
}
