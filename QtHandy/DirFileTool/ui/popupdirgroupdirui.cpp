#include "popupdirgroupdirui.h"
#include "ui_popupdirgroupdirui.h"
#include <QFileDialog>

#pragma execution_character_set(push, "utf-8")

PopupDirGroupDirUi::PopupDirGroupDirUi(QWidget *parent) : QhBasePopupContent(parent), ui(new Ui::PopupDirGroupDirUi)
{
    ui->setupUi(this);
    this->setMinimumWidth(680);
    ui->labelGroup->setVisible(false);
    ui->lineEditGroup->setVisible(false);
}

PopupDirGroupDirUi::~PopupDirGroupDirUi()
{
    delete ui;
}

void PopupDirGroupDirUi::setData(DirGroupDirModel::Ptr ptr, const QString &groupName)
{
    ui->lineEditGroup->setText(groupName);

    m_data = ptr;
    if (!m_data)
        return;

    ui->lineEditName->setText(ptr->name);
    ui->lineEditDir->setText(ptr->dirPath);
    ui->lineEditDes->setText(ptr->description);
}

DirGroupDirModel::Ptr PopupDirGroupDirUi::data()
{
    auto ptr = DirGroupDirModel::Ptr::create();
    if (m_data)
        *ptr = *m_data;

    ptr->name = ui->lineEditName->text();
    ptr->dirPath = ui->lineEditDir->text();
    ptr->description = ui->lineEditDes->text();
    return ptr;
}

DirGroupDirModel::Ptr PopupDirGroupDirUi::exec(DirGroupDirModel::Ptr ptr, const QString &groupName)
{
    PopupDirGroupDirUi cw;
    cw.setData(ptr, groupName);

    QhBasePopup popup(!ptr ? tr("添加目录") : tr("编辑目录"));
    popup.initFramelessWindow();
    popup.setContentWidget(&cw);

    return popup.exec() == QDialog::Accepted ? cw.data() : nullptr;
}

bool PopupDirGroupDirUi::afterButtonOk()
{
    auto name = ui->lineEditName->text();
    auto dirPath = ui->lineEditDir->text();
    if (name.isEmpty() || dirPath.isEmpty())
        return false;
    return true;
}

void PopupDirGroupDirUi::on_pushButtonChooseDir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(
        this, tr("选择目录"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!dir.isEmpty())
        ui->lineEditDir->setText(dir);
}
