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

bool QhLoading::eventFilter(QObject *obj, QEvent *event)
{
    auto ret = QWidget::eventFilter(obj, event);
    if (obj == this->parentWidget() && event->type() == QEvent::Resize) {
        updateSize();
    }
    return ret;
}

QhLoadingPrivate::QhLoadingPrivate(QhLoading *q):
    ptr(q)
{

}

QhLoadingPrivate::~QhLoadingPrivate()
{

}

void QhLoadingPrivate::init()
{
    ptr->parentWidget()->installEventFilter(this);

    timer.setSingleShot(true);
    connect(&timer, &QTimer::timeout, this, [=]() {
        if (state == StateWait) {
            state = StateShow;
            etimer.start();
            ptr->startLoadding();
            ptr->updateSize();
            ptr->show();
        } else if (state == StateClose) {
            ptr->stopLoadding();
            ptr->close();
        }
    });
}
