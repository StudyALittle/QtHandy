#ifndef POPUPDIRGROUPUI_H
#define POPUPDIRGROUPUI_H

#include <qhbasepopup.h>
#include <qhbasepopupcontent.h>
#include "core/modeldefine.h"

namespace Ui
{
class PopupDirGroupUi;
}

class PopupDirGroupUi : public QhBasePopupContent
{
    Q_OBJECT

public:
    explicit PopupDirGroupUi(QWidget *parent = nullptr);
    ~PopupDirGroupUi();

    void setData(DirGroupModel::Ptr ptr, const QString &parentName);
    DirGroupModel::Ptr data();

    static DirGroupModel::Ptr exec(DirGroupModel::Ptr ptr, const QString &parentName = QString());

protected:
    bool afterButtonOk() override;

private:
    Ui::PopupDirGroupUi *ui;

    DirGroupModel::Ptr m_data = nullptr;
};

#endif // POPUPDIRGROUPUI_H
