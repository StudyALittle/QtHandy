#include "testwidgettable.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QCheckBox>
#include "qhtablewidgetitem.h"
#include "qhheaderviewitem.h"

#pragma execution_character_set(push, "utf-8")

TestWidgetTable::TestWidgetTable()
{
    auto *tableWidget = new QhTableWidget;
    tableWidget->openFrozenTableFront(2); // 锁定第一列和第二列
    tableWidget->openFrozenTableBehind(1);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->setHorizontalHeaderItems({
        new QhTableWidgetItem(tr(""), 80),
        new QhTableWidgetItem(tr(""), 50, new QhHeaderViewItem(QhHeaderViewItem::WT_CheckBox)),
        new QhTableWidgetItem(tr("序号"), 60),
        new QhTableWidgetItem(tr("姓名"), 100),
        new QhTableWidgetItem(tr("性别"), 80),
        new QhTableWidgetItem(tr("地址"), 100, true),
        new QhTableWidgetItem(tr("操作"), 80/*, new QhHeaderViewItem(QhHeaderViewItem::WT_CheckBox)*/),
    });
    // 水平表头关联数据复选框
    int checkBoxColumn = 1;
    tableWidget->horizontalHeaderAssociatedCheckBoxStatus(checkBoxColumn);

    auto *ly = new QVBoxLayout(this);
    ly->addWidget(tableWidget);

    int num = 5;
    tableWidget->clearContents();
    tableWidget->horizontalHeaderItemAt(checkBoxColumn)->checkBox()->setCheckState(Qt::Unchecked);
    tableWidget->setRowCount(num);
    for (int n = 0; n < num; ++n) {
        int col = 0;

        tableWidget->setCellText(n, col++, tr("收藏"));

        // checkbox
        auto *item = new QhHeaderViewItem(QhHeaderViewItem::WT_CheckBox);
        tableWidget->setCellWidget(n, col++, item);
        // 关联水平表头复选框
        tableWidget->associatedHorizontalHeaderCheckBoxStatus(item, checkBoxColumn);

        tableWidget->setCellText(n, col++, QString::number(n + 1));
        tableWidget->setCellText(n, col++, tr("用户%1").arg(n + 1));
        tableWidget->setCellText(n, col++, (n % 2) ? tr("男") : tr("女"));
        tableWidget->setCellText(n, col++, "xxxxxxxxxxxxxxxxxxxxxxxxxx");

        {
            auto *item = new QTableWidgetItem;
            tableWidget->setItem(n, col, item);
            auto *btn = new QPushButton(tr("删除"));
            btn->setStyleSheet("border: 1px solid red; padding: 3px;");
            tableWidget->setCellWidget(n, col, btn);
        }
    }
}
