#include "qhbasepopup.h"
#include "qhbasepopup_p.h"
#include "qhqss.h"

QhBasePopup::QhBasePopup(QWidget *parent):
    QhFramelessDialog(parent),
    d(new QhBasePopupPrivate(this))
{
    d->init();
}

QhBasePopup::QhBasePopup(const QString &title, QWidget *parent):
    QhFramelessDialog(parent),
    d(new QhBasePopupPrivate(this))
{
    d->init();
    setTitle(title);
}

QhBasePopup::~QhBasePopup()
{

}

QPushButton *QhBasePopup::button(Button btn) const
{
    switch (btn) {
    case ButtonOk:      return d->buttonOk;
    case ButtonCancel:  return d->buttonCancel;
    case ButtonClose:   return d->buttonClose;
    default: return nullptr;
    }
}

QhBasePopup::Buttons QhBasePopup::buttons() const
{
    return d->buttons;
}

QString QhBasePopup::buttonText(Button btn) const
{
    auto *pbtn = button(btn);
    return pbtn ? pbtn->text() : QString();
}

bool QhBasePopup::buttonEnable(Button btn) const
{
    auto *pbtn = button(btn);
    return pbtn ? pbtn->isEnabled() : true;
}

QString QhBasePopup::title() const
{
    return d->labelTitle->text();
}

QLabel *QhBasePopup::iconLabel() const
{
    return d->labelIcon;
}

QWidget *QhBasePopup::contentWidget() const
{
    return d->widgetContent;
}

QWidget *QhBasePopup::takeContentWidget() const
{
    if (!d->widgetContent)
        return nullptr;

    auto *w = d->widgetContent;
    w->setParent(nullptr);
    d->widgetContent = nullptr;
    return w;
}

QhBasePopup::Button QhBasePopup::closedButton() const
{
    return d->closedButton;
}

void QhBasePopup::setButtons(Buttons btns)
{
    d->buttons = btns;
    d->buttonOk->setVisible(btns & ButtonOk);
    d->buttonCancel->setVisible(btns & ButtonCancel);
    d->buttonClose->setVisible(btns & ButtonClose);
}

void QhBasePopup::setButtonText(Button btn, const QString &text)
{
    auto *pbtn = button(btn);
    if (pbtn)
        pbtn->setText(text);
}

void QhBasePopup::setButtonsEnable(Buttons btns, bool enable)
{
    if (btns & ButtonOk)
        d->buttonOk->setEnabled(enable);
    if (btns & ButtonCancel)
        d->buttonCancel->setEnabled(enable);
    if (btns & ButtonClose)
        d->buttonClose->setEnabled(enable);
}

void QhBasePopup::setButtonEnable(Button btn, bool enable)
{    
    auto *pbtn = button(btn);
    if (pbtn)
        pbtn->setEnabled(enable);
}

void QhBasePopup::setTitle(const QString &text)
{
    d->labelTitle->setText(text);
}

void QhBasePopup::setContentWidget(QWidget *w)
{
    d->setWidgetContent(w);
}

void QhBasePopup::setContentWidget(QhBasePopupContent *w)
{
    w->setBasePopup(this);
    d->setWidgetContent(w);
}

int QhBasePopup::getWidgetTitleSpace() const
{
    return d->widgetTitleSpace;
}

void QhBasePopup::setWidgetTitleSpace(int space)
{
    d->setWidgetTitleSpace(space);
}

int QhBasePopup::getWidgetButtonsSpace() const
{
    return d->widgetButtonsSpace;
}

void QhBasePopup::setWidgetButtonsSpace(int space)
{
    d->setWidgetButtonsSpace(space);
}

QString QhBasePopup::getWidgetTitleMargins() const
{
    return QhQss::marginsToString(d->widgetTitleMargins);
}

void QhBasePopup::setWidgetTitleMargins(const QString &mgs)
{
    d->setWidgetTitleMargins(QhQss::stringToMargins(mgs));
}

QString QhBasePopup::getWidgetButtonsMargins() const
{
    return QhQss::marginsToString(d->widgetButtonsMargins);
}

void QhBasePopup::setWidgetButtonsMargins(const QString &mgs)
{
    d->setWidgetButtonsMargins(QhQss::stringToMargins(mgs));
}

bool QhBasePopup::afterButtonOk()
{
    return true;
}

bool QhBasePopup::afterButtonCancel()
{
    return true;
}

bool QhBasePopup::afterButtonClose()
{
    return true;
}
