/********************************************************************************
** Form generated from reading UI file 'treedirgroupdiritemui.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TREEDIRGROUPDIRITEMUI_H
#define UI_TREEDIRGROUPDIRITEMUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "qhlabel.h"

QT_BEGIN_NAMESPACE

class Ui_TreeDirGroupDirItemUi
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *labelName;
    QhLabel *labelPath;
    QPushButton *pushButtonOpen;
    QPushButton *pushButtonEdit;
    QPushButton *pushButtonDel;

    void setupUi(QWidget *TreeDirGroupDirItemUi)
    {
        if (TreeDirGroupDirItemUi->objectName().isEmpty())
            TreeDirGroupDirItemUi->setObjectName(QString::fromUtf8("TreeDirGroupDirItemUi"));
        TreeDirGroupDirItemUi->resize(643, 52);
        horizontalLayout = new QHBoxLayout(TreeDirGroupDirItemUi);
        horizontalLayout->setSpacing(8);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(12, 12, 12, 12);
        labelName = new QLabel(TreeDirGroupDirItemUi);
        labelName->setObjectName(QString::fromUtf8("labelName"));
        labelName->setMinimumSize(QSize(136, 0));

        horizontalLayout->addWidget(labelName);

        labelPath = new QhLabel(TreeDirGroupDirItemUi);
        labelPath->setObjectName(QString::fromUtf8("labelPath"));

        horizontalLayout->addWidget(labelPath);

        pushButtonOpen = new QPushButton(TreeDirGroupDirItemUi);
        pushButtonOpen->setObjectName(QString::fromUtf8("pushButtonOpen"));

        horizontalLayout->addWidget(pushButtonOpen);

        pushButtonEdit = new QPushButton(TreeDirGroupDirItemUi);
        pushButtonEdit->setObjectName(QString::fromUtf8("pushButtonEdit"));

        horizontalLayout->addWidget(pushButtonEdit);

        pushButtonDel = new QPushButton(TreeDirGroupDirItemUi);
        pushButtonDel->setObjectName(QString::fromUtf8("pushButtonDel"));

        horizontalLayout->addWidget(pushButtonDel);

        horizontalLayout->setStretch(1, 1);

        retranslateUi(TreeDirGroupDirItemUi);

        QMetaObject::connectSlotsByName(TreeDirGroupDirItemUi);
    } // setupUi

    void retranslateUi(QWidget *TreeDirGroupDirItemUi)
    {
        TreeDirGroupDirItemUi->setWindowTitle(QCoreApplication::translate("TreeDirGroupDirItemUi", "Form", nullptr));
        labelName->setText(QCoreApplication::translate("TreeDirGroupDirItemUi", "---", nullptr));
        labelPath->setText(QCoreApplication::translate("TreeDirGroupDirItemUi", "---", nullptr));
        pushButtonOpen->setText(QCoreApplication::translate("TreeDirGroupDirItemUi", "\346\211\223\345\274\200", nullptr));
        pushButtonEdit->setText(QCoreApplication::translate("TreeDirGroupDirItemUi", "\347\274\226\350\276\221", nullptr));
        pushButtonDel->setText(QCoreApplication::translate("TreeDirGroupDirItemUi", "\345\210\240\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TreeDirGroupDirItemUi: public Ui_TreeDirGroupDirItemUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TREEDIRGROUPDIRITEMUI_H
