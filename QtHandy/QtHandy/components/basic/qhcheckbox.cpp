#include "qhcheckbox.h"
#include "qhcheckbox_p.h"

QhCheckBox::QhCheckBox(QWidget *parent):
    QCheckBox(parent),
    d(new QhCheckBoxPrivate)
{

}

QhCheckBox::QhCheckBox(const QString &text, QWidget *parent):
    QCheckBox(text, parent),
    d(new QhCheckBoxPrivate)
{

}

QhCheckBox::QhCheckBox(bool bLockState, const QString &text, QWidget *parent):
    QCheckBox(text, parent),
    d(new QhCheckBoxPrivate)
{
    setLockState(bLockState);
}

QhCheckBox::~QhCheckBox()
{

}

void QhCheckBox::setLockState(bool b)
{
    d->bLockState = b;
}

bool QhCheckBox::isLockState() const
{
    return d->bLockState;
}

void QhCheckBox::nextCheckState()
{
    if (d->bLockState)
        return;

    QCheckBox::nextCheckState();
}
