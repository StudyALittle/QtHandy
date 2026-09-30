#ifndef QHSTYLE_H
#define QHSTYLE_H

/**
 * @file       qhstyle.h
 * @brief      样式器
 *
 * @author     wmz
 * @date       2026/09/30
 * @history
 */

#include "QH_global.h"

class QTHANDY_EXPORT QhStyle
{
public:
    QhStyle();

    /// @brief 绘制指示器圆环
    /// @param p: QPainter
    /// @param center: 圆中心点
    /// @param color: 填充颜色
    /// @param radius: 圆半径
    /// @param rw: 圆环宽度
    static void drawIndicatorRing(QPainter *p,
        const QPointF &center, const QColor &color, qreal radius, qreal rw = 4.0f);
};

#endif // QHSTYLE_H
