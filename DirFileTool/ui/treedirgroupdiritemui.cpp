#include "treedirgroupdiritemui.h"
#include "ui_treedirgroupdiritemui.h"

TreeDirGroupDirItemUi::TreeDirGroupDirItemUi(QWidget *parent) : QWidget(parent), ui(new Ui::TreeDirGroupDirItemUi)
{
    ui->setupUi(this);
    init();
}

TreeDirGroupDirItemUi::TreeDirGroupDirItemUi(DirGroupDirModel::Ptr data, QWidget *parent) :
    QWidget(parent), ui(new Ui::TreeDirGroupDirItemUi), m_dataDir(data)
{
    ui->setupUi(this);
    if (data) {
        ui->labelName->setText(data->name);
        ui->labelPath->setText(data->dirPath);
    }
    init();
}

TreeDirGroupDirItemUi::~TreeDirGroupDirItemUi()
{
    delete ui;
}

void TreeDirGroupDirItemUi::init()
{
    this->setAttribute(Qt::WA_StyledBackground);
    ui->labelPath->setEllipsis(true);
    connect(ui->pushButtonDel, &QPushButton::clicked, this, &TreeDirGroupDirItemUi::deleteDir);
    connect(ui->pushButtonOpen, &QPushButton::clicked, this, &TreeDirGroupDirItemUi::openDir);
    connect(ui->pushButtonEdit, &QPushButton::clicked, this, &TreeDirGroupDirItemUi::editDir);
}

DirGroupDirModel::Ptr TreeDirGroupDirItemUi::dataDir() const
{
    return m_dataDir;
}

void TreeDirGroupDirItemUi::setData(DirGroupDirModel::Ptr data)
{
    m_dataDir = data;
    if (data) {
        ui->labelName->setText(data->name);
        ui->labelPath->setText(data->dirPath);
    }
}
