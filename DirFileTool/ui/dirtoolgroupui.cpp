#include "dirtoolgroupui.h"
#include <QGraphicsDropShadowEffect>
#include <QDesktopServices>
#include <QUrl>
#include <qhmessagebox.h>
#include "treedirgroupitemui.h"
#include "treedirgroupdiritemui.h"
#include "popupdirgroupui.h"
#include "popupdirgroupdirui.h"
#include "db/dbmanager.h"

#pragma execution_character_set(push, "utf-8")

DirToolGroupUi::DirToolGroupUi(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);

    // auto *shadowEffect = new QGraphicsDropShadowEffect;
    // shadowEffect->setOffset(0, 0);
    // shadowEffect->setColor(QColor(0x00, 0x00, 0x00, 0x88));
    // shadowEffect->setBlurRadius(18);
    // this->setGraphicsEffect(shadowEffect);

    auto *ly = new QVBoxLayout(this);
    ly->setSpacing(0);
    ly->setContentsMargins(1, 1, 1, 1);
}

void DirToolGroupUi::setData(DirGroupModel::Ptr group, const QList<DirGroupDirModel::Ptr> &dirs)
{
    auto *w = new TreeDirGroupItemUi(group);
    connect(w, &TreeDirGroupItemUi::deleteGroup, this, &DirToolGroupUi::onDeleteGroup);
    connect(w, &TreeDirGroupItemUi::editGroup, this, &DirToolGroupUi::onEditGroup);
    connect(w, &TreeDirGroupItemUi::addDir, this, &DirToolGroupUi::onAddDir);
    connect(w, &TreeDirGroupItemUi::openDirs, this, &DirToolGroupUi::onOpenDirs);
    selfLayout()->addWidget(w);

    for (auto &dir : dirs) {
        auto *wdir = new TreeDirGroupDirItemUi(dir);
        connect(wdir, &TreeDirGroupDirItemUi::deleteDir, this, &DirToolGroupUi::onDeleteDir);
        connect(wdir, &TreeDirGroupDirItemUi::editDir, this, &DirToolGroupUi::onEditDir);
        connect(wdir, &TreeDirGroupDirItemUi::openDir, this, &DirToolGroupUi::onOpenDir);
        selfLayout()->addWidget(wdir);
        // m_dirItemUis.append(wdir);
    }

    m_group = group;
    m_dirs = dirs;
    // m_groupItemUi = w;
}

void DirToolGroupUi::addDir(DirGroupDirModel::Ptr dir)
{
    auto *wdir = new TreeDirGroupDirItemUi(dir);
    connect(wdir, &TreeDirGroupDirItemUi::deleteDir, this, &DirToolGroupUi::onDeleteDir);
    connect(wdir, &TreeDirGroupDirItemUi::editDir, this, &DirToolGroupUi::onEditDir);
    connect(wdir, &TreeDirGroupDirItemUi::openDir, this, &DirToolGroupUi::onOpenDir);
    selfLayout()->addWidget(wdir);
    // m_dirItemUis.append(wdir);

    m_dirs.append(dir);
}

void DirToolGroupUi::delDir(TreeDirGroupDirItemUi *dirUi)
{
    // m_dirItemUis.removeAll(dirUi);
    selfLayout()->removeWidget(dirUi);
    m_dirs.removeAll(dirUi->dataDir());
}

QVBoxLayout *DirToolGroupUi::selfLayout()
{
    return static_cast<QVBoxLayout *>(this->layout());
}

void DirToolGroupUi::onDeleteGroup()
{
    if (QhBasePopup::ButtonOk !=
        QhMessageBox::warning(nullptr, tr("提示"), tr("确定删除分组？"), QhBasePopup::ButtonAll))
        return;

    auto *item = static_cast<TreeDirGroupItemUi *>(sender());
    if (DBManager::instance().dirGroupDB()->deleteDirGroup(item->dataGroup()->id) &&
        DBManager::instance().dirGroupDirDB()->deleteDirGroupDirByGroupId(item->dataGroup()->id)) {
        emit deleteGroupFinished(true);
    } else {
        QhMessageBox::warning(nullptr, tr("错误"), tr("删除分组错误"));
        emit deleteGroupFinished(false);
    }
}

void DirToolGroupUi::onEditGroup()
{
    auto *item = static_cast<TreeDirGroupItemUi *>(sender());
    auto data = PopupDirGroupUi::exec(item->dataGroup());
    if (!data)
        return;

    if (DBManager::instance().dirGroupDB()->updateDirGroup(*data)) {
        item->setData(data);
        emit editGroupFinished(true);
    } else {
        QhMessageBox::warning(nullptr, tr("错误"), tr("更新分组错误"));
        emit editGroupFinished(false);
    }
}

void DirToolGroupUi::onAddDir()
{
    auto *item = static_cast<TreeDirGroupItemUi *>(sender());
    auto data = PopupDirGroupDirUi::exec(nullptr, item->dataGroup()->name);
    if (!data)
        return;

    data->groupId = item->dataGroup()->id;
    int dirId = DBManager::instance().dirGroupDirDB()->addDirGroupDir(*data);
    if (dirId >= 0) {
        data->id = dirId;
        addDir(data);
    } else {
        QhMessageBox::warning(nullptr, tr("错误"), tr("添加目录错误"));
    }
}

void DirToolGroupUi::onOpenDirs()
{
    auto *item = static_cast<TreeDirGroupItemUi *>(sender());
    auto group = item->dataGroup();
    for (auto &dir : m_dirs) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(dir->dirPath));
    }
}

void DirToolGroupUi::onDeleteDir()
{
    if (QhBasePopup::ButtonOk !=
        QhMessageBox::warning(nullptr, tr("提示"), tr("确定删除目录？"), QhBasePopup::ButtonAll))
        return;

    auto *item = static_cast<TreeDirGroupDirItemUi *>(sender());
    if (DBManager::instance().dirGroupDirDB()->deleteDirGroupDirById(item->dataDir()->id)) {
        delDir(item);
    } else {
        QhMessageBox::warning(nullptr, tr("错误"), tr("删除目录错误"));
    }
}

void DirToolGroupUi::onOpenDir()
{
    auto *item = static_cast<TreeDirGroupDirItemUi *>(sender());
    QDesktopServices::openUrl(QUrl::fromLocalFile(item->dataDir()->dirPath));
}

void DirToolGroupUi::onEditDir()
{
    auto *item = static_cast<TreeDirGroupDirItemUi *>(sender());
    auto data = PopupDirGroupDirUi::exec(item->dataDir());
    if (!data)
        return;

    if (DBManager::instance().dirGroupDirDB()->updateDirGroupDir(*data)) {
        item->setData(data);
    } else {
        QhMessageBox::warning(nullptr, tr("错误"), tr("更新目录错误"));
    }
}
