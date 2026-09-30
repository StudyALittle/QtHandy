#ifndef QHALPHASLIDER_H
#define QHALPHASLIDER_H

/**
 * @file       qhalphaslider.h
 * @brief      透明度滑块(目前只支持水平滑块)
 *
 * @author     wmz
 * @date       2026/09/30
 * @history
 */

#include <QWidget>
#include "QH_global.h"

class QhAlphaSliderPrivate;

class QTHANDY_EXPORT QhAlphaSlider: public QWidget
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhAlphaSlider)

public:
    QhAlphaSlider(QWidget *parent = nullptr);
    ~QhAlphaSlider();

    qreal alpha() const;

    void setColor(const QColor &color);
    void setAlpha(qreal alpha);

signals:
    void alphaChanged(qreal alpha);

protected:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
};

#endif // QHALPHASLIDER_H
