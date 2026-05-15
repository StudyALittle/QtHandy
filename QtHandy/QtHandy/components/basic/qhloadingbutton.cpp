#include "qhloadingbutton.h"
#include "qhloadingbutton_p.h"
#include <QHBoxLayout>

QhLoadingButton::QhLoadingButton(QWidget *parent) :
    QhPushButton(new QhSpin, new QhSpin, QString(), parent), d(new QhLoadingButtonPrivate(this))
{
    d->init();
}

QhLoadingButton::QhLoadingButton(const QString &text, QWidget *parent) :
    QhPushButton(new QhSpin, new QhSpin, text, parent), d(new QhLoadingButtonPrivate(this))
{
    d->init();
}

QhLoadingButton::~QhLoadingButton()
{
}

QhSpin *QhLoadingButton::spinLeft()
{
    return static_cast<QhSpin *>(this->iconLeft());
}

void QhLoadingButton::start(int ms)
{
    this->setImageMode(true);
    this->iconRight()->setVisible(false);
    spinLeft()->start(ms);
}

void QhLoadingButton::stop()
{
    this->setImageMode(false);
    spinLeft()->stop();
}

QhLoadingButtonPrivate::QhLoadingButtonPrivate(QhLoadingButton *p) : p(p)
{
}

QhLoadingButtonPrivate::~QhLoadingButtonPrivate()
{
}

void QhLoadingButtonPrivate::init()
{
    auto *hy = static_cast<QHBoxLayout *>(p->layout());
    hy->setStretch(1, 0);
    hy->insertStretch(0, 1);
    hy->addStretch(1);

    p->spinLeft()->setStyle(QhSpin::StyleDotSS);
    p->spinLeft()->setFixedSize(12, 12);
    p->spinLeft()->setMinWidth(4);
    p->spinLeft()->setWidthRatio(0.2f);
    p->textLabel()->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
}
