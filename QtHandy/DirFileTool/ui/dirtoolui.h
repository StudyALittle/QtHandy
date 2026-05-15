#ifndef DIRTOOLUI_H
#define DIRTOOLUI_H

#include <QWidget>
#include <QTreeWidget>
#include <QPushButton>
#include <QScrollArea>
#include <qhpage.h>
#include "dirtoolgroupui.h"
#include "core/modeldefine.h"

class DirToolGroupUi;

class DirToolUi : public QWidget, public QhPage
{
    Q_OBJECT

public:
    DirToolUi(QWidget *parent = nullptr);

    void enterPage() override;

protected:
    void init();
    void searchData();

private slots:
    void onAddGroup();
    void onDeleteGroupFinished(bool b);

private:
    QPushButton *buttonAdd = nullptr;
    QPushButton *buttonAddSub = nullptr;
    QScrollArea *m_scrollArea = nullptr;

    QMap<int, QList<DirGroupDirModel::Ptr> > m_dirs;
};

#endif // DIRTOOLUI_H
