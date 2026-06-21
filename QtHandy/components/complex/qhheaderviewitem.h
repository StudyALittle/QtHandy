#ifndef QHHEADERVIEWITEM_H
#define QHHEADERVIEWITEM_H

#include <QWidget>
#include <QCheckBox>
#include "QH_global.h"

class QhHeaderViewItemPrivate;

class QTHANDY_EXPORT QhHeaderViewItem : public QWidget
{
    Q_OBJECT
    friend class QhHeaderView;
    Q_PRIVATE_VARIABLE(QhHeaderViewItem)

public:
    /// @biref 窗口类型
    enum WType {
        WT_CheckBox,     // 复选框
        WT_Custom = 100, // 自定义
    };

    /// @brief 排序
    enum SortOrder {
        Order_Not, // 不排序
        Order_Asc, // 升序
        Order_Desc // 降序
    };

    /// @brief 构造函数
    /// @param wtype: 窗口类型
    QhHeaderViewItem(int wtype, QWidget *parent = nullptr);
    ~QhHeaderViewItem();

    /// 设置项名称
    void setName(const QString &name);

    /// @brief 复选框
    QCheckBox *checkBox();

signals:
    /// @brief 选中状态变化（WT_CheckBox有效）
    /// @param index: 对应表头的行/列索引
    void checkStateChanged(int index, int state);

protected:
    void setIndex(int index);
};

#endif // QHHEADERVIEWITEM_H
