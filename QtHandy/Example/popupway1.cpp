#include "popupway1.h"
#include <QLabel>
#include <QVBoxLayout>
#include "qhmessagebox.h"

#pragma execution_character_set("utf-8")

PopupWay1::PopupWay1(const QString &title, QWidget *parent):
    QhBasePopup(title, parent)
{
    auto *w = new QWidget;
    w->setMinimumSize(200, 200);

    auto *label = new QLabel("Inherited from the QhBasePopup!");
    label->setAlignment(Qt::AlignCenter);

    auto *ly = new QVBoxLayout(w);
    ly->addWidget(label);
    ly->setContentsMargins(24, 24, 24, 24);

    this->setContentWidget(w);
}

bool PopupWay1::afterButtonOk()
{
    QhMessageBox::message(QhMessageBox::NoIcon,
        nullptr, tr("test"), "return false: do not close the window", QhMessageBox::ButtonOk);
    return false; // return false: do not close the window
}

bool PopupWay1::afterButtonCancel()
{
    return true;
}

bool PopupWay1::afterButtonClose()
{
    return true;
}
