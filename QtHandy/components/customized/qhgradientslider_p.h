#ifndef QHGRADIENTSLIDER_P_H
#define QHGRADIENTSLIDER_P_H

#include <QLinearGradient>
#include "qhgradientslider.h"

class QhGradientSliderPrivate: public QObject
{
    Q_OBJECT

public:
    QhGradientSliderPrivate(QhGradientSlider *gradientSlider);
    ~QhGradientSliderPrivate();

    bool containsCircle(const QPointF &center, qreal radius, const QPointF &pos) const;
    QColor colorAt(qreal t) const;
    qreal posToAt(const QPoint &pos) const;
    void processPressPos(const QPoint &pos);
    void updateFromPos(const QPoint &pos);
    void removeCheckedPos();
    bool eventFilter(QObject *obj, QEvent *event) override;

    QhGradientSlider *gradientSlider;

    QMarginsF margin = QMarginsF(0, 8, 0, 8);
    QLinearGradient linearGradient;
    QColor checkedColor;
    qreal checkedIndex = 0;

    qreal circleRadius;
    qreal barRadius;
    QRectF barRect;
};

#endif // QHGRADIENTSLIDER_P_H
