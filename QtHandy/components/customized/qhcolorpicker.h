#ifndef QHCOLORPICKER_H
#define QHCOLORPICKER_H

/**
 * @file       qhcolorpicker.h
 * @brief      颜色选择器，支持渐变色
 *
 * @author     wmz
 * @date       2026/09/29
 * @history
 */

#include <QWidget>
#include "QH_global.h"

class QhColorPickerPrivate;

class QTHANDY_EXPORT QhColorPicker: public QWidget
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhColorPicker)

public:
    QhColorPicker(QWidget *parent = nullptr);
    ~QhColorPicker();

    /// @brief 设置界面缩放倍数（高分辨率）
    void setZoom(qreal zoom);

    /// @brief 设置颜色
    void setColor(const QColor &color);

    /// @brief 界面缩放倍数
    qreal zoom() const;
};

#endif // QHCOLORPICKER_H
