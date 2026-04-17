#include "qhpushbutton.h"
#include "qhpushbutton_p.h"
#include <QStyleOptionButton>
#include <QPainter>
#include <QDebug>
#include <QHBoxLayout>
#include "qhwidgetutil.h"

QhPushButton::QhPushButton(QWidget *parent) : QPushButton(parent), d(new QhPushButtonPrivate(this))
{
    d->init(new QhLabel, new QhLabel);
}

QhPushButton::QhPushButton(const QString &text, QWidget *parent) :
    QPushButton(QString(), parent), d(new QhPushButtonPrivate(this))
{
    d->init(new QhLabel, new QhLabel);
    setText(text);
}

QhPushButton::QhPushButton(QWidget *iconLeft, QWidget *iconRight, const QString &text, QWidget *parent) :
    QPushButton(QString(), parent), d(new QhPushButtonPrivate(this))
{
    d->init(iconLeft, iconRight);
    setText(text);
}

QhPushButton::~QhPushButton()
{
}

bool QhPushButton::isImageMode() const
{
    return d->bImageMode;
}

QString QhPushButton::text() const
{
    return d->labelText->text();
}

QhLabel *QhPushButton::textLabel() const
{
    return d->labelText;
}

QWidget *QhPushButton::iconLeft() const
{
    return d->labelIconLeft;
}

QWidget *QhPushButton::iconRight() const
{
    return d->labelIconRight;
}

void QhPushButton::setImageMode(bool b)
{
    d->bImageMode = b;
    if (d->labelIconLeft)
        d->labelIconLeft->setVisible(b);
    if (d->labelText)
        d->labelText->setVisible(b);
    if (d->labelIconRight)
        d->labelIconRight->setVisible(b);
    QPushButton::setText(b ? QString() : (d->labelText ? d->labelText->text() : QString()));
}

void QhPushButton::setText(const QString &text)
{
    if (d->labelText)
        d->labelText->setText(text);

    if (!d->bImageMode) {
        QPushButton::setText(text);
    } else {
        this->adjustSize();
        this->update();
    }
}

// bool QhPushButton::setProperty(const char *name, const QVariant &value)
//{
//    auto ret = QPushButton::setProperty(name, value);
//    if (d->labelText) {
//        d->labelText->setProperty(name, value);
//        QhWidgetUtil::updateQssStyle(d->labelText);
//    }
//    if (d->labelIconLeft) {
//        d->labelIconLeft->setProperty(name, value);
//        QhWidgetUtil::updateQssStyle(d->labelIconLeft);
//    }
//    if (d->labelIconRight) {
//        d->labelIconRight->setProperty(name, value);
//        QhWidgetUtil::updateQssStyle(d->labelIconRight);
//    }
//    QhWidgetUtil::updateQssStyle(this);
//    return ret;
//}

void QhPushButton::attachPropertyState(const QString &value)
{
    d->attachState = value;
    this->setProperty("qstate", value);
    QhWidgetUtil::updateQssStyle(this);
}

void QhPushButton::paintEvent(QPaintEvent *e)
{
    QPushButton::paintEvent(e);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::SmoothPixmapTransform, true);

    QStyleOptionButton option;
    initStyleOption(&option);

    auto state = d->currentState(option);
    QString strState = QhQss::stateToString(state);
    if (!d->attachState.isEmpty()) {
        if (!strState.isEmpty())
            strState.append("-");
        strState.append(d->attachState);
    }

    if (d->labelIconLeft) {
        d->labelIconLeft->setProperty("qstate", strState);
        setLabelIconProperty(0, strState);
        QhWidgetUtil::updateQssStyle(d->labelIconLeft);
    }

    if (d->labelText) {
        d->labelText->setProperty("qstate", strState);
        QhWidgetUtil::updateQssStyle(d->labelText);
    }

    if (d->labelIconRight) {
        d->labelIconRight->setProperty("qstate", strState);
        setLabelIconProperty(1, strState);
        QhWidgetUtil::updateQssStyle(d->labelIconRight);
    }
}

void QhPushButton::setLabelIconProperty(int index, const QString &strState)
{
    Q_UNUSED(index)
    Q_UNUSED(strState)
}

QhPushButtonPrivate::QhPushButtonPrivate(QhPushButton *p) : p(p)
{
}

void QhPushButtonPrivate::init(QWidget *labelIconLeft, QWidget *labelIconRight)
{
    this->labelIconLeft = labelIconLeft;
    labelText = new QhLabel;
    this->labelIconRight = labelIconRight;

    labelIconLeft->setObjectName("IconLeft");
    labelText->setObjectName("LabelText");
    labelIconRight->setObjectName("IconRight");

    auto *ly = new QHBoxLayout(p);
    ly->addWidget(labelIconLeft);
    ly->addWidget(labelText, 1);
    ly->addWidget(labelIconRight);
    ly->setContentsMargins(12, 0, 12, 0);
    ly->setSpacing(6);

    p->setImageMode(false);
}

QhQss::PseudoState QhPushButtonPrivate::currentState(QStyleOptionButton &option)
{
    QhQss::PseudoState state;
    if (!p->isEnabled()) { // disable
        state = QhQss::SPS_Disabled;
    } else if ((option.state & QStyle::State_Sunken) == QStyle::State_Sunken) { // pressed
        state = QhQss::SPS_Pressed;
    } else if ((option.state & QStyle::State_MouseOver) == QStyle::State_MouseOver) { // hover
        state = QhQss::SPS_Hover;
    } else { // normal
        state = QhQss::SPS_Normal;
    }
    return state;
}
