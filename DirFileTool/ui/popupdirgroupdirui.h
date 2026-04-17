#ifndef POPUPDIRGROUPDIRUI_H
#define POPUPDIRGROUPDIRUI_H

#include <qhbasepopup.h>
#include <qhbasepopupcontent.h>
#include "core/modeldefine.h"

namespace Ui
{
class PopupDirGroupDirUi;
}

class PopupDirGroupDirUi : public QhBasePopupContent
{
    Q_OBJECT

public:
    explicit PopupDirGroupDirUi(QWidget *parent = nullptr);
    ~PopupDirGroupDirUi();

    void setData(DirGroupDirModel::Ptr ptr, const QString &groupName);
    DirGroupDirModel::Ptr data();

    static DirGroupDirModel::Ptr exec(DirGroupDirModel::Ptr ptr, const QString &groupName = QString());

protected:
    bool afterButtonOk() override;

private slots:
    void on_pushButtonChooseDir_clicked();

private:
    Ui::PopupDirGroupDirUi *ui;

    DirGroupDirModel::Ptr m_data = nullptr;
};

#endif // POPUPDIRGROUPDIRUI_H
