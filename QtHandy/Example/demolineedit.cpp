#include "demolineedit.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QValidator>
#include <qhlabel.h>
#include <qhwidgetutil.h>

DemoLineEdit::DemoLineEdit(QWidget *parent):
    QWidget(parent)
{
    auto *ly = new QVBoxLayout(this);
    {
        auto *label = new QhLabel("Normal LineEdit");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");

        auto *lineEdit = new QhLineEdit;
        lineEdit->setObjectName("LineEditNormal");  // qss style
        lineEdit->leftWidget()->setVisible(false);
        lineEdit->rightWidget()->setVisible(false);

        ly->addWidget(label);
        ly->addWidget(lineEdit);
    }

    {
        auto *label = new QhLabel("Left LineEdit(1)");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");

        auto *lineEdit = new QhLineEdit;
        lineEdit->setObjectName("LineEditLeft");  // qss style
        lineEdit->leftWidget()->setVisible(true);
        lineEdit->rightWidget()->setVisible(false);

        lineEdit->leftWidget()->layout()->setContentsMargins(12, 0, 0, 0);
        lineEdit->leftWidgetC<QhLineEditLeft*>()->label()->setFixedSize(16, 16);

        lineEdit->resetMargin();

        ly->addWidget(label);
        ly->addWidget(lineEdit);
    }

    {
        auto *label = new QhLabel("Left LineEdit(2)");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");

        auto *lineEdit = new QhLineEdit;
        lineEdit->setObjectName("LineEditLeft2");  // qss style
        lineEdit->leftWidget()->setVisible(true);
        lineEdit->rightWidget()->setVisible(false);

        lineEdit->leftWidget()->layout()->setContentsMargins(12, 0, 12, 0);
        lineEdit->leftWidgetC<QhLineEditLeft*>()->label()->setFixedSize(16, 16);

        lineEdit->resetMargin();

        ly->addWidget(label);
        ly->addWidget(lineEdit);
    }

    {
        auto *label = new QhLabel("Left LineEdit Password");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");

        auto *lineEdit = new QhLineEdit;
        lineEdit->setObjectName("LineEditLeftPassword");  // qss style
        lineEdit->leftWidget()->setVisible(true);
        lineEdit->rightWidget()->setVisible(true);

        lineEdit->leftWidget()->layout()->setContentsMargins(12, 0, 0, 0);
        lineEdit->leftWidgetC<QhLineEditLeft*>()->label()->setFixedSize(20, 20);

        lineEdit->rightWidget()->layout()->setContentsMargins(0, 0, 12, 0);
        lineEdit->rightWidgetC<QhLineEditRight*>()->button()->setFixedSize(20, 20);
        lineEdit->rightWidgetC<QhLineEditRight*>()->setPasswdModeEnable(true);
        lineEdit->rightWidgetC<QhLineEditRight*>()->setPasswdMode(true);

        lineEdit->resetMargin();

        ly->addWidget(label);
        ly->addWidget(lineEdit);
    }

    {
        auto *label = new QhLabel("TextValidator LineEdit");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");

        auto *lineEdit = new QhLineEdit;
        lineEdit->leftWidget()->setVisible(false);
        lineEdit->rightWidget()->setVisible(false);
        lineEdit->setTextValidator(new QRegularExpressionValidator(
            QRegularExpression("^[0-9a-zA-Z_]{1,30}$")));

        ly->addWidget(label);
        ly->addWidget(lineEdit);
    }

    {
        auto *label = new QhLabel("TextValidator LineEdit");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");

        auto *lineEdit = new QhLineEdit;
        lineEdit->leftWidget()->setVisible(false);
        lineEdit->rightWidget()->setVisible(false);
        lineEdit->setTextValidator(new QRegularExpressionValidator(
            QRegularExpression("^[0-9a-zA-Z_]{2,30}$")), true);

        ly->addWidget(label);
        ly->addWidget(lineEdit);
    }

    {
        auto *label = new QhLabel("LineEdit (length limit)");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");

        auto *lineEdit = new QhLineEdit(nullptr, new QhLineEditLeft);
        lineEdit->setObjectName("LineEditLeftLimit");  // qss style
        lineEdit->leftWidget()->setVisible(false);
        lineEdit->rightWidget()->setVisible(true);
        lineEdit->setTextValidator(new QRegularExpressionValidator(
            QRegularExpression("^[0-9a-zA-Z_]{2,10}$")), true);

        // length limit
        auto *labelLimit = lineEdit->rightWidgetC<QhLineEditLeft*>()->label();
        // labelLimit->setFixedWidth(30);
        labelLimit->setText("0/10");
        connect(lineEdit, &QhLineEdit::textChanged, this, [labelLimit](const QString &text) {
            labelLimit->setText(QString("%1/10").arg(text.size()));
            labelLimit->adjustSize();
        });

        ly->addWidget(label);
        ly->addWidget(lineEdit);
    }

    ly->addStretch(1);
}
