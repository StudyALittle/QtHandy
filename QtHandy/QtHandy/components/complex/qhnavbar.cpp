#include "qhnavbar.h"
#include "qhnavbar_p.h"
#include <QBoxLayout>

QhNavbar::QhNavbar(int direction, int position,
        QhNavbarProxy *proxy, QWidget *parent):
    QWidget(parent),
    d(new QhNavbarPrivate(this))
{
    d->direction = direction;
    d->position = position;
    d->navbarProxy = proxy;
    d->navbarProxy->setNavbar(this);
    connect(proxy, &QhNavbarProxy::clicked, this, &QhNavbar::onItemClicked);
}

QhNavbar::~QhNavbar()
{
    delete d;
}

QhNavbarProxy *QhNavbar::navbarProxy() const
{
    return d->navbarProxy;
}

int QhNavbar::direction() const
{
    return d->direction;
}

int QhNavbar::position() const
{
    return d->position;
}

QList<QhNavbarItem*> QhNavbar::items() const
{
    return d->items;
}

QhNavbarItem *QhNavbar::item(qint64 id) const
{
    return item(d->items, id);
}

QhNavbarItem *QhNavbar::checkedItem() const
{
    return checkedItem(d->items);
}

QhNavbarItem *QhNavbar::lastCheckedItem() const
{
    return d->lastCheckedItem;
}

QhNavbarItem* QhNavbar::parentItem(qint64 id) const
{
    return parentItem(d->items, id);
}

bool QhNavbar::isChildChecked(QhNavbarItem *item) const
{
    return isExistChecked(item->childItems());
}

bool QhNavbar::isChildExpand(QhNavbarItem *item) const
{
    foreach (auto *citem, item->childItems()) {
        if (citem->widget() && citem->widget()->isVisible())
            return true;
    }
    return false;
}

int QhNavbar::itemLevel(QhNavbarItem *item) const
{
    return itemLevel(d->items, item->id(), 1);
}

int QhNavbar::itemSpace(qint64 pid, int level) const
{
    QString key = QString("%1_%2").arg(pid).arg(level);
    return d->layoutSpaces.value(key);
}

void QhNavbar::setItems(const QList<QhNavbarItem*> &items)
{
    d->items = items;
    setItemsToLayout(items);
}

void QhNavbar::setChecked(qint64 id, bool bExpand)
{
    auto *ptr = item(id);
    if (!ptr)
        return;

    // 之前的选中取消
    auto *lastChecked = checkedItem();
    if (lastChecked) {
        lastChecked->setChecked(false);
    }

    // 设置新的选中
    ptr->setChecked(true);
    if (bExpand)
        setItemParentExpand(ptr, true);
}

void QhNavbar::setItemSpace(int space, qint64 pid, int level)
{
    QString key = QString("%1_%2").arg(pid).arg(level);
    d->layoutSpaces.insert(key, space);
    d->navbarProxy->setLayoutSpace(pid, level, space);
}

void QhNavbar::setItemChildExpand(QhNavbarItem *item, bool bExpand)
{
    item->setChildExpand(bExpand);
    d->navbarProxy->childExpand(item, item->isChildExpand());
    foreach (auto *child, item->childItems()) {
        auto *w = child->widget();
        if (!w)
            continue;
        w->setVisible(bExpand);
    }
}

void QhNavbar::setItemParentExpand(QhNavbarItem *item, bool bExpand)
{
    auto *pitem = parentItem(item->id());
    if (pitem) {
        setItemParentExpand(pitem, bExpand);
        setItemChildExpand(pitem, bExpand);
    }
}

QhNavbarItem *QhNavbar::item(const QList<QhNavbarItem*> &items, qint64 id) const
{
    foreach (auto *_item, items) {
        if (_item->id() == id)
            return _item;

        auto *child = item(_item->childItems(), id);
        if (child)
            return child;
    }
    return nullptr;
}

QhNavbarItem *QhNavbar::checkedItem(const QList<QhNavbarItem*> &items) const
{
    foreach (auto *item, items) {
        if (item->isChecked())
            return item;

        auto *child = checkedItem(item->childItems());
        if (child)
            return child;
    }
    return nullptr;
}

QhNavbarItem *QhNavbar::parentItem(const QList<QhNavbarItem*> &items, qint64 id) const
{
    foreach (auto *item, items) {
        foreach (auto *citem, item->childItems()) {
            if (citem->id() == id)
                return item;
        }

        auto *child = parentItem(item->childItems(), id);
        if (child)
            return child;
    }
    return nullptr;
}

bool QhNavbar::isExistChecked(const QList<QhNavbarItem*> &items) const
{
    foreach (auto *item, items) {
        if (item->isChecked() ||
                isExistChecked(item->childItems()))
            return true;
    }
    return false;
}

int QhNavbar::itemLevel(const QList<QhNavbarItem*> &items, qint64 id, int level) const
{
    foreach (auto *item, items) {
        if (item->id() == id)
            return level;

        auto fdlv = itemLevel(item->childItems(), id, level + 1);
        if (fdlv > 0)
            return fdlv;
    }
    return 0;
}

int QhNavbar::itemCount() const
{
    int cnt = 0;
    itemCount(d->items, cnt);
    return cnt;
}

void QhNavbar::itemCount(const QList<QhNavbarItem*> &items, int &cnt) const
{
    foreach (auto *item, items) {
        ++cnt;
        itemCount(item->childItems(), cnt);
    }
}

QLayout *QhNavbar::getLayout(qint64 pid, int level)
{
    QString key = QString("%1_%2").arg(pid).arg(level);
    if (d->layouts.contains(key))
        return d->layouts.value(key);

    return nullptr;
}

void QhNavbar::recordLayout(qint64 pid, int level, QLayout *layout)
{
    QString key = QString("%1_%2").arg(pid).arg(level);
    d->layouts.insert(key, layout);
}

void QhNavbar::removeLayout(qint64 pid, int level)
{
    QString key = QString("%1_%2").arg(pid).arg(level);
    if (d->layouts.contains(key))
        d->layouts.remove(key);
}

void QhNavbar::setItemsToLayout(const QList<QhNavbarItem *> &items)
{
    auto *layout = static_cast<QBoxLayout*>(this->layout());
    if (layout) {
        delete layout;
        this->setLayout(nullptr);
    }

    setItemsToLayout(d->items, QhNavbarItem::INVALIDID, 1);
}

void QhNavbar::setItemsToLayout(const QList<QhNavbarItem *> &items, qint64 pid, int level)
{
    auto *layout = d->navbarProxy->createLayout(pid, level);
    if (level == 1) {
        layout->setContentsMargins(0, 0, 0 , 0);
        this->setLayout(layout);
    } else if (level == 2) {
        d->navbarProxy->addLayoutToParent(level, layout,
            getLayout(QhNavbarItem::INVALIDID, level - 1));
    } else {
        auto *pitem = parentItem(d->items, pid);
        d->navbarProxy->addLayoutToParent(level, layout,
            getLayout(pitem->id(), level - 1));
    }
    recordLayout(pid, level, layout);

    for (int n = 0; n < items.size(); ++n) {
        auto *item = items.at(n);
        item->setParent(this);
        item->setNavbar(this);

        // create item
        auto *widget = d->navbarProxy->createItemWidget(level, item);
        item->setWidget(widget);
        item->setChecked(false);
        d->navbarProxy->addItemWidgetToLayout(pid, level, widget);

        // Recursive creation
        setItemsToLayout(item->childItems(), item->id(), level + 1);

        setItemChildExpand(item, item->isChildExpand());
    }
    setItemSpace(itemSpace(pid, level), pid, level);
    d->navbarProxy->addItemWidgetToLayoutEnd(pid, level);
}

void QhNavbar::onItemClicked(qint64 id)
{
    if (d->navbarProxy->checkedBefore(checkedItem(), item(id))) {
        d->lastCheckedItem = checkedItem();
        setChecked(id);
        emit itemChecked(id);
    }
}
