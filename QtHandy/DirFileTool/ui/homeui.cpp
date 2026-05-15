#include "homeui.h"
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QPushButton>
#include <QButtonGroup>
#include <qhnavbarproxy.h>
#include <qhnavbaritem.h>
#include "dirtoolui.h"

#pragma execution_character_set(push, "utf-8")

class HomeNavbarProxy : public QhNavbarProxy
{
    Q_OBJECT

public:
    enum Page { PageDirTool, PageFileTool };
    QWidget *createItemWidget(int level, QhNavbarItem *item) override
    {
        Q_UNUSED(level)

        auto *btn = new QPushButton(item->name());
        btn->setCheckable(true);
        m_btnGroup.addButton(btn, item->id());
        connect(btn, &QPushButton::clicked, this, [this, item]() { emit clicked(item->id()); });
        return btn;
    }

    void setItemChecked(QhNavbarItem *item, bool bChekced) override
    {
        item->widgetConvert<QPushButton>()->setChecked(bChekced);
    }

protected:
    QButtonGroup m_btnGroup;
};

HomeUi::HomeUi(QWidget *parent) : QWidget(parent), QhPageManager(new QStackedWidget)
{
    this->setAttribute(Qt::WA_StyledBackground);

    auto *navbarProxy = new HomeNavbarProxy;
    m_navbar = new QhNavbar(QhNavbar::Horizontal, QhNavbar::Left, navbarProxy);
    m_navbar->setItems({new QhNavbarItem(HomeNavbarProxy::PageDirTool, tr("目录")),
        new QhNavbarItem(HomeNavbarProxy::PageFileTool, tr("文件"))});
    connect(m_navbar, &QhNavbar::itemChecked, this, [this](qint64 id) { this->enterPage(id); });

    auto *ly = new QVBoxLayout(this);
    auto *lyNavbar = new QHBoxLayout;
    {
        lyNavbar->addWidget(m_navbar);
        lyNavbar->addStretch(1);
    }
    ly->addLayout(lyNavbar);
    ly->addWidget(this->stackedWidget(), 1);

    this->enterPage(HomeNavbarProxy::PageDirTool);
    m_navbar->setChecked(HomeNavbarProxy::PageDirTool);
}

QWidget *HomeUi::createPage(qint64 id)
{
    switch (id) {
    case HomeNavbarProxy::PageDirTool:
        return new DirToolUi;
        break;
    default:
        break;
    }
    return nullptr;
}
#include "homeui.moc"
