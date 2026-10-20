#ifndef QHPAGING_H
#define QHPAGING_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include "qhlineedit.h"
#include "QH_global.h"

class QhPagingPrivate;

class QTHANDY_EXPORT QhPaging : public QWidget
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhPaging)

    /// Minimum width of page switching button
    Q_PROPERTY_EX(int, ButtonPageMinWidth)
    Q_PROPERTY_EX(int, ButtonPageFixedHeight)
    Q_PROPERTY_EX(int, ButtonFixedSize)

public:
    QhPaging(QWidget *parent = nullptr);
    ~QhPaging();

    /// @brief 每页显示几条数据列表（可以切换每页显示几条数据）
    QList<QPair<int, QString> > pageSizeList();

    /// @brief 数据总条数
    int totalNumber();

    /// @brief 数据总页数
    int totalPage();

    /// @brief 每页显示几条数据
    int pageSize();

    /// @brief 当前是第几页
    int pageIndex();

    int getButtonPageMinWidth();

    int getButtonFixedSize() const;

    int getButtonPageFixedHeight() const;

    /// @brief
    void setPageSizeList(const QList<QPair<int, QString> > &lists);

    /// @brief
    void setTotalNumber(int n);

    /// @brief
    void setTotalPage(int n);

    /// @brief
    void setPageSize(int n);

    /// @brief
    void setPageIndex(int n);

    void setButtonPageMinWidth(int width);
    void setButtonPageFixedHeight(int h);
    void setButtonFixedSize(int size);

    QHBoxLayout *layoutPageJump() const;
    QhLineEdit *lineEditPageJump() const;

    void setPageJumpVisible(bool b);
    void setPageSizeBoxVisible(bool b);

signals:
    /// @brief 页面索引变化
    void pageIndexChanged(int index);

    /// @brief pageSizeChanged
    void pageSizeChanged(int size);
};

#endif // QHPAGING_H
