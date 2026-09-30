#ifndef QHSVPANEL_H
#define QHSVPANEL_H

/**
 * @file       qhsvpanel.h
 * @brief      SV（饱和度-亮度）选择区
 *
 * @author     wmz
 * @date       2026/09/29
 * @history
 */

#include <QWidget>
#include "QH_global.h"

class QhSVPanelPrivate;

class QTHANDY_EXPORT QhSVPanel: public QWidget
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhSVPanel)

public:
    QhSVPanel(QWidget *parent = nullptr);
    ~QhSVPanel();

    /// @brief hue
    qreal hue() const;

    /// @brief saturation
    qreal saturation() const;

    /// @brief value
    qreal value() const;

    /// @brief 选中颜色
    QColor selectedColor() const;

    /// @brief 选中位置
    QPointF selectedPos() const;

    /// @brief 设置选中位置
    void setSelectPos(const QPointF &pos);

    QPointF posFromColor(const QColor &color) const;

signals:
    /// @brief 选中颜色变化
    void selectedColorChanged(const QColor &color);

public slots:
    /// 设置hue
    void setHue(qreal h);

    /// @brief 设置颜色
    void setColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
};

#endif // QHSVPANEL_H
