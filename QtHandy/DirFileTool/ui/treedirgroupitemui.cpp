#include "treedirgroupitemui.h"
#include "ui_treedirgroupitemui.h"

TreeDirGroupItemUi::TreeDirGroupItemUi(QWidget *parent) : QWidget(parent), ui(new Ui::TreeDirGroupItemUi)
{
    ui->setupUi(this);
    init();
}

TreeDirGroupItemUi::TreeDirGroupItemUi(DirGroupModel::Ptr data, QWidget *parent) :
    QWidget(parent), ui(new Ui::TreeDirGroupItemUi), m_dataGroup(data)
{
    ui->setupUi(this);
    if (data)
        setName(data->name);
    init();
}

TreeDirGroupItemUi::~TreeDirGroupItemUi()
{
    delete ui;
}

DirGroupModel::Ptr TreeDirGroupItemUi::dataGroup() const
{
    return m_dataGroup;
}

void TreeDirGroupItemUi::setData(DirGroupModel::Ptr data)
{
    m_dataGroup = data;
    if (data)
        setName(data->name);
}

void TreeDirGroupItemUi::init()
{
    this->setAttribute(Qt::WA_StyledBackground);

    auto initButton = [](QhPushButton *button) {
        // button->setFixedSize(20, 20);
        button->setImageMode(false);
        // button->iconRight()->setVisible(false);
        // button->iconLeft()->setVisible(true);
        // button->textLabel()->setVisible(false);
        // button->layout()->setContentsMargins(2, 2, 2, 2);
    };

    initButton(ui->pushButtonAdd);
    initButton(ui->pushButtonDel);
    initButton(ui->pushButtonEdit);
    initButton(ui->pushButtonOpen);

    connect(ui->pushButtonAdd, &QPushButton::clicked, this, &TreeDirGroupItemUi::addDir);
    connect(ui->pushButtonOpen, &QPushButton::clicked, this, &TreeDirGroupItemUi::openDirs);
    connect(ui->pushButtonDel, &QPushButton::clicked, this, &TreeDirGroupItemUi::deleteGroup);
    connect(ui->pushButtonEdit, &QPushButton::clicked, this, &TreeDirGroupItemUi::editGroup);
}

void TreeDirGroupItemUi::setName(const QString &text)
{
    ui->labelName->setText(text);
}

QString TreeDirGroupItemUi::name() const
{
    return ui->labelName->text();
}
