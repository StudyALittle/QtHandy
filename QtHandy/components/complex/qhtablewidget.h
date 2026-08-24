#ifndef QHTABLEWIDGET_H
#define QHTABLEWIDGET_H

#include <QPair>
#include <QTableWidget>
#include "QH_global.h"

class QhTableWidgetPrivate;
class QhHeaderView;
class QhHeaderViewItem;
class QhTableWidgetItem;

class QTHANDY_EXPORT QhTableWidget : public QTableWidget
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhTableWidget)

public:
    QhTableWidget(QWidget *parent = nullptr);
    QhTableWidget(int rows, int columns, QWidget *parent = nullptr);
    ~QhTableWidget();

    /// @brief 打开冻结前面的表格，需要在setHorizontalHeaderItems前调用（一般用于复选框选择）
    void openFrozenTableFront(int columnCount = 1);

    /// @brief 冻结后面的表格，需要在setHorizontalHeaderItems前调用（一般用于放置操作按钮）
    void openFrozenTableBehind(int columnCount = 1);

    /// @brief 水平表头项
    QhHeaderViewItem *horizontalHeaderItemAt(int index);

    /// @brief 设置水平表头items
    void setHorizontalHeaderItems(const QList<QhTableWidgetItem *> &items);

    /// @brief 设置行数
    void setRowCount(int count);

    /// @brief 设置item（覆盖原生的setItem，处理冻结表格数据）
    void setItem(int row, int column, QTableWidgetItem *item);

    /// @brief 设置Cell文本
    QTableWidgetItem *setCellText(int row, int column, const QString &text, int alignment = Qt::AlignCenter);

    /// @brief 设置item窗口（覆盖原生的setCellWidget，处理冻结表格数据）
    void setCellWidget(int row, int column, QWidget *widget);

    /// @brief 设置Column宽度
    void setColumnWidth(int column, int width);

    QTableWidgetItem *item(int row, int column) const;
    QWidget *cellWidget(int row, int column) const;

    void clearContents();
    void clear();

    /// @brief 选中的行（widget 必须提供 checkBox() 函数）
    template <class CellWidget>
    QList<int> checkedRows(int column = 0)
    {
        QList<int> indexs;
        int rowCount = this->rowCount();
        for (int row = 0; row < rowCount; ++row) {
            auto *w = static_cast<CellWidget *>(this->cellWidget(row, column));
            if (w && w->checkBox()->isChecked())
                indexs.append(row);
        }
        return indexs;
    }

    /// @brief 水平表头关联数据复选框
    void horizontalHeaderAssociatedCheckBoxStatus(int column = 0);
    /// @brief 关联水平表头复选框
    void associatedHorizontalHeaderCheckBoxStatus(QhHeaderViewItem *item, int column = 0);

protected:
    void resizeEvent(QResizeEvent *e) override;

    QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) override;
    void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) override;
};

#endif // QHTABLEWIDGET_H
