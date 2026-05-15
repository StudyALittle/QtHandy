#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setStyleSheet("Widget{ background: white; }");

    ui->progressBar->setType(QhProgressBar::Line);
    ui->progressBar->setTextVisible(true);
    ui->progressBar->setStyleSheet(
        "QhProgressBar {"
        "color: white;"
        "qproperty-pBackground: #F0F0F0;"
        "qproperty-pChunkBackground: rgb(64, 158, 255); }");
    connect(ui->comboBoxAlign, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [=](int index) { ui->progressBar->setTextAlign(static_cast<QhProgressBar::TextAlign>(index)); });
    connect(ui->comboBoxOrient, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [=](int index) { ui->progressBar->setGradientOrientation(static_cast<Qt::Orientation>(index + 1)); });
    connect(ui->checkBox1, &QCheckBox::clicked, this, [this](bool b) {
        if (b)
            ui->progressBar->setGradients({
                {0.0, Qt::yellow},
                {1.0, Qt::red},
            });
        else
            ui->progressBar->setGradients({});
    });

    ui->progressBar2->setType(QhProgressBar::Circle);
    ui->progressBar2->setCircleWidthRatio(0.6f);
    ui->progressBar2->setBackground(QColor(0xF0, 0xF0, 0xF0));
    ui->progressBar2->setChunkBackground(QColor(82, 196, 26));
    ui->progressBar2->setStyleSheet(
        "QhProgressBar {"
        "color: black;"
        "font-size: 20px; font-weight: 500;"
        "}");
    ui->progressBar2->setGradients({
        {0.0, Qt::yellow},
        {0.9, Qt::red},
        {1.0, Qt::yellow},
    });

    ui->progressBar3->setType(QhProgressBar::Dashboard);
    ui->progressBar3->setCircleWidthRatio(0.2f);
    ui->progressBar3->setBackground(QColor(0xF0, 0xF0, 0xF0));
    ui->progressBar3->setChunkBackground(QColor(82, 196, 26));
    ui->progressBar3->setStyleSheet(
        "QhProgressBar {"
        "color: black;"
        "font-size: 20px; font-weight: 500;"
        "}");
    ui->progressBar3->setGradients({
        {0.0, Qt::yellow},
        {1.0, Qt::red},
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonProgressBar_clicked()
{
    ui->progressBar->setValue(ui->spinBoxProgressBar->value());
}

void Widget::on_pushButtonProgressBar2_clicked()
{
    ui->progressBar2->setValue(ui->spinBoxProgressBar2->value());
}

void Widget::on_pushButtonProgressBar2_1_clicked()
{
    ui->progressBar2->setCircleWidthRatio(ui->spinBoxProgressBar2_1->value());
}

void Widget::on_pushButtonProgressBar3_clicked()
{
    ui->progressBar3->setValue(ui->spinBoxProgressBar3->value());
}

void Widget::on_pushButtonProgressBar3_1_clicked()
{
    ui->progressBar3->setCircleWidthRatio(ui->spinBoxProgressBar3_1->value());
}
