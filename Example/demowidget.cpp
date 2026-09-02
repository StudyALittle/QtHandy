#include "demowidget.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCloseEvent>
#include <QDebug>
#include <qhmessagebox.h>
#include "demopopup.h"
#include "democheckbox.h"
#include "demolabel.h"
#include "demobutton.h"
#include "demolineedit.h"
#include "demolineeditdatetime.h"
#include "demotextedit.h"
#include "demodatetime.h"
#include "demopaging.h"

#pragma execution_character_set("utf-8")

enum SystemTrayID
{
    SYSTRAY_Test1 = QhSystemTrayIcon::ID::CustomID + 1,
    SYSTRAY_Test2,
    SYSTRAY_Test3,
    SYSTRAY_Test4,
    SYSTRAY_Test5
};

DemoWidget::DemoWidget()
{
    this->setAttribute(Qt::WA_StyledBackground);

    qApp->setQuitOnLastWindowClosed(false); // 禁止最后一个窗口关闭时退出程序
    m_systemTrayIcon = new QhSystemTrayIcon(QIcon(":/resources/app.ico"), this);
    m_systemTrayIcon->setToolTip("QtHandy DemoWidget");

    QIcon ficon(":/resources/app2.ico");
    m_systemTrayIcon->setFlickerIcon(ficon);

    m_systemTrayIcon->setItems({
            new QhSystemTrayIconItem(QhSystemTrayIcon::ExitProgram, tr("退出程序")),
            new QhSystemTrayIconItem(QhSystemTrayIcon::OpenMainWindow, tr("打开主窗口")),
            new QhSystemTrayIconItem(true),
            new QhSystemTrayIconItem(SYSTRAY_Test1, tr("开启图标闪烁")),
            new QhSystemTrayIconItem(SYSTRAY_Test2, tr("关闭图标闪烁")),
            new QhSystemTrayIconItem(SYSTRAY_Test3, tr("开启鼠标消息")),
            new QhSystemTrayIconItem(SYSTRAY_Test4, tr("停止鼠标消息")),
            new QhSystemTrayIconItem(SYSTRAY_Test5, tr("测试"))
        });

    connect(m_systemTrayIcon, &QhSystemTrayIcon::activated,
            this, [this](QSystemTrayIcon::ActivationReason reason) {
        if (reason == QSystemTrayIcon::Trigger)
            this->show();
         qDebug() << "QhSystemTrayIcon::activated " << reason;
    });

    connect(m_systemTrayIcon, &QhSystemTrayIcon::itemClicked, this, [this](int id) {
        switch (id) {
        case QhSystemTrayIcon::ExitProgram: {
            qApp->exit();
            break;
        }
        case QhSystemTrayIcon::OpenMainWindow: {
            this->show();
            break;
        }
        case SYSTRAY_Test1: {
            m_systemTrayIcon->startFlickerIcon(500);
            break;
        }
        case SYSTRAY_Test2: {
            m_systemTrayIcon->stopFlickerIcon();
            break;
        }
        case SYSTRAY_Test3: {
            if (m_systemTrayIcon->startTrayMoveMessage()) {
                qInfo() << "systemTrayIcon startTrayMoveMessage success";
            } else {
                qInfo() << "systemTrayIcon startTrayMoveMessage error";
            }
            break;
        }
        case SYSTRAY_Test4: {
            m_systemTrayIcon->stopTrayMoveMessage();
            break;
        }
        case SYSTRAY_Test5: {
            QhMessageBox::information(nullptr, tr("info"), tr("QhSystemTrayIcon item 'Test' clicked"));
            break;
        }
        default:
            break;
        }
    });
    connect(m_systemTrayIcon, &QhSystemTrayIcon::entered,
            this, []() {
        qInfo() << "systemTrayIcon startTrayMoveMessage mouse entered";
    });
    connect(m_systemTrayIcon, &QhSystemTrayIcon::leaved,
            this, []() {
        qInfo() << "systemTrayIcon startTrayMoveMessage mouse leaved";
    });
    m_systemTrayIcon->show();

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
    connect(navbar, &QhNavbar::itemChecked, this, [this](qint64 id) {
        enterPage(id);
    });

    ly->addWidget(navbar);

    m_stackedWidget = new QStackedWidget;
    ly->addWidget(m_stackedWidget, 1);

    this->setStackedWidget(m_stackedWidget);
    // default page
    enterPage(DemoNavbarProxy::Page_Popup);
}

QWidget *DemoWidget::createPage(qint64 id)
{
    switch (id) {
    case DemoNavbarProxy::Page_Popup:       { return new DemoPopup; }
    case DemoNavbarProxy::Page_CheckBox:    { return new DemoCheckBox; }
    case DemoNavbarProxy::Page_Label:       { return new DemoLabel; }
    case DemoNavbarProxy::Page_PushButton:  { return new DemoButton; }
    case DemoNavbarProxy::Page_LineEdit:    { return new DemoLineEdit; }
    case DemoNavbarProxy::Page_LineEditDateTime: { return new DemoLineEditDateTime; }
    case DemoNavbarProxy::Page_TextEdit:    { return new DemoTextEdit; }
    case DemoNavbarProxy::Page_DateTime:    { return new DemoDateTime; }
    case DemoNavbarProxy::Page_Paging:      { return new DemoPaging; }
    default: break;
    }
    return nullptr;
}

void DemoWidget::closeEvent(QCloseEvent *event)
{
    m_systemTrayIcon->showMessage(tr("提示"), tr("%1已在后台运行")
        .arg(m_systemTrayIcon->toolTip()), QSystemTrayIcon::Information, 5000);
    this->hide();
    event->ignore();
}
