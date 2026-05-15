#ifndef QHPROGRESSBAR_P_H
#define QHPROGRESSBAR_P_H

#include "qhprogressbar.h"

class QhProgressBarPrivate : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhProgressBarPrivate)

public:
    QhProgressBarPrivate(QhProgressBar *p);
    ~QhProgressBarPrivate();

    QhProgressBar::Type type = QhProgressBar::Default;
    QhProgressBar::TextAlign textAlign = QhProgressBar::AlignFollowText;

    QColor background = QColor(0x12, 0x57, 0x60);         // 进度条背景颜色
    QColor chunkBackground = QColor(0x32, 0xE7, 0xFF);    // 进度条进度颜色
    QVector<QhProgressBar::GradientItem> gradients;       // 渐变色
    Qt::Orientation gradientOrientation = Qt::Horizontal; // 渐变色方向（线性有效）

    qreal circleMinWidth = 6;       // 圆环最小宽度
    qreal circleMaxWidth = 48;      // 圆环最大宽度
    qreal circleWidthRatio = 0.15f; // 圆环宽度与圆半径的比例

    void drawLine(QPainter &p);

    qreal calculateCircularRingWidth(qreal min);
    void setPen(QPainter &p, const QBrush &brush);
    void drawCircle(QPainter &p);
    void drawDashboard(QPainter &p);
    void drawText(QPainter &p);

private:
    QhProgressBar *pBar = nullptr;
};

#endif // QHPROGRESSBAR_P_H
