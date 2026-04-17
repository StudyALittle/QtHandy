#include "dirtoolui.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDesktopServices>
#include <QTreeWidgetItem>
#include <qhmessagebox.h>
#include <qhwidgetutil.h>
#include "db/dbmanager.h"
#include "popupdirgroupui.h"

#pragma execution_character_set(push, "utf-8")

DirToolUi::DirToolUi(QWidget *parent) : QWidget(parent)
{
    init();
}

void DirToolUi::enterPage()
{
    QhPage::enterPage();
    if (this->isFirstEnterPage())
        searchData();
}

void DirToolUi::init()
{
    this->setAttribute(Qt::WA_StyledBackground);

    buttonAdd = new QPushButton(tr("添加"));
    buttonAddSub = new QPushButton(tr("添加子目录"));
    m_scrollArea = new QScrollArea;
    m_scrollArea->setWidget(new QWidget);
    m_scrollArea->setWidgetResizable(true);
    {
        auto *ly = new QVBoxLayout(m_scrollArea->widget());
        ly->setSpacing(12);
        ly->setContentsMargins(0, 0, 0, 0);
    }

    auto *ly = new QVBoxLayout(this);

    auto *lyTop = new QHBoxLayout;
    lyTop->addWidget(buttonAdd);
    lyTop->addWidget(buttonAddSub);
    lyTop->addStretch(1);

    ly->addLayout(lyTop);
    ly->addWidget(m_scrollArea, 1);
    ly->setContentsMargins(0, 0, 0, 0);

    connect(buttonAdd, &QPushButton::clicked, this, &DirToolUi::onAddGroup);
}

void DirToolUi::searchData()
{
    QhWidgetUtil::clearLayout(m_scrollArea->widget()->layout());

    auto dirs = DBManager::instance().dirGroupDirDB()->getDirGroupDirList();
    m_dirs = DirGroupDirDB::dirGroupDirListToMap(dirs);

    auto groups = DBManager::instance().dirGroupDB()->getDirGroupList();
    auto groupTrees = DirGroupDB::listToTree(groups);
    for (auto &group : groupTrees) {
        QList<DirGroupDirModel::Ptr> gdir;
        if (m_dirs.contains(group->id))
            gdir = m_dirs.value(group->id);

        auto *groupUi = new DirToolGroupUi;
        groupUi->setData(group, gdir);

        static_cast<QVBoxLayout *>(m_scrollArea->widget()->layout())->insertWidget(0, groupUi);
    }
    static_cast<QVBoxLayout *>(m_scrollArea->widget()->layout())->addStretch(1);
}

void DirToolUi::onAddGroup()
{
    auto data = PopupDirGroupUi::exec(nullptr);
    if (!data)
        return;

    data->parentId = -1;
    if (DBManager::instance().dirGroupDB()->addDirGroup(*data)) {
        searchData();
    } else {
        QhMessageBox::warning(nullptr, tr("错误"), tr("添加分组错误"));
    }
}

void DirToolUi::onDeleteGroupFinished(bool b)
{
    if (b)
        searchData();
}
