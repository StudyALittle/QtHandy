#ifndef QHCOLORPICKER_P_H
#define QHCOLORPICKER_P_H

#include <QLabel>
#include <QPushButton>
#include <QButtonGroup>
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

    qreal zoom = 1.0f;
    QColor selectedColor;

    QButtonGroup *buttonGroup;
    QPushButton *buttonMonochrome;      // 单色
    QPushButton *buttonLinearColor;     // 线性
    QhGradientSlider *gradientSlider;   // 渐变色选择器
    QLabel *labelColor;
    QLineEdit *lineEditColor;
    QPushButton *buttonColorAbsorber;   // 吸色器
    QhAlphaSlider *alphaSlider;         // 透明度条
    QLineEdit *lineEditAlpha;
    QhSVPanel *svPanel;                 // SV选择区
    QhHueSlider *hueSlider;             // 色相条

    void setZoom(qreal zoom);
    void setColor(const QColor &color);

public slots:
    void onButtonToggled(QAbstractButton *button, bool checked);
    void onEditColorTextChanged(const QString &text);
    void onAlphaChanged(qreal alpha);
    void onSVSelectedColorChanged(const QColor &color);
    void onHueChanged(qreal hue);
    void onGradientSelectedColorChanged(const QColor &color);
};

#endif // QHCOLORPICKER_P_H
