#ifndef TREEDIRGROUPITEMUI_H
#define TREEDIRGROUPITEMUI_H

#include <QWidget>
#include "core/modeldefine.h"

namespace Ui
{
class TreeDirGroupItemUi;
}

class TreeDirGroupItemUi : public QWidget
{
    Q_OBJECT

public:
    TreeDirGroupItemUi(QWidget *parent = nullptr);
    TreeDirGroupItemUi(DirGroupModel::Ptr data, QWidget *parent = nullptr);
    ~TreeDirGroupItemUi();

    DirGroupModel::Ptr dataGroup() const;
    void setData(DirGroupModel::Ptr data);

    void setName(const QString &text);
    QString name() const;

protected:
    void init();

signals:
    void addDir();
    void openDirs();
    void deleteGroup();
    void editGroup();

private:
    Ui::TreeDirGroupItemUi *ui;

    DirGroupModel::Ptr m_dataGroup = nullptr;
};

#endif // TREEDIRGROUPITEMUI_H
