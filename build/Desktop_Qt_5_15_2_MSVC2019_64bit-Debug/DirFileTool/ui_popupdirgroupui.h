/********************************************************************************
** Form generated from reading UI file 'popupdirgroupui.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POPUPDIRGROUPUI_H
#define UI_POPUPDIRGROUPUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PopupDirGroupUi
{
public:
    QGridLayout *gridLayout;
    QLabel *labelGroup;
    QLineEdit *lineEditParent;
    QLabel *label_2;
    QLineEdit *lineEditName;
    QLabel *label_3;
    QLineEdit *lineEditDes;

    void setupUi(QWidget *PopupDirGroupUi)
    {
        if (PopupDirGroupUi->objectName().isEmpty())
            PopupDirGroupUi->setObjectName(QString::fromUtf8("PopupDirGroupUi"));
        PopupDirGroupUi->resize(352, 155);
        gridLayout = new QGridLayout(PopupDirGroupUi);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(6);
        gridLayout->setVerticalSpacing(12);
        gridLayout->setContentsMargins(20, 20, 20, 20);
        labelGroup = new QLabel(PopupDirGroupUi);
        labelGroup->setObjectName(QString::fromUtf8("labelGroup"));

        gridLayout->addWidget(labelGroup, 0, 0, 1, 1);

        lineEditParent = new QLineEdit(PopupDirGroupUi);
        lineEditParent->setObjectName(QString::fromUtf8("lineEditParent"));

        gridLayout->addWidget(lineEditParent, 0, 1, 1, 1);

        label_2 = new QLabel(PopupDirGroupUi);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEditName = new QLineEdit(PopupDirGroupUi);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        gridLayout->addWidget(lineEditName, 1, 1, 1, 1);

        label_3 = new QLabel(PopupDirGroupUi);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineEditDes = new QLineEdit(PopupDirGroupUi);
        lineEditDes->setObjectName(QString::fromUtf8("lineEditDes"));

        gridLayout->addWidget(lineEditDes, 2, 1, 1, 1);


        retranslateUi(PopupDirGroupUi);

        QMetaObject::connectSlotsByName(PopupDirGroupUi);
    } // setupUi

    void retranslateUi(QWidget *PopupDirGroupUi)
    {
        PopupDirGroupUi->setWindowTitle(QCoreApplication::translate("PopupDirGroupUi", "Form", nullptr));
        labelGroup->setText(QCoreApplication::translate("PopupDirGroupUi", "\347\210\266\345\210\206\347\273\204:", nullptr));
        label_2->setText(QCoreApplication::translate("PopupDirGroupUi", "\345\220\215\347\247\260:", nullptr));
        label_3->setText(QCoreApplication::translate("PopupDirGroupUi", "\346\217\217\350\277\260:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PopupDirGroupUi: public Ui_PopupDirGroupUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POPUPDIRGROUPUI_H
