#ifndef QHGRADIENTSLIDER_H
#define QHGRADIENTSLIDER_H

/**
 * @file       qhgradientslider.h
 * @brief      渐变色选择滑块，目前只支持水平线性滑块
 *
 * @author     wmz
 * @date       2026/09/30
 * @history
 */

#include <QWidget>
#include "QH_global.h"

class QhGradientSliderPrivate;

class QhGradientSlider: public QWidget
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhGradientSlider)

public:
    QhGradientSlider(QWidget *parent = nullptr);
    ~QhGradientSlider();

    QColor selectedColor() const;
    int selectedIndex() const;

    void setSelectColor(const QColor &color);
    void setSelectIndex(int index);

signals:
    void selectedColorChanged(const QColor &color);
    void selectedIndexChanged(int index);

protected:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
};

#endif // QHGRADIENTSLIDER_H
