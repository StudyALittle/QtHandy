/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qhprogressbar.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox1;
    QLabel *label_2;
    QComboBox *comboBoxOrient;
    QLabel *label;
    QComboBox *comboBoxAlign;
    QLabel *label_3;
    QSpinBox *spinBoxProgressBar;
    QPushButton *pushButtonProgressBar;
    QhProgressBar *progressBar;
    QHBoxLayout *horizontalLayout_4;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QhProgressBar *progressBar2;
    QGridLayout *gridLayout;
    QPushButton *pushButtonProgressBar2;
    QSpinBox *spinBoxProgressBar2;
    QDoubleSpinBox *spinBoxProgressBar2_1;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButtonProgressBar2_1;
    QSpacerItem *verticalSpacer_2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_3;
    QhProgressBar *progressBar3;
    QGridLayout *gridLayout_2;
    QSpinBox *spinBoxProgressBar3;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pushButtonProgressBar3_1;
    QPushButton *pushButtonProgressBar3;
    QDoubleSpinBox *spinBoxProgressBar3_1;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 508);
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        checkBox1 = new QCheckBox(groupBox);
        checkBox1->setObjectName(QString::fromUtf8("checkBox1"));

        horizontalLayout->addWidget(checkBox1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        comboBoxOrient = new QComboBox(groupBox);
        comboBoxOrient->addItem(QString());
        comboBoxOrient->addItem(QString());
        comboBoxOrient->setObjectName(QString::fromUtf8("comboBoxOrient"));

        horizontalLayout->addWidget(comboBoxOrient);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comboBoxAlign = new QComboBox(groupBox);
        comboBoxAlign->addItem(QString());
        comboBoxAlign->addItem(QString());
        comboBoxAlign->addItem(QString());
        comboBoxAlign->addItem(QString());
        comboBoxAlign->setObjectName(QString::fromUtf8("comboBoxAlign"));

        horizontalLayout->addWidget(comboBoxAlign);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        spinBoxProgressBar = new QSpinBox(groupBox);
        spinBoxProgressBar->setObjectName(QString::fromUtf8("spinBoxProgressBar"));
        spinBoxProgressBar->setMinimumSize(QSize(70, 0));
        spinBoxProgressBar->setMaximum(100);

        horizontalLayout->addWidget(spinBoxProgressBar);

        pushButtonProgressBar = new QPushButton(groupBox);
        pushButtonProgressBar->setObjectName(QString::fromUtf8("pushButtonProgressBar"));

        horizontalLayout->addWidget(pushButtonProgressBar);


        verticalLayout_3->addLayout(horizontalLayout);

        progressBar = new QhProgressBar(groupBox);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        verticalLayout_3->addWidget(progressBar);


        verticalLayout->addWidget(groupBox);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setSizeConstraint(QLayout::SetMinAndMaxSize);
        widget = new QWidget(Widget);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        progressBar2 = new QhProgressBar(widget);
        progressBar2->setObjectName(QString::fromUtf8("progressBar2"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(progressBar2->sizePolicy().hasHeightForWidth());
        progressBar2->setSizePolicy(sizePolicy1);
        progressBar2->setMinimumSize(QSize(0, 0));
        progressBar2->setValue(24);

        verticalLayout_2->addWidget(progressBar2);


        horizontalLayout_4->addWidget(widget);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinimumSize);
        pushButtonProgressBar2 = new QPushButton(Widget);
        pushButtonProgressBar2->setObjectName(QString::fromUtf8("pushButtonProgressBar2"));

        gridLayout->addWidget(pushButtonProgressBar2, 1, 1, 1, 1);

        spinBoxProgressBar2 = new QSpinBox(Widget);
        spinBoxProgressBar2->setObjectName(QString::fromUtf8("spinBoxProgressBar2"));
        spinBoxProgressBar2->setMinimumSize(QSize(70, 0));
        spinBoxProgressBar2->setMaximum(100);

        gridLayout->addWidget(spinBoxProgressBar2, 1, 0, 1, 1);

        spinBoxProgressBar2_1 = new QDoubleSpinBox(Widget);
        spinBoxProgressBar2_1->setObjectName(QString::fromUtf8("spinBoxProgressBar2_1"));
        spinBoxProgressBar2_1->setMinimum(0.010000000000000);

        gridLayout->addWidget(spinBoxProgressBar2_1, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 0, 1, 1);

        pushButtonProgressBar2_1 = new QPushButton(Widget);
        pushButtonProgressBar2_1->setObjectName(QString::fromUtf8("pushButtonProgressBar2_1"));

        gridLayout->addWidget(pushButtonProgressBar2_1, 2, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 0, 1, 1);


        horizontalLayout_4->addLayout(gridLayout);

        horizontalLayout_4->setStretch(0, 1);

        verticalLayout->addLayout(horizontalLayout_4);

        widget_2 = new QWidget(Widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(0, 200));
        horizontalLayout_3 = new QHBoxLayout(widget_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        progressBar3 = new QhProgressBar(widget_2);
        progressBar3->setObjectName(QString::fromUtf8("progressBar3"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(progressBar3->sizePolicy().hasHeightForWidth());
        progressBar3->setSizePolicy(sizePolicy2);
        progressBar3->setValue(24);

        horizontalLayout_3->addWidget(progressBar3);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        spinBoxProgressBar3 = new QSpinBox(widget_2);
        spinBoxProgressBar3->setObjectName(QString::fromUtf8("spinBoxProgressBar3"));
        spinBoxProgressBar3->setMaximum(100);

        gridLayout_2->addWidget(spinBoxProgressBar3, 1, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 0, 0, 1, 1);

        pushButtonProgressBar3_1 = new QPushButton(widget_2);
        pushButtonProgressBar3_1->setObjectName(QString::fromUtf8("pushButtonProgressBar3_1"));

        gridLayout_2->addWidget(pushButtonProgressBar3_1, 2, 1, 1, 1);

        pushButtonProgressBar3 = new QPushButton(widget_2);
        pushButtonProgressBar3->setObjectName(QString::fromUtf8("pushButtonProgressBar3"));

        gridLayout_2->addWidget(pushButtonProgressBar3, 1, 1, 1, 1);

        spinBoxProgressBar3_1 = new QDoubleSpinBox(widget_2);
        spinBoxProgressBar3_1->setObjectName(QString::fromUtf8("spinBoxProgressBar3_1"));
        spinBoxProgressBar3_1->setMinimum(0.010000000000000);

        gridLayout_2->addWidget(spinBoxProgressBar3_1, 2, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_4, 3, 0, 1, 1);


        horizontalLayout_3->addLayout(gridLayout_2);


        verticalLayout->addWidget(widget_2);

        verticalLayout->setStretch(1, 2);
        verticalLayout->setStretch(2, 2);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Widget", "\347\272\277\345\275\242\350\277\233\345\272\246\346\235\241", nullptr));
        checkBox1->setText(QCoreApplication::translate("Widget", "\346\270\220\345\217\230\350\211\262", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\346\270\220\345\217\230\350\211\262\346\226\271\345\220\221\357\274\232", nullptr));
        comboBoxOrient->setItemText(0, QCoreApplication::translate("Widget", "\346\260\264\345\271\263", nullptr));
        comboBoxOrient->setItemText(1, QCoreApplication::translate("Widget", "\345\236\202\347\233\264", nullptr));

        label->setText(QCoreApplication::translate("Widget", "\346\226\207\346\234\254\346\226\271\345\220\221:", nullptr));
        comboBoxAlign->setItemText(0, QCoreApplication::translate("Widget", "AlignFollowText", nullptr));
        comboBoxAlign->setItemText(1, QCoreApplication::translate("Widget", "AlignLeft", nullptr));
        comboBoxAlign->setItemText(2, QCoreApplication::translate("Widget", "AlignRight", nullptr));
        comboBoxAlign->setItemText(3, QCoreApplication::translate("Widget", "AlignCenter", nullptr));

        label_3->setText(QCoreApplication::translate("Widget", "\345\200\274", nullptr));
        pushButtonProgressBar->setText(QCoreApplication::translate("Widget", "\350\256\276\347\275\256", nullptr));
        pushButtonProgressBar2->setText(QCoreApplication::translate("Widget", "\350\256\276\347\275\256", nullptr));
        pushButtonProgressBar2_1->setText(QCoreApplication::translate("Widget", "\350\256\276\347\275\256", nullptr));
        pushButtonProgressBar3_1->setText(QCoreApplication::translate("Widget", "\350\256\276\347\275\256", nullptr));
        pushButtonProgressBar3->setText(QCoreApplication::translate("Widget", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
