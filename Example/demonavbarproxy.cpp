#include "demonavbarproxy.h"
#include <QHBoxLayout>
#include <QLabel>
#include <qhmessagebox.h>
#include <qhimagebutton.h>
#include <qhwidgetutil.h>

DemoNavbarProxy::DemoNavbarProxy()
{

}

QWidget *DemoNavbarProxy::createItemWidget(int level, QhNavbarItem *item)
{
    auto *btn = new QhImageButton(item->name());

    if (level == 1) {
        switch (item->id()) {
        case Page_Popup:    { btn->setObjectName("NavButtonL1Popup"); break; }
        case Page_Navbar:   { btn->setObjectName("NavButtonL1Navbar"); break; }
        case Page_Button:   { btn->setObjectName("NavButtonL1Button"); break; }
        case Page_Label:    { btn->setObjectName("NavButtonL1Label"); break; }
        default:            { btn->setObjectName("NavButtonL1"); break; }
        }
        QhWidgetUtil::updateQssStyle(btn);
    } else if (level == 2) {
        btn->setObjectName("NavButtonL2");
        btn->setLeftIconVisible(false);
    } else if (level == 3) {
        btn->setObjectName("NavButtonL3");
        btn->setLeftIconVisible(false);
    }

    // No need for the icon on the right side
    if (item->childItems().isEmpty() || level == 2 || level == 3) {
        btn->setRightIconVisible(false);
    }
    connect(btn, &QhImageButton::clicked, this, [this, item]() { emit clicked(item->id()); });
    return btn;
}

void DemoNavbarProxy::setItemChecked(QhNavbarItem *item, bool bChekced)
{
    item->widget()->setProperty("state", bChekced ? "checked" : "");

    auto *parentItem = navbar()->parentItem(item->id());
    if (parentItem) {
        childExpand(parentItem, navbar()->isChildExpand(parentItem));
    }
    QhWidgetUtil::updateQssStyle(item->widget());
}

bool DemoNavbarProxy::checkedBefore(QhNavbarItem *currentItem, QhNavbarItem *willItem)
{
    Q_UNUSED(currentItem)

    if (willItem->id() == Page_NavbarV) {
        QhMessageBox::message(QhMessageBox::NoIcon,
            nullptr, tr("Navbar tips"), willItem->customParam().toString(), QhMessageBox::ButtonOk);
        return false;
    }

    return QhNavbarProxy::checkedBefore(currentItem, willItem);
}

void DemoNavbarProxy::childExpand(QhNavbarItem *item, bool bExpand)
{
    if (item->childItems().isEmpty())
        item->widget()->setProperty("state", "");
    else
        item->widget()->setProperty("state", bExpand ? "expand" : "");
    QhWidgetUtil::updateQssStyle(item->widget());
}
