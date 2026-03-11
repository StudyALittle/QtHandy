#include "demowidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "demopopup.h"
#include "democheckbox.h"
#include "demolabel.h"
#include "demobutton.h"
#include "demolineedit.h"
#include "demolineeditdatetime.h"
#include "demotextedit.h"
#include "demodatetime.h"
#include "demoimagebutton.h"
#include "demopaging.h"

#pragma execution_character_set("utf-8")

DemoWidget::DemoWidget()
{
    this->setAttribute(Qt::WA_StyledBackground);

    auto *ly = new QHBoxLayout(this);

    auto *navbar = new QhNavbar(QhNavbar::Vertical, QhNavbar::Top, new DemoNavbarProxy);
    navbar->setItems({
        new QhNavbarItem(DemoNavbarProxy::Page_Popup, "Popup"),
        new QhNavbarItem(DemoNavbarProxy::Page_Navbar, "Navbar", {
            new QhNavbarItem(DemoNavbarProxy::Page_NavbarV, "Vertical",
                {}, "Refer to the menu bar on the left side of the current interface"),
            new QhNavbarItem(DemoNavbarProxy::Page_NavbarH, "Horizontal"),
        }),
        new QhNavbarItem(DemoNavbarProxy::Page_Button, "Button", {
            new QhNavbarItem(DemoNavbarProxy::Page_CheckBox, "CheckBox"),
            new QhNavbarItem(DemoNavbarProxy::Page_ComboBox, "ComboBox"),
            new QhNavbarItem(DemoNavbarProxy::Page_PushButton, "PushButton"),
            new QhNavbarItem(DemoNavbarProxy::Page_ImageButton, "ImageButton"),
        }),
        new QhNavbarItem(DemoNavbarProxy::Page_Edit, "Edit", {
            new QhNavbarItem(DemoNavbarProxy::Page_LineEdit, "LineEdit"),
            new QhNavbarItem(DemoNavbarProxy::Page_LineEditDateTime, "LineEditDateTime"),
            new QhNavbarItem(DemoNavbarProxy::Page_TextEdit, "TextEdit")
        }),
        new QhNavbarItem(DemoNavbarProxy::Page_DateTime, "DateTime"),
        new QhNavbarItem(DemoNavbarProxy::Page_Label, "Label"),
        new QhNavbarItem(DemoNavbarProxy::Page_Paging, "Paging")
    });
    navbar->setMinimumWidth(166);
    navbar->setItemSpace(2, QhNavbarItem::INVALIDID, 1);
    navbar->setChecked(DemoNavbarProxy::Page_Popup);
    connect(navbar, &QhNavbar::itemChecked, this, &DemoWidget::toPage);

    ly->addWidget(navbar);

    m_stackedWidget = new QStackedWidget;
    ly->addWidget(m_stackedWidget, 1);

    // default page
    toPage(DemoNavbarProxy::Page_Popup);
}

QWidget *DemoWidget::createPage(qint64 id)
{
    switch (id) {
    case DemoNavbarProxy::Page_Popup:       { return new DemoPopup; }
    case DemoNavbarProxy::Page_CheckBox:    { return new DemoCheckBox; }
    case DemoNavbarProxy::Page_Label:       { return new DemoLabel; }
    case DemoNavbarProxy::Page_PushButton:  { return new DemoButton; }
    case DemoNavbarProxy::Page_ImageButton: { return new DemoImageButton; }
    case DemoNavbarProxy::Page_LineEdit:    { return new DemoLineEdit; }
    case DemoNavbarProxy::Page_LineEditDateTime: { return new DemoLineEditDateTime; }
    case DemoNavbarProxy::Page_TextEdit:    { return new DemoTextEdit; }
    case DemoNavbarProxy::Page_DateTime:    { return new DemoDateTime; }
    case DemoNavbarProxy::Page_Paging:      { return new DemoPaging; }
    default: break;
    }
    return nullptr;
}

void DemoWidget::toPage(qint64 id)
{
    if (!m_pages.contains(id)) {
        auto *page = createPage(id);
        if (!page)
            return;
        m_pages.insert(id, page);
        m_stackedWidget->addWidget(page);
    }
    m_stackedWidget->setCurrentWidget(m_pages.value(id));
}
