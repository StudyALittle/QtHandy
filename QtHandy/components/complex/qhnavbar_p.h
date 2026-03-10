#ifndef QHNAVBAR_P_H
#define QHNAVBAR_P_H

#include "qhnavbar.h"
#include "qhnavbaritem.h"
#include "qhnavbarproxy.h"

class QhNavbarPrivate: public QObject
{
    Q_OBJECT

    Q_DISABLE_COPY(QhNavbarPrivate)
    Q_DECLARE_PUBLIC(QhNavbar)

public:
    QhNavbarPrivate(QhNavbar *q):
        q_ptr(q) {}

    QList<QhNavbarItem*> items;

    QhNavbarProxy *navbarProxy = nullptr;
    QhNavbarItem *lastCheckedItem = nullptr;

    QMap<QString, QLayout*> layouts;
    QMap<QString, int> layoutSpaces;

    int direction;
    int position;

private:
    QhNavbar *const q_ptr;
};

class QhNavbarProxyPrivate: public QObject
{
    Q_OBJECT

    Q_DISABLE_COPY(QhNavbarProxyPrivate)
    Q_DECLARE_PUBLIC(QhNavbarProxy)

public:
    QhNavbarProxyPrivate(QhNavbarProxy *q):
        q_ptr(q) {}

    QhNavbar *navbar = nullptr;

private:
    QhNavbarProxy *const q_ptr;
};

class QhNavbarItemPrivate: public QObject
{
    Q_OBJECT

    Q_DISABLE_COPY(QhNavbarItemPrivate)
    Q_DECLARE_PUBLIC(QhNavbarItem)

public:
    QhNavbarItemPrivate(QhNavbarItem *q):
        q_ptr(q) {}

    qint64 id;
    QString name;
    QList<QhNavbarItem*> childItems;
    QVariant customParam;

    // The window corresponding to the navigation bar(button)
    QWidget *widget = nullptr;

    bool bChecked = false;
    bool bChildExpand = false;

    QhNavbar *navbar = nullptr;

private:
    QhNavbarItem *const q_ptr;
};

#endif // QHNAVBAR_P_H
