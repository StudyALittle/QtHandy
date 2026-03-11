#include "qhpagemanager.h"
#include "qhpagemanager_p.h"
#include "qhpage.h"

QhPageManager::QhPageManager(QStackedWidget *stackedWidget):
    d(new QhPageManagerPrivate)
{
    setStackedWidget(stackedWidget);
}

QhPageManager::~QhPageManager()
{

}

QStackedWidget *QhPageManager::stackedWidget() const
{
    return d->stackedWidget;
}

void QhPageManager::setStackedWidget(QStackedWidget *sw)
{
    d->stackedWidget = sw;
}

QWidget *QhPageManager::enterPage(qint64 id)
{
    auto *page = getPage(id);
    if (!page) {
        page = createPage(id);
        if (page) {
            insertPage(id, page);
        }
    }

    if (!page)
        return nullptr;

    if (d->lastWidget) {
        leavePage(pageID(d->lastWidget));
    }

    d->lastWidget = page;
    if (d->stackedWidget)
        d->stackedWidget->setCurrentWidget(page);
    dynamic_cast<QhPage*>(page)->enterPage();

    return page;
}

void QhPageManager::leavePage(qint64 id)
{
    auto *page = getPage(id);
    if (!page)
        return;

    dynamic_cast<QhPage*>(page)->leavePage();
}

QWidget *QhPageManager::getPage(qint64 id)
{
    if (d->pages.contains(id))
        return d->pages.value(id);
    return nullptr;
}

qint64 QhPageManager::pageID(QWidget *w)
{
    for (auto it = d->pages.begin(); it != d->pages.end(); ++it) {
        if (it.value() == w)
            return it.key();
    }
    return -1;
}

void QhPageManager::insertPage(qint64 id, QWidget *page)
{
    if (d->stackedWidget)
        d->stackedWidget->addWidget(page);
    d->pages.insert(id, page);
}

QWidget *QhPageManager::takePage(qint64 id)
{
    if (d->pages.contains(id)) {
        auto *page = d->pages.take(id);
        if (d->stackedWidget)
            d->stackedWidget->removeWidget(page);
        return page;
    }
    return nullptr;
}

QhPageManagerPrivate::QhPageManagerPrivate()
{

}

QhPageManagerPrivate::~QhPageManagerPrivate()
{

}
