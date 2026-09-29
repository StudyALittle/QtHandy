#ifndef QHHUESLIDER_H
#define QHHUESLIDER_H

/**
 * @file       qhhueslider.h
 * @brief      色相条
 *
 * @author     wmz
 * @date       2026/09/29
 * @history
 */

#include <QWidget>
#include "QH_global.h"

class QhHueSliderPrivate;

class QTHANDY_EXPORT QhHueSlider: public QWidget
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhHueSlider)

public:
    QhHueSlider(Qt::Orientation orientation, QWidget *parent = nullptr);
    ~QhHueSlider();

    qreal hue() const;
    QColor color() const;

    void setHue(qreal hue);
    void setColor(const QColor &color);

signals:
    void hueChanged(qreal hue);

protected:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
};

#endif // QHHUESLIDER_H
