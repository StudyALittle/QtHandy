#ifndef QHCOLORPICKER_P_H
#define QHCOLORPICKER_P_H

#include <QLabel>
#include <QPushButton>
#include "qhlineedit.h"
#include "qhcolorpicker.h"
#include "qhsvpanel.h"
#include "qhhueslider.h"

class QhColorPickerPrivate: public QObject
{
    Q_OBJECT

public:
    QhColorPickerPrivate(QhColorPicker *colorPicker);
    ~QhColorPickerPrivate();

    void init();

    QhColorPicker *colorPicker;

    QLabel *labelColor;
    QLineEdit *lineEditColor;
    QhSVPanel *svPanel;     // SV选择区
    QhHueSlider *hueSlider; // 色相条

public slots:
    void onSVColorChanged(const QColor &color);
    void onHueChanged(qreal hue);
};

#endif // QHCOLORPICKER_P_H
