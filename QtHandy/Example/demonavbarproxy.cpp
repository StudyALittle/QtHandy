#include "demonavbarproxy.h"
#include <QHBoxLayout>
#include <QLabel>
#include <qhmessagebox.h>
#include <qhpushbutton.h>
#include <qhwidgetutil.h>

DemoNavbarProxy::DemoNavbarProxy()
{

}

QWidget *DemoNavbarProxy::createItemWidget(int level, QhNavbarItem *item)
{
    auto *btn = new QhPushButton(item->name());

    if (level == 1) {
        btn->setImageMode(true);
        btn->setObjectName("NavButtonL1");

        switch (item->id()) {
        case Page_Popup:    { btn->iconLeft()->setObjectName("IconPopup"); break; }
        case Page_Navbar:   { btn->iconLeft()->setObjectName("IconNavbar"); break; }
        case Page_Button:   { btn->iconLeft()->setObjectName("IconButton"); break; }
        case Page_Label:    { btn->iconLeft()->setObjectName("IconLabel"); break; }
        default:            { btn->iconLeft()->setObjectName("Icon"); break; }
        }
        QhWidgetUtil::updateQssStyle(btn->iconLeft());
    } else if (level == 2) {
        btn->setObjectName("NavButtonL2");
    } else if (level == 3) {
        btn->setObjectName("NavButtonL3");
    }

    // No need for the icon on the right side
    if (item->childItems().isEmpty() || level == 2 || level == 3) {
        btn->iconRight()->setVisible(false);
    }
    connect(btn, &QhPushButton::clicked, this, [this, item]() { emit clicked(item->id()); });
    return btn;
}

void DemoNavbarProxy::setItemChecked(QhNavbarItem *item, bool bChekced)
{
    static_cast<QhPushButton*>(item->widget())
        ->attachPropertyState(bChekced ? "checked" : "");

    auto *parentItem = navbar()->parentItem(item->id());
    if (parentItem) {
        childExpand(parentItem, navbar()->isChildExpand(parentItem));
    }
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
    if (item->childItems().isEmpty()) {
        static_cast<QhPushButton*>(item->widget())
            ->attachPropertyState("");
    } else {
        static_cast<QhPushButton*>(item->widget())
            ->attachPropertyState(bExpand ? "expand" : "");
    }
}
