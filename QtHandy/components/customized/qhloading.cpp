#include "qhloading.h"
#include "qhloading_p.h"
#include <QVBoxLayout>
#include <QDateTime>
#include <QEvent>
#include <QResizeEvent>

QhLoading::QhLoading(QWidget *parent):
    QWidget(parent),
    d(new QhLoadingPrivate(this))
{
    d->init();
}

QhLoading::~QhLoading()
{

}

void QhLoading::showLoadding(int nWaitShowTimeSpace, int nMinShowTimeSpace)
{
    d->nWaitShowTimeSpace = nWaitShowTimeSpace;
    d->nMinShowTimeSpace = nMinShowTimeSpace;
    d->state = QhLoadingPrivate::StateWait;
    d->timer.start(nWaitShowTimeSpace);
}

void QhLoading::closeLoadding()
{
    if (d->state == QhLoadingPrivate::StateWait) {
        this->stopLoadding();
        d->timer.stop();
        close();
        return;
    }

    if (d->state == QhLoadingPrivate::StateShow) {
        auto space = d->etimer.elapsed();
        d->state = QhLoadingPrivate::StateClose;
        if (space > d->nMinShowTimeSpace) {
            this->stopLoadding();
            close();
            return;
        }

        d->timer.start(d->nMinShowTimeSpace - space);
        return;
    }

    // StateClose
    this->stopLoadding();
    d->timer.stop();
    close();
}

void QhLoading::updateSize()
{
    this->move(0, 0);
    this->resize(this->parentWidget()->size());
}

void QhLoading::setParent(QWidget *parent)
{
    if (parent && (d->installEventWidget == nullptr || d->installEventWidget != parent)) {
        parent->installEventFilter(this);
    }
    QWidget::setParent(parent);
}

QhLoadingPrivate::QhLoadingPrivate(QhLoading *loading):
    loading(loading)
{

}

QhLoadingPrivate::~QhLoadingPrivate()
{

}

void QhLoadingPrivate::init()
{
    installEventWidget = loading->parentWidget();
    if (installEventWidget)
        installEventWidget->installEventFilter(this);

    timer.setSingleShot(true);
    connect(&timer, &QTimer::timeout, this, [=]() {
        if (state == StateWait) {
            state = StateShow;
            etimer.start();
            loading->startLoadding();
            loading->updateSize();
            loading->show();
        } else if (state == StateClose) {
            loading->stopLoadding();
            loading->close();
        }
    });
}

bool QhLoadingPrivate::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == loading->parentWidget() && event->type() == QEvent::Resize) {
        loading->updateSize();
    }
    return QObject::eventFilter(obj, event);
}
