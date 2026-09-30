#ifndef QHALPHASLIDER_P_H
#define QHALPHASLIDER_P_H

#include "qhalphaslider.h"

class QhAlphaSliderPrivate: public QObject
{
    Q_OBJECT

public:
    QhAlphaSliderPrivate(QhAlphaSlider *alphaSlider);
    ~QhAlphaSliderPrivate();

    void updateFromPos(const QPoint &pos);

    void drawCheckerboard(QPainter *p, const QRectF &rect, int rows = 4);

    QhAlphaSlider *alphaSlider;

    QMarginsF margin = QMarginsF(0, 4, 0, 4);
    QColor color = Qt::black;
    qreal alpha = 1.0f;
};

#endif // QHALPHASLIDER_P_H
