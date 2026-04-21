#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->progressBar->setRoundedCorner(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonProgressBar_clicked()
{
    ui->progressBar->setValue(ui->spinBoxProgressBar->value());
}
