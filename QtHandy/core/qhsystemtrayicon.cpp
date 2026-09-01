#include "qhsystemtrayicon.h"
#include "qhsystemtrayicon_p.h"

//////////// QhSystemTrayIcon ///////////
QhSystemTrayIcon::QhSystemTrayIcon(QObject *parent):
    QSystemTrayIcon(parent),
    d(new QhSystemTrayIconPrivate(this))
{

}

QhSystemTrayIcon::QhSystemTrayIcon(const QIcon &icon, QObject *parent):
    QSystemTrayIcon(icon, parent),
    d(new QhSystemTrayIconPrivate(this))
{
    d->normalIcon = icon;
}

QhSystemTrayIcon::~QhSystemTrayIcon()
{
    for (auto &item: d->items) {
        item->deleteLater();
    }
}

void QhSystemTrayIcon::setItems(const QList<QhSystemTrayIconItem *> &items)
{
    d->items = items;
    if (items.isEmpty())
        return;

    if (!d->menu) {
        d->menu = new QMenu;
        d->menu->setObjectName("SystemTrayIconMenu");
        this->setContextMenu(d->menu);
    }

    for (auto &item: items) {
        if (item->isSeparator()) {
            d->menu->addSeparator();
            continue;
        }

        auto *action = new QAction(item->name());
        connect(action, &QAction::triggered, this, [this, item]() {
            emit itemClicked(item->id());
        });
        d->menu->addAction(action);
    }
}

void QhSystemTrayIcon::setIcon(const QIcon &icon)
{
    d->normalIcon = icon;
    QSystemTrayIcon::setIcon(icon);
}

void QhSystemTrayIcon::setFlickerIcon(const QIcon &icon)
{
    d->flickerIcon = icon;
}

QhSystemTrayIconItem *QhSystemTrayIcon::item(int id)
{
    for (auto &item: d->items) {
        if (item->id() == id)
            return item;
    }
    return nullptr;
}

QIcon QhSystemTrayIcon::flickerIcon() const
{
    return d->flickerIcon;
}

void QhSystemTrayIcon::startFlickerIcon(int msec)
{
    if (!d->flickerTimer) {
        d->flickerTimer = new QTimer(this);
        connect(d->flickerTimer, &QTimer::timeout, this, [this]() {
            QSystemTrayIcon::setIcon(d->flickerState ? d->flickerIcon : d->normalIcon);
            d->flickerState = !(d->flickerState);
        });
    }
    d->flickerState = true;
    d->flickerTimer->start(msec);
}

void QhSystemTrayIcon::stopFlickerIcon()
{
    if (!d->flickerTimer)
        return;

    d->flickerTimer->stop();
    this->setIcon(d->normalIcon);
}

QhSystemTrayIconPrivate::QhSystemTrayIconPrivate(QhSystemTrayIcon *sysTrayIcon):
    systemTrayIcon(sysTrayIcon)
{

}

QhSystemTrayIconPrivate::~QhSystemTrayIconPrivate()
{

}

//////////// QhSystemTrayIconItem ///////////
QhSystemTrayIconItem::QhSystemTrayIconItem(QObject *parent):
    QObject(parent),
    d(new QhSystemTrayIconItemPrivate())
{

}

QhSystemTrayIconItem::QhSystemTrayIconItem(int id, const QString &name, QObject *parent):
    QObject(parent),
    d(new QhSystemTrayIconItemPrivate())
{
    setId(id);
    setName(name);
}

QhSystemTrayIconItem::QhSystemTrayIconItem(bool bSeparator, QObject *parent):
    QObject(parent),
    d(new QhSystemTrayIconItemPrivate())
{
    setSeparator(bSeparator);
}

QhSystemTrayIconItem::~QhSystemTrayIconItem()
{

}

bool QhSystemTrayIconItem::isSeparator() const
{
    return d->bSeparator;
}

int QhSystemTrayIconItem::id() const
{
    return d->id;
}

QString QhSystemTrayIconItem::name() const
{
    return d->name;
}

QAction *QhSystemTrayIconItem::action()
{
    return d->action;
}

void QhSystemTrayIconItem::setSeparator(bool b)
{
    d->bSeparator = b;
}

void QhSystemTrayIconItem::setId(int id)
{
    d->id = id;
}

void QhSystemTrayIconItem::setName(const QString &name)
{
    d->name = name;
}

void QhSystemTrayIconItem::setAction(QAction *action)
{
    d->action = action;
}

QhSystemTrayIconItemPrivate::QhSystemTrayIconItemPrivate()
{

}

QhSystemTrayIconItemPrivate::~QhSystemTrayIconItemPrivate()
{

}
