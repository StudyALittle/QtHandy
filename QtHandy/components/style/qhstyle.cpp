#include "qhstyle.h"
#include <QPainter>

QhStyle::QhStyle()
{

}

void QhStyle::drawIndicatorRing(QPainter *p,
    const QPointF &center, const QColor &color, qreal radius, qreal rw)
{
    qreal gr = 1.5f;
    qreal rr = rw / 2.0f;

    // 外圈阴影
    p->setPen(QPen(QColor(0, 0, 0, 20), gr * 2.0f));
    p->setBrush(Qt::NoBrush);
    p->drawEllipse(center, radius - gr, radius - gr);

    // 外圈白色
    p->setPen(QPen(QColor(0xFF, 0xFF, 0xFF), rw));
    p->drawEllipse(center, radius - rr - gr, radius - rr - gr);

    // 内圈显示当前 alpha 下的颜色
    p->setPen(Qt::NoPen);
    p->setBrush(color);
    p->drawEllipse(center, radius - rw, radius - rw);
}
