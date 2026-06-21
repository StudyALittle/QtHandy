#ifndef QHHEADERVIEW_H
#define QHHEADERVIEW_H

#include <QHeaderView>
#include "QH_global.h"

class QhHeaderViewPrivate;
class QhHeaderViewItem;

class QTHANDY_EXPORT QhHeaderView : public QHeaderView
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhHeaderView)

public:
    QhHeaderView(Qt::Orientation orientation, QWidget *parent = nullptr);
    ~QhHeaderView();

    /// @brief 获取item
    QhHeaderViewItem *itemAt(int index);

    /// @brief 设置item
    void setItem(int index, QhHeaderViewItem *item);

    /// @brief 删除item
    void removeItem(int index);

    /// @brief 取出item
    QhHeaderViewItem *takeItem(int index);

    /// @brief 删除全部item
    void clearItems(bool bUpdate = true);

protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override;
    void mouseMoveEvent(QMouseEvent *e) override;
};

#endif // QHHEADERVIEW_H
