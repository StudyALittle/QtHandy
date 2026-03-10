#include "qhpage.h"
#include "qhpage_p.h"
#include <QDateTime>

QhPage::QhPage():
    d(new QhPagePrivate)
{

}

QhPage::~QhPage()
{

}

void QhPage::enterPage()
{
    d->enterTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
}

void QhPage::leavePage()
{
    d->bFirstEnter = false;
    d->leaveTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
}

qint64 QhPage::leavePageInterval() const
{
    return QDateTime::currentDateTime().toMSecsSinceEpoch() - d->leaveTime;
}

qint64 QhPage::enterPageInterval() const
{
    return QDateTime::currentDateTime().toMSecsSinceEpoch() - d->enterTime;
}

bool QhPage::isFirstEnterPage() const
{
    return d->bFirstEnter;
}

void QhPage::setFirstEnterPage(bool b)
{
    d->bFirstEnter = b;
}

QhPagePrivate::QhPagePrivate()
{

}

QhPagePrivate::~QhPagePrivate()
{

}
