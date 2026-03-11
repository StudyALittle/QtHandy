#ifndef DEMONAVBARPROXY_H
#define DEMONAVBARPROXY_H

#include <qhnavbar.h>
#include <qhnavbaritem.h>
#include <qhnavbarproxy.h>
#include <qhwidgetutil.h>
#include <qhpage.h>

class DemoNavbarProxy: public QhNavbarProxy
{
public:
    enum PageID
    {
        Page_Popup,

        Page_Navbar,
        Page_NavbarV,
        Page_NavbarH,

        Page_Button,
        Page_CheckBox,
        Page_ComboBox,
        Page_PushButton,
        Page_ImageButton,

        Page_Edit,
        Page_LineEdit,
        Page_LineEditDateTime,
        Page_TextEdit,

        Page_DateTime,

        Page_Label,

        Page_Paging,
    };

    DemoNavbarProxy();

protected:
    QWidget *createItemWidget(int level, QhNavbarItem *item) override;
    void setItemChecked(QhNavbarItem *item, bool bChekced) override;

    bool checkedBefore(QhNavbarItem *currentItem, QhNavbarItem *willItem) override;
    void childExpand(QhNavbarItem *item, bool bExpand) override;
};

#endif // DEMONAVBARPROXY_H
