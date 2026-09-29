#ifndef QHHUESLIDER_P_H
#define QHHUESLIDER_P_H

#include <QObject>
#include "qhhueslider.h"

class QhHueSliderPrivate: public QObject
{
    Q_OBJECT
public:
    QhHueSliderPrivate(QhHueSlider *hueSlider);
    ~QhHueSliderPrivate();

    void updateFromPos(const QPoint &pos);

    QhHueSlider *hueSlider;
    Qt::Orientation orientation;
    qreal hue = 0.0;
};

#endif // QHHUESLIDER_P_H
