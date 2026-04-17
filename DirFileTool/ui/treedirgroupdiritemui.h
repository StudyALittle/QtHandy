#ifndef TREEDIRGROUPDIRITEMUI_H
#define TREEDIRGROUPDIRITEMUI_H

#include <QWidget>
#include "core/modeldefine.h"

namespace Ui
{
class TreeDirGroupDirItemUi;
}

class TreeDirGroupDirItemUi : public QWidget
{
    Q_OBJECT

public:
    TreeDirGroupDirItemUi(QWidget *parent = nullptr);
    TreeDirGroupDirItemUi(DirGroupDirModel::Ptr data, QWidget *parent = nullptr);
    ~TreeDirGroupDirItemUi();

    DirGroupDirModel::Ptr dataDir() const;

    void setData(DirGroupDirModel::Ptr data);

protected:
    void init();

signals:
    void deleteDir();
    void openDir();
    void editDir();

private:
    Ui::TreeDirGroupDirItemUi *ui;

    DirGroupDirModel::Ptr m_dataDir = nullptr;
};

#endif // TREEDIRGROUPDIRITEMUI_H
