#ifndef QHTABLEWIDGETITEM_H
#define QHTABLEWIDGETITEM_H

#include <QObject>
#include <QString>
#include "QH_global.h"

class QhHeaderViewItem;
class QTableWidgetItem;
class QhTableWidgetItemPrivate;

/// @brief 列/行表头项信息（目前主要争对列）
/// 关于size、bFillRemaiSize，如果设置了表格列均分宽、列宽可以鼠标拖动等size、bFillRemaiSize将失效

class QTHANDY_EXPORT QhTableWidgetItem
{
    friend class QhTableWidget;
    friend class QhTableWidgetPrivate;
    Q_PRIVATE_VARIABLE(QhTableWidgetItem)

public:
    QhTableWidgetItem();
    QhTableWidgetItem(const QString &name, int size, bool bFillRemaiSize = false);
    QhTableWidgetItem(const QString &name, int size, QTableWidgetItem *item, bool bFillRemaiSize = false);
    QhTableWidgetItem(const QString &name, int size, QhHeaderViewItem *item, bool bFillRemaiSize = false);
    ~QhTableWidgetItem();

    /// @brief 索引
    int index() const;

    /// @brief 项名称
    QString name() const;

    /// @brief 大小
    int size() const;

    /// @brief 补齐剩余的大小，只有一个有效
    bool isFillRemaiSize() const;

    /// @brief qt item
    QTableWidgetItem *item() const;

    /// @brief 表头自定义item
    QhHeaderViewItem *hitem() const;

protected:
    void setIndex(int index);
};

#endif // QHTABLEWIDGETITEM_H
