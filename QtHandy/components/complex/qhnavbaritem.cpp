#include "qhnavbaritem.h"
#include "qhnavbar_p.h"
#include "qhnavbarproxy.h"

QhNavbarItem::QhNavbarItem(qint64 id, QObject *parent):
    QObject(parent),
    d(new QhNavbarItemPrivate(this))
{
    d->id = id;
}

QhNavbarItem::QhNavbarItem(qint64 id, const QString &name, QObject *parent):
    QObject(parent),
    d(new QhNavbarItemPrivate(this))
{
    d->id = id;
    setName(name);
}

QhNavbarItem::QhNavbarItem(qint64 id, const QString &name,
    const QList<QhNavbarItem*> &childs,
    const QVariant &customParam, QObject *parent):
    QObject(parent),
    d(new QhNavbarItemPrivate(this))
{
    d->id = id;
    d->childItems = childs;
    d->customParam = customParam;
    setName(name);
}

QhNavbarItem::~QhNavbarItem()
{
    delete d;
}

qint64 QhNavbarItem::id() const { return d->id; }

QString QhNavbarItem::name() const { return d->name; }

QList<QhNavbarItem*> QhNavbarItem::childItems() const { return d->childItems; }

QVariant QhNavbarItem::customParam() const { return d->customParam; }

bool QhNavbarItem::isChildExpand() const { return d->bChildExpand; }

bool QhNavbarItem::isChecked() const { return d->bChecked; }

QWidget *QhNavbarItem::widget() const { return d->widget;  }

void QhNavbarItem::setName(const QString &name)
{
    d->name = name;
    if (d->navbar && d->navbar->navbarProxy())
        d->navbar->navbarProxy()->setItemName(this, name);
}

void QhNavbarItem::setChecked(bool b)
{
    d->bChecked = b;
    if (d->navbar && d->navbar->navbarProxy())
        d->navbar->navbarProxy()->setItemChecked(this, b);
}

void QhNavbarItem::setChildExpand(bool b)
{
    d->bChildExpand = b;
}

void QhNavbarItem::setWidget(QWidget *w)
{
    d->widget = w;
}

void QhNavbarItem::setNavbar(QhNavbar *navbar)
{
    d->navbar = navbar;
}




