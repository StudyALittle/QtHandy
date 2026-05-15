/********************************************************************************
** Form generated from reading UI file 'popupdirgroupdirui.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POPUPDIRGROUPDIRUI_H
#define UI_POPUPDIRGROUPDIRUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PopupDirGroupDirUi
{
public:
    QGridLayout *gridLayout_2;
    QLabel *labelGroup;
    QLineEdit *lineEditGroup;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEditDir;
    QPushButton *pushButtonChooseDir;
    QLineEdit *lineEditDes;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEditName;

    void setupUi(QWidget *PopupDirGroupDirUi)
    {
        if (PopupDirGroupDirUi->objectName().isEmpty())
            PopupDirGroupDirUi->setObjectName(QString::fromUtf8("PopupDirGroupDirUi"));
        PopupDirGroupDirUi->resize(649, 187);
        gridLayout_2 = new QGridLayout(PopupDirGroupDirUi);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(6);
        gridLayout_2->setVerticalSpacing(12);
        gridLayout_2->setContentsMargins(20, 20, 20, 20);
        labelGroup = new QLabel(PopupDirGroupDirUi);
        labelGroup->setObjectName(QString::fromUtf8("labelGroup"));

        gridLayout_2->addWidget(labelGroup, 0, 0, 1, 1);

        lineEditGroup = new QLineEdit(PopupDirGroupDirUi);
        lineEditGroup->setObjectName(QString::fromUtf8("lineEditGroup"));
        lineEditGroup->setReadOnly(true);

        gridLayout_2->addWidget(lineEditGroup, 0, 1, 1, 1);

        label_2 = new QLabel(PopupDirGroupDirUi);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEditDir = new QLineEdit(PopupDirGroupDirUi);
        lineEditDir->setObjectName(QString::fromUtf8("lineEditDir"));

        horizontalLayout->addWidget(lineEditDir);

        pushButtonChooseDir = new QPushButton(PopupDirGroupDirUi);
        pushButtonChooseDir->setObjectName(QString::fromUtf8("pushButtonChooseDir"));

        horizontalLayout->addWidget(pushButtonChooseDir);


        gridLayout_2->addLayout(horizontalLayout, 2, 1, 1, 1);

        lineEditDes = new QLineEdit(PopupDirGroupDirUi);
        lineEditDes->setObjectName(QString::fromUtf8("lineEditDes"));

        gridLayout_2->addWidget(lineEditDes, 3, 1, 1, 1);

        label_3 = new QLabel(PopupDirGroupDirUi);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 3, 0, 1, 1);

        label_4 = new QLabel(PopupDirGroupDirUi);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        lineEditName = new QLineEdit(PopupDirGroupDirUi);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        gridLayout_2->addWidget(lineEditName, 1, 1, 1, 1);


        retranslateUi(PopupDirGroupDirUi);

        QMetaObject::connectSlotsByName(PopupDirGroupDirUi);
    } // setupUi

    void retranslateUi(QWidget *PopupDirGroupDirUi)
    {
        PopupDirGroupDirUi->setWindowTitle(QCoreApplication::translate("PopupDirGroupDirUi", "Form", nullptr));
        labelGroup->setText(QCoreApplication::translate("PopupDirGroupDirUi", "\345\210\206\347\273\204:", nullptr));
        label_2->setText(QCoreApplication::translate("PopupDirGroupDirUi", "\347\233\256\345\275\225:", nullptr));
        pushButtonChooseDir->setText(QCoreApplication::translate("PopupDirGroupDirUi", "\351\200\211\346\213\251\347\233\256\345\275\225", nullptr));
        label_3->setText(QCoreApplication::translate("PopupDirGroupDirUi", "\346\217\217\350\277\260:", nullptr));
        label_4->setText(QCoreApplication::translate("PopupDirGroupDirUi", "\345\220\215\347\247\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PopupDirGroupDirUi: public Ui_PopupDirGroupDirUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POPUPDIRGROUPDIRUI_H
