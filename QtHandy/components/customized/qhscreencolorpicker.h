#ifndef QHSCREENCOLORPICKER_H
#define QHSCREENCOLORPICKER_H

/**
 * @file       qhscreencolorpicker.h
 * @brief      屏幕颜色拾取器
 *
 * @author     wmz
 * @date       2026/10/08
 * @history
 */

#include <QWidget>
#include "QH_global.h"

class QhScreenColorPickerPrivate;

class QTHANDY_EXPORT QhScreenColorPicker: public QWidget
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhScreenColorPicker)

public:
    QhScreenColorPicker();
    ~QhScreenColorPicker();

signals:
    void colorPicked(const QColor &color);
    void canceled();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // QHSCREENCOLORPICKER_H
