#ifndef QHCOLORPICKER_P_H
#define QHCOLORPICKER_P_H

#include <QLabel>
#include <QPushButton>
#include "qhlineedit.h"
#include "qhcolorpicker.h"
#include "qhsvpanel.h"
#include "qhhueslider.h"
#include "qhalphaslider.h"
#include "qhgradientslider.h"

class QhColorPickerPrivate: public QObject
{
    Q_OBJECT

public:
    QhColorPickerPrivate(QhColorPicker *colorPicker);
    ~QhColorPickerPrivate();

    void init();

    QhColorPicker *colorPicker;

    QColor selectedColor;

    QhGradientSlider *gradientSlider;   // 渐变色选择器
    QLabel *labelColor;
    QLineEdit *lineEditColor;
    QhAlphaSlider *alphaSlider; // 透明度条
    QhSVPanel *svPanel;         // SV选择区
    QhHueSlider *hueSlider;     // 色相条

    void setColor(const QColor &color);

public slots:
    void onEditColorTextChanged(const QString &text);
    void onSVSelectedColorChanged(const QColor &color);
    void onHueChanged(qreal hue);
    void onGradientSelectedColorChanged(const QColor &color);
};

#endif // QHCOLORPICKER_P_H
