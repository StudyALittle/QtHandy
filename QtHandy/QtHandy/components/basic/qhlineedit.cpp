#include "qhlineedit.h"
#include "qhlineedit_p.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QValidator>
#include <QPainter>
#include "qhqss.h"
#include "qhwidgetutil.h"

QhLineEdit::QhLineEdit(QWidget *parent):
    QLineEdit(parent),
    d(new QhLineEditPrivate(this))
{
    d->init(nullptr, nullptr);
}

QhLineEdit::QhLineEdit(const QString &contents, QWidget *parent):
    QLineEdit(contents, parent),
    d(new QhLineEditPrivate(this))
{
    d->init(nullptr, nullptr);
}

QhLineEdit::QhLineEdit(QhLineEditSub *leftWidget, QhLineEditSub *rightWidget, QWidget *parent):
    QLineEdit(parent),
    d(new QhLineEditPrivate(this))
{
    d->init(leftWidget, rightWidget);
}

QhLineEdit::~QhLineEdit()
{

}

QhLineEditSub *QhLineEdit::leftWidget() const
{
    return d->widgetLeft;
}

QhLineEditSub *QhLineEdit::rightWidget() const
{
    return d->widgetRight;
}

QMargins QhLineEdit::textMargins() const
{
    if (!d->widgetLeft->isVisible() && !d->widgetRight->isVisible()) {
        return d->margins;
    } else {
        auto margins = QLineEdit::textMargins();
        return QMargins(
            margins.left() - d->widgetLeft->validWidth(),
            margins.top(),
            margins.right() - d->widgetRight->validWidth(),
            margins.bottom());
    }
}

void QhLineEdit::setTextMargins(int left, int top, int right, int bottom)
{
    setTextMargins(QMargins(left, top, right, bottom));
}

void QhLineEdit::setTextMargins(const QMargins &margins)
{
    d->margins = margins;

    if (!d->widgetLeft->isVisible() && !d->widgetRight->isVisible()) {
        QLineEdit::setTextMargins(margins);
    } else {
        d->resetMargin();
    }
}

void QhLineEdit::resetMargin()
{
    d->resetMargin();
}

bool QhLineEdit::isTextValidateValid()
{
    if (d->textValidateFunction)
        return d->textValidateFunction(this);

    auto *valid = this->validator();
    if (!valid)
        return true;

    QString text = this->text();
    if (d->bValidateEmptyNoError && text.isEmpty())
        return true;

    if (valid->inherits("QRegularExpressionValidator")) {
        const auto *regValid = static_cast<const QRegularExpressionValidator*>(valid);
        return regValid->regularExpression()
            .match(text, 0, QRegularExpression::PartialPreferCompleteMatch).hasMatch();
    } else if (valid->inherits("QDoubleValidator")) {
        if (text.isEmpty())
            return false;

        const auto *doubleValid = static_cast<const QDoubleValidator*>(valid);
        auto val = text.toDouble();
        if (val > doubleValid->top() || val < doubleValid->bottom())
            return false;
    } else if (valid->inherits("QIntValidator")) {
        if (text.isEmpty())
            return false;

        const auto *intValid = static_cast<const QIntValidator*>(valid);
        auto val = text.toInt();
        if (val > intValid->top() || val < intValid->bottom())
            return false;
    }

    return true;
}

void QhLineEdit::setTextValidate(std::function<bool (QhLineEdit *)> func)
{
    d->textValidateFunction = func;
    d->checkTextFormat();
}

void QhLineEdit::setTextValidator(const QValidator *validator, bool bEmptyNoError)
{
    d->bValidateEmptyNoError = bEmptyNoError;
    QLineEdit::setValidator(validator);
    d->checkTextFormat();
}

QString QhLineEdit::getLayoutMargins() const
{
    if (this->layout())
        return QhQss::marginsToString(this->layout()->contentsMargins());
    return QString();
}

void QhLineEdit::setLayoutMargins(const QString &str)
{
    if (this->layout())
        this->layout()->setContentsMargins(QhQss::stringToMargins(str));
}

void QhLineEdit::resizeEvent(QResizeEvent *e)
{
    QLineEdit::resizeEvent(e);
    d->resetMargin();
}

void QhLineEdit::showEvent(QShowEvent *e)
{
    QLineEdit::showEvent(e);
    d->resetMargin();
}

void QhLineEdit::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    emit focusIn();
}

void QhLineEdit::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusOutEvent(event);
    emit focusOut();
}

void QhLineEdit::mousePressEvent(QMouseEvent *event)
{
    QLineEdit::mousePressEvent(event);
    emit clicked();
}

QhLineEditPrivate::QhLineEditPrivate(QhLineEdit *p):
    ptr(p)
{

}

void QhLineEditPrivate::init(QhLineEditSub *lWidget, QhLineEditSub *rWidget)
{
    margins = static_cast<QLineEdit*>(ptr)->textMargins();
    if (!lWidget) {
        widgetLeft = new QhLineEditLeft;
    } else {
        widgetLeft = lWidget;
    }
    if (!rWidget) {
        widgetRight = new QhLineEditRight;
    } else {
        widgetRight = rWidget;
    }

    widgetLeft->lineEdit = ptr;
    widgetRight->lineEdit = ptr;

    auto *ly = new QHBoxLayout(ptr);
    ly->addWidget(widgetLeft);
    ly->addStretch(1);
    ly->addWidget(widgetRight);
    ly->setSpacing(0);
    ly->setContentsMargins(1, 1, 1, 1);

    resetMargin();

    connect(ptr, &QhLineEdit::textChanged, this, [this](const QString &) {
        checkTextFormat();
    });
    checkTextFormat();

    widgetLeft->setVisible(false);
    widgetRight->setVisible(false);
}

void QhLineEditPrivate::checkTextFormat()
{
    if (!textValidateFunction && !ptr->validator())
        return;

    auto textVaild = ptr->isTextValidateValid();
    ptr->setProperty("qtextformate", textVaild ? "" : "error");
    QhWidgetUtil::updateQssStyle(ptr);
}

void QhLineEditPrivate::resetMargin()
{
    auto mgs = QMargins(
        margins.left() + widgetLeft->validWidth(),
        margins.top(),
        margins.right() + widgetRight->validWidth(),
        margins.bottom());
    static_cast<QLineEdit*>(ptr)->setTextMargins(mgs);
}

QhLineEditLeft::QhLineEditLeft(QWidget *parent):
    d(new QhLineEditLeftPrivate(this))
{
    this->setAttribute(Qt::WA_StyledBackground);
    d->init();
}

QhLineEditLeft::~QhLineEditLeft()
{

}

QLabel *QhLineEditLeft::label()
{
    return d->label;
}

int QhLineEditLeft::validWidth()
{
    return d->width();
}

QhLineEditRight::QhLineEditRight(QWidget *parent):
    d(new QhLineEditRightPrivate(this))
{
    this->setAttribute(Qt::WA_StyledBackground);
    d->init();
}

QhLineEditRight::~QhLineEditRight()
{

}

QAbstractButton *QhLineEditRight::button()
{
    return d->button;
}

int QhLineEditRight::validWidth()
{
    return d->width();
}

void QhLineEditRight::setPasswdModeEnable(bool bPasswd)
{
    if (bPasswd && !d->bConClicked) {
        d->bConClicked = true;
        connect(d->button, &QPushButton::clicked, d.get(), &QhLineEditRightPrivate::onClicked);
    } else if (!bPasswd && d->bConClicked) {
        d->bConClicked = false;
        disconnect(d->button, &QPushButton::clicked, d.get(), &QhLineEditRightPrivate::onClicked);
    }
}

void QhLineEditRight::setPasswdMode(bool bPasswd)
{
    if (!lineEdit)
        return;

    auto *button = lineEdit->rightWidgetC<QhLineEditRight*>()->button();
    button->setProperty("qstate", bPasswd ? "passwd" : "");
    lineEdit->setEchoMode(bPasswd ? QLineEdit::Password : QLineEdit::Normal);
    QhWidgetUtil::updateQssStyle(button);
}

void QhLineEditRight::switchPasswdMode()
{
    if (!lineEdit)
        return;

    setPasswdMode(!(lineEdit->echoMode() == QLineEdit::Password));
}

QhLineEditLeftPrivate::QhLineEditLeftPrivate(QhLineEditLeft *p):
    ptr(p)
{

}

QhLineEditLeftPrivate::~QhLineEditLeftPrivate()
{

}

void QhLineEditLeftPrivate::init()
{
    label = new QLabel;

    auto *ly = new QHBoxLayout(ptr);
    ly->addWidget(label);
}

int QhLineEditLeftPrivate::width()
{
    int w = 0;
    if (ptr->isVisible()) {
        if (ptr->layout()) {
            auto mgs = ptr->layout()->contentsMargins();
            w = ptr->label()->width() + mgs.left() + mgs.right();
            w = qMax(w, ptr->width());
        } else {
            w = ptr->width();
        }
    }
    return w;
}

QhLineEditRightPrivate::QhLineEditRightPrivate(QhLineEditRight *p):
    ptr(p)
{

}

QhLineEditRightPrivate::~QhLineEditRightPrivate()
{

}

void QhLineEditRightPrivate::init()
{
    button = new QPushButton;
    connect(button, &QPushButton::clicked, ptr, &QhLineEditRight::clicked);

    auto *ly = new QHBoxLayout(ptr);
    ly->addWidget(button);
}

int QhLineEditRightPrivate::width()
{
    int w = 0;
    if (ptr->isVisible()) {
        if (ptr->layout()) {
            auto mgs = ptr->layout()->contentsMargins();
            w = ptr->button()->width() + mgs.left() + mgs.right();
            w = qMax(w, ptr->width());
        } else {
            w = ptr->width();
        }
    }
    return w;
}

void QhLineEditRightPrivate::onClicked(bool checked)
{
    ptr->switchPasswdMode();
}

QhLineEditSub::QhLineEditSub(QWidget *parent):
    QWidget(parent)
{

}

QhLineEditSub::~QhLineEditSub()
{

}
