#ifndef QHPAGING_H
#define QHPAGING_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include "qhlabel.h"
#include "qhlineedit.h"
#include "qhcombobox.h"
#include "QH_global.h"

class QhPagingPrivate;

class QTHANDY_EXPORT QhPaging: public QWidget
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhPaging)

    /// Minimum width of page switching button
    Q_PROPERTY_EX(int, ButtonPageMinWidth)

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

signals:
    /// @brief 页面索引变化
    void pageIndexChanged(int index);

    /// @brief pageSizeChanged
    void pageSizeChanged(int size);
};

#endif // QHPAGING_H
