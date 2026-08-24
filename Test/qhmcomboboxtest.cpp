#include "qhmcomboboxtest.h"
#include "ui_qhmcomboboxtest.h"
#include <qhfileutil.h>

QhMComboBoxTest::QhMComboBoxTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QhMComboBoxTest)
{
    ui->setupUi(this);

    this->setStyleSheet(QhFileUtil::readFileText(":/resource/qss/QhMComboBox.css"));

    QStringList items;
    for (int n = 0; n < 9; ++n) {
        ui->comboBox->addItem("item " + QString::number(n + 1));
    }
}

QhMComboBoxTest::~QhMComboBoxTest()
{
    delete ui;
}
