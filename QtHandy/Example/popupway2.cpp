#include "popupway2.h"
#include "ui_popupway2.h"
#include <QMessageBox>

PopupWay2::PopupWay2(QWidget *parent) :
    QhBasePopupContent(parent),
    ui(new Ui::PopupWay2)
{
    ui->setupUi(this);
}

PopupWay2::~PopupWay2()
{
    delete ui;
}

bool PopupWay2::exec(const QString &title)
{
    PopupWay2 content;

    QhBasePopup popup(title);
    popup.initFramelessWindow();
    popup.setContentWidget(&content);

    auto ret = (popup.exec() == QDialog::Accepted) ? true : false;
    popup.takeContentWidget();
    return ret;
}

bool PopupWay2::afterButtonOk()
{
    QMessageBox::information(this, tr("test"), "return false: do not close the window");
    return false; // return false: do not close the window
}

bool PopupWay2::afterButtonCancel()
{
    return true;
}

bool PopupWay2::afterButtonClose()
{
    return true;
}
