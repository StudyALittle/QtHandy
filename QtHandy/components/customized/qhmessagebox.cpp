#include "qhmessagebox.h"
#include "qhmessagebox_p.h"
#include <QLabel>
#include <QVBoxLayout>

int QhMessageBoxPrivate::s_nBorderRadius = 0;
int QhMessageBoxPrivate::s_nShadowWidth = 0;

QhMessageBox::QhMessageBox(QWidget *parent):
    QhBasePopup(parent), d(new QhMessageBoxPrivate(this))
{
    d->init();
}

QhMessageBox::~QhMessageBox()
{
    delete d;
}

void QhMessageBox::setRoundedBorder(int borderRadius, int shadowWidth)
{
    QhMessageBoxPrivate::s_nBorderRadius = borderRadius;
    QhMessageBoxPrivate::s_nShadowWidth = shadowWidth;
}

void QhMessageBox::setMessage(const QString &text)
{
    d->labelContent->setText(text);
    d->labelContent->adjustSize();
    d->widgetContent->adjustSize();
    this->adjustSize();
}

QhBasePopup::Button QhMessageBox::question(
    QWidget *widget, const QString &title, const QString &text, Buttons buttons)
{
    return message(Question, widget, title, text, buttons);
}

QhBasePopup::Button QhMessageBox::information(
    QWidget *widget, const QString &title, const QString &text, Buttons buttons)
{
    return message(Question, widget, title, text, buttons);
}

QhBasePopup::Button QhMessageBox::warning(
    QWidget *widget, const QString &title, const QString &text, Buttons buttons)
{
    return message(Question, widget, title, text, buttons);
}

QhBasePopup::Button QhMessageBox::critical(
    QWidget *widget, const QString &title, const QString &text, Buttons buttons)
{
    return message(Question, widget, title, text, buttons);
}

QhBasePopup::Button QhMessageBox::message(
    Icon icon, QWidget *widget, const QString &title, const QString &text, Buttons buttons)
{
    QhMessageBox dlg(widget);
    dlg.init(icon);
    dlg.setTitle(title);
    dlg.setMessage(text);
    dlg.setButtons(buttons);
    dlg.exec();

    return dlg.closedButton();
}

void QhMessageBox::init(Icon icon)
{
    d->icon = icon;
    if (d->icon == NoIcon) {
        this->iconLabel()->setVisible(false);
    }
    this->setMaxNormalAtTitleBar(false);
    this->initFramelessWindow(QhMessageBoxPrivate::s_nBorderRadius);
    if (QhMessageBoxPrivate::s_nBorderRadius > 0)
        this->setShadowWidth(QhMessageBoxPrivate::s_nShadowWidth);
}

void QhMessageBoxPrivate::init()
{
    widgetContent = new QWidget;
    widgetContent->setMinimumSize(200, 100);

    labelContent = new QLabel;
    labelContent->setAlignment(Qt::AlignCenter);

    auto *ly = new QVBoxLayout(widgetContent);
    ly->addWidget(labelContent);
    ly->setContentsMargins(24, 24, 24, 24);

    q_ptr->setButtons(QhMessageBox::ButtonClose);
    q_ptr->setContentWidget(widgetContent);
}
