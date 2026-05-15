#include "popupdirgroupui.h"
#include "ui_popupdirgroupui.h"

#pragma execution_character_set(push, "utf-8")

PopupDirGroupUi::PopupDirGroupUi(QWidget *parent) : QhBasePopupContent(parent), ui(new Ui::PopupDirGroupUi)
{
    ui->setupUi(this);
    ui->lineEditParent->setReadOnly(true);
    ui->labelGroup->setVisible(false);
    ui->lineEditParent->setVisible(false);
}

PopupDirGroupUi::~PopupDirGroupUi()
{
    delete ui;
}

void PopupDirGroupUi::setData(DirGroupModel::Ptr ptr, const QString &parentName)
{
    ui->lineEditParent->setText(parentName);

    m_data = ptr;
    if (!m_data)
        return;

    ui->lineEditName->setText(ptr->name);
    ui->lineEditDes->setText(ptr->description);
}

DirGroupModel::Ptr PopupDirGroupUi::data()
{
    auto ptr = DirGroupModel::Ptr::create();
    if (m_data)
        *ptr = *m_data;

    ptr->name = ui->lineEditName->text();
    ptr->description = ui->lineEditDes->text();
    return ptr;
}

DirGroupModel::Ptr PopupDirGroupUi::exec(DirGroupModel::Ptr ptr, const QString &parentName)
{
    PopupDirGroupUi cw;
    cw.setData(ptr, parentName);

    QhBasePopup popup(!ptr ? tr("添加分组") : tr("编辑分组"));
    popup.initFramelessWindow();
    popup.setContentWidget(&cw);

    return popup.exec() == QDialog::Accepted ? cw.data() : nullptr;
}

bool PopupDirGroupUi::afterButtonOk()
{
    auto name = ui->lineEditName->text();
    auto description = ui->lineEditDes->text();
    if (name.isEmpty() || description.isEmpty())
        return false;
    return true;
}
