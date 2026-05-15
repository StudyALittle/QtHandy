#ifndef QHNAVBARPROXY_H
#define QHNAVBARPROXY_H

#include <QWidget>
#include "QH_global.h"

class QhNavbar;
class QhNavbarItem;
class QhNavbarProxyPrivate;

class QTHANDY_EXPORT QhNavbarProxy: public QObject
{
    Q_OBJECT

public:
    QhNavbarProxy(QhNavbar *navbar = nullptr);
    ~QhNavbarProxy();

    QhNavbar *navbar();

signals:
    void clicked(qint64 id);

protected:
    virtual QWidget *createItemWidget(int level, QhNavbarItem *item) = 0;
    virtual void setItemChecked(QhNavbarItem *item, bool bChekced) = 0;
    virtual void setItemName(QhNavbarItem *item, const QString &name);

    virtual QLayout *createLayout(qint64 pid, int level);
    virtual void addLayoutToParent(int level, QLayout *layout, QLayout *parent);
    virtual void addItemWidgetToLayout(qint64 pid, int level, QWidget *widget);
    virtual void addItemWidgetToLayoutEnd(qint64 pid, int level);
    virtual void setLayoutSpace(qint64 pid, int level, int space);

    virtual bool checkedBefore(QhNavbarItem *currentItem, QhNavbarItem *willItem);
    virtual void checkedAfter(QhNavbarItem *lastItem, QhNavbarItem *newItem);

    virtual void childExpand(QhNavbarItem *item, bool bExpand);

protected:
    void setNavbar(QhNavbar *navbar);

private:
    QhNavbarProxyPrivate *d;
    Q_DISABLE_COPY(QhNavbarProxy)
    friend class QhNavbarProxyPrivate;
    friend class QhNavbar;
    friend class QhNavbarItem;
};

#endif // QHNAVBARPROXY_H
