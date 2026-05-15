/********************************************************************************
** Form generated from reading UI file 'treedirgroupitemui.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TREEDIRGROUPITEMUI_H
#define UI_TREEDIRGROUPITEMUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include "qhpushbutton.h"

QT_BEGIN_NAMESPACE

class Ui_TreeDirGroupItemUi
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *labelName;
    QhPushButton *pushButtonOpen;
    QhPushButton *pushButtonAdd;
    QhPushButton *pushButtonEdit;
    QhPushButton *pushButtonDel;

    void setupUi(QWidget *TreeDirGroupItemUi)
    {
        if (TreeDirGroupItemUi->objectName().isEmpty())
            TreeDirGroupItemUi->setObjectName(QString::fromUtf8("TreeDirGroupItemUi"));
        TreeDirGroupItemUi->resize(707, 56);
        horizontalLayout = new QHBoxLayout(TreeDirGroupItemUi);
        horizontalLayout->setSpacing(8);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(12, 12, 12, 12);
        labelName = new QLabel(TreeDirGroupItemUi);
        labelName->setObjectName(QString::fromUtf8("labelName"));

        horizontalLayout->addWidget(labelName);

        pushButtonOpen = new QhPushButton(TreeDirGroupItemUi);
        pushButtonOpen->setObjectName(QString::fromUtf8("pushButtonOpen"));
        pushButtonOpen->setMinimumSize(QSize(0, 0));
        pushButtonOpen->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(pushButtonOpen);

        pushButtonAdd = new QhPushButton(TreeDirGroupItemUi);
        pushButtonAdd->setObjectName(QString::fromUtf8("pushButtonAdd"));
        pushButtonAdd->setMinimumSize(QSize(0, 0));
        pushButtonAdd->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(pushButtonAdd);

        pushButtonEdit = new QhPushButton(TreeDirGroupItemUi);
        pushButtonEdit->setObjectName(QString::fromUtf8("pushButtonEdit"));
        pushButtonEdit->setMinimumSize(QSize(0, 0));
        pushButtonEdit->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(pushButtonEdit);

        pushButtonDel = new QhPushButton(TreeDirGroupItemUi);
        pushButtonDel->setObjectName(QString::fromUtf8("pushButtonDel"));
        pushButtonDel->setMinimumSize(QSize(0, 0));
        pushButtonDel->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(pushButtonDel);

        horizontalLayout->setStretch(0, 1);

        retranslateUi(TreeDirGroupItemUi);

        QMetaObject::connectSlotsByName(TreeDirGroupItemUi);
    } // setupUi

    void retranslateUi(QWidget *TreeDirGroupItemUi)
    {
        TreeDirGroupItemUi->setWindowTitle(QCoreApplication::translate("TreeDirGroupItemUi", "Form", nullptr));
        labelName->setText(QCoreApplication::translate("TreeDirGroupItemUi", "---", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonOpen->setToolTip(QCoreApplication::translate("TreeDirGroupItemUi", "\346\211\223\345\274\200\347\233\256\345\275\225", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonOpen->setText(QCoreApplication::translate("TreeDirGroupItemUi", "\346\211\223\345\274\200", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonAdd->setToolTip(QCoreApplication::translate("TreeDirGroupItemUi", "\346\267\273\345\212\240\347\233\256\345\275\225", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonAdd->setText(QCoreApplication::translate("TreeDirGroupItemUi", "\346\267\273\345\212\240", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonEdit->setToolTip(QCoreApplication::translate("TreeDirGroupItemUi", "\347\274\226\350\276\221\345\210\206\347\273\204", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonEdit->setText(QCoreApplication::translate("TreeDirGroupItemUi", "\347\274\226\350\276\221", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonDel->setToolTip(QCoreApplication::translate("TreeDirGroupItemUi", "\345\210\240\351\231\244\345\210\206\347\273\204", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonDel->setText(QCoreApplication::translate("TreeDirGroupItemUi", "\345\210\240\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TreeDirGroupItemUi: public Ui_TreeDirGroupItemUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TREEDIRGROUPITEMUI_H
