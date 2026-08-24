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

void QhCheckBox::setSelectOutsideText(int b)
{
    d->bSelectOutsideText = b;
}

bool QhCheckBox::isLockState() const
{
    return d->bLockState;
}

bool QhCheckBox::isSelectOutsideText() const
{
    return d->bSelectOutsideText;
}

bool QhCheckBox::hitButton(const QPoint &pos) const
{
    return d->bSelectOutsideText ?
        QAbstractButton::hitButton(pos) : QCheckBox::hitButton(pos);
}

void QhCheckBox::nextCheckState()
{
    if (d->bLockState)
        return;

    QCheckBox::nextCheckState();
}

void QhCheckBox::mouseReleaseEvent(QMouseEvent *event)
{
    QCheckBox::mouseReleaseEvent(event);
}

