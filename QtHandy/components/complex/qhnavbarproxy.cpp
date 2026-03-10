#include "qhnavbarproxy.h"
#include "qhnavbar_p.h"
#include "qhnavbar.h"
#include "qhnavbaritem.h"
#include <QBoxLayout>

QhNavbarProxy::QhNavbarProxy(QhNavbar *navbar):
    d(new QhNavbarProxyPrivate(this))
{
    setNavbar(navbar);
}

QhNavbarProxy::~QhNavbarProxy()
{
    delete d;
}

QhNavbar *QhNavbarProxy::navbar()
{
    return d->navbar;
}

void QhNavbarProxy::setItemName(QhNavbarItem *item, const QString &name)
{
    Q_UNUSED(item)
    Q_UNUSED(name)
}

QLayout *QhNavbarProxy::createLayout(qint64 pid, int level)
{
    Q_UNUSED(pid)

    QBoxLayout *layout = static_cast<QBoxLayout*>(navbar()
        ->getLayout(QhNavbarItem::INVALIDID, level));
    if (!layout) {
        switch (navbar()->direction()) {
        case QhNavbar::Vertical:
            layout = new QVBoxLayout;
            if (level > 1) {
                layout->setContentsMargins(12, 0, 0, 0);
            }
            break;
        case QhNavbar::Horizontal:
            layout = new QHBoxLayout;
            break;
        }
    }
    return layout;
}

void QhNavbarProxy::addLayoutToParent(int level, QLayout *layout, QLayout *parent)
{
    Q_UNUSED(level)

    if (!layout || !parent || layout == parent)
        return;

    static_cast<QBoxLayout*>(parent)->addLayout(layout);
}

void QhNavbarProxy::addItemWidgetToLayout(qint64 pid, int level, QWidget *widget)
{
    Q_UNUSED(pid)
    Q_UNUSED(level)

    auto *layout = static_cast<QBoxLayout*>(navbar()->getLayout(pid, level));
    if (layout)
        layout->addWidget(widget);
}

void QhNavbarProxy::addItemWidgetToLayoutEnd(qint64 pid, int level)
{
    Q_UNUSED(pid)

    if (level != 1)
        return;

    auto *layout = static_cast<QBoxLayout*>(navbar()->getLayout(pid, level));
    switch (navbar()->position()) {
    case QhNavbar::Top:
    case QhNavbar::Left: {
        layout->insertStretch(navbar()->itemCount(), 1);
        break;
    }
    case QhNavbar::Bottom:
    case QhNavbar::Right:
        layout->insertStretch(0, 1);
        break;
    default:
        break;
    }
}

void QhNavbarProxy::setLayoutSpace(qint64 pid, int level, int space)
{
    Q_UNUSED(pid)

    if (level != 1)
        return;

    auto *layout = static_cast<QBoxLayout*>(navbar()->getLayout(pid, level));
    if (layout)
        layout->setSpacing(space);
}

bool QhNavbarProxy::checkedBefore(QhNavbarItem *currentItem, QhNavbarItem *willItem)
{
    Q_UNUSED(currentItem)

    // 存在子项的，不能被选中，只能展开、收起
    if (willItem && willItem->childItems().size() > 0) {
        navbar()->setItemChildExpand(willItem, !willItem->isChildExpand());
        return false;
    }
    return true;
}

void QhNavbarProxy::checkedAfter(QhNavbarItem *lastItem, QhNavbarItem *newItem)
{
    Q_UNUSED(lastItem)
    Q_UNUSED(newItem)
}

void QhNavbarProxy::childExpand(QhNavbarItem *item, bool bExpand)
{
    Q_UNUSED(item)
    Q_UNUSED(bExpand)
}

void QhNavbarProxy::setNavbar(QhNavbar *navbar)
{
    d->navbar = navbar;
}
