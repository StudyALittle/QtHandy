#ifndef QHSCREENCOLORPICKER_P_H
#define QHSCREENCOLORPICKER_P_H

#include "qhscreencolorpicker.h"

class QhScreenColorPickerPrivate: public QObject
{
    Q_OBJECT

public:
    QhScreenColorPickerPrivate(QhScreenColorPicker *colorPicker);
    ~QhScreenColorPickerPrivate();

    QhScreenColorPicker *colorPicker;

    QTimer        *timer      = nullptr;
    QPoint         cursorPos;
    QColor         currentColor;
    QPixmap        magnifierPixmap;         // 鼠标周围截取的小图
    bool           hasColor   = false;
    bool           captureMode = false;

    // 放大镜参数
    static constexpr int kZoomRadius = 10;  // 截取半径（像素）
    static constexpr int kZoomFactor = 12;  // 放大倍数

    bool eventFilter(QObject *obj, QEvent *event) override;

public slots:
    void updateMagnifier();
    void drawMagnifier(QPainter &p);
};

#endif // QHSCREENCOLORPICKER_P_H
