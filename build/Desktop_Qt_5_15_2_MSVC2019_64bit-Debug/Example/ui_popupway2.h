/********************************************************************************
** Form generated from reading UI file 'popupway2.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POPUPWAY2_H
#define UI_POPUPWAY2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PopupWay2
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;

    void setupUi(QWidget *PopupWay2)
    {
        if (PopupWay2->objectName().isEmpty())
            PopupWay2->setObjectName(QString::fromUtf8("PopupWay2"));
        PopupWay2->resize(421, 200);
        PopupWay2->setMinimumSize(QSize(200, 200));
        verticalLayout = new QVBoxLayout(PopupWay2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(24, 24, 24, 24);
        label = new QLabel(PopupWay2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);


        retranslateUi(PopupWay2);

        QMetaObject::connectSlotsByName(PopupWay2);
    } // setupUi

    void retranslateUi(QWidget *PopupWay2)
    {
        PopupWay2->setWindowTitle(QCoreApplication::translate("PopupWay2", "Form", nullptr));
        label->setText(QCoreApplication::translate("PopupWay2", "QtHandyBasePopup as a container", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PopupWay2: public Ui_PopupWay2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POPUPWAY2_H
