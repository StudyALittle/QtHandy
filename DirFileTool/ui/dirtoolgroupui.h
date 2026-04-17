#ifndef DIRTOOLGROUPUI_H
#define DIRTOOLGROUPUI_H

#include <QWidget>
#include <QVBoxLayout>
#include "core/modeldefine.h"

class TreeDirGroupItemUi;
class TreeDirGroupDirItemUi;

class DirToolGroupUi : public QWidget
{
    Q_OBJECT

public:
    DirToolGroupUi(QWidget *parent = nullptr);

    void setData(DirGroupModel::Ptr group, const QList<DirGroupDirModel::Ptr> &dirs);
    void addDir(DirGroupDirModel::Ptr dir);
    void delDir(TreeDirGroupDirItemUi *dirUi);

    QVBoxLayout *selfLayout();

signals:
    void deleteGroupFinished(bool b);
    void editGroupFinished(bool b);

private slots:
    void onDeleteGroup();
    void onEditGroup();
    void onAddDir();
    void onOpenDirs();

    void onDeleteDir();
    void onOpenDir();
    void onEditDir();

private:
    // TreeDirGroupItemUi *m_groupItemUi = nullptr;
    // QList<TreeDirGroupDirItemUi> m_dirItemUis;

    DirGroupModel::Ptr m_group = nullptr;
    QList<DirGroupDirModel::Ptr> m_dirs;
};

#endif // DIRTOOLGROUPUI_H
