#ifndef QHSPIN_P_H
#define QHSPIN_P_H

#include <QTimer>
#include "qhspin.h"

class QhSpinPrivate : public QObject
{
    Q_OBJECT

public:
    QhSpinPrivate(QhSpin *p);
    ~QhSpinPrivate();

    QhSpin *p;

    QhSpin::Style style;
    QColor undersideColor = Qt::gray; // 底色
    QColor displayColor = Qt::blue;   // 显示颜色

    int dotNum = 8;          // 圆点数量
    qreal widthRatio = 0.4f; // 宽度比例（圆点时，圆点直径与正方形半径比例）
    qreal maxWidth = 66.0f;  // 最大宽度（圆点时，代表直径）
    qreal minWidth = 10.0f;  // 最小宽度（圆点时，代表直径）

    // 旋转时圆点的信息
    struct DotCircle {
        qreal angle;  // 角度
        QSizeF size;  // 大小
        QColor color; // 颜色
    };

    QTimer timer;                 // 旋转定时器
    QVector<DotCircle> dotCircle; // 圆点的位置信息

    void init();
    void initSizeColor();
    inline qreal minWH();

public slots:
    void updateAngles();
    void updateSizes();
};

#endif // QHSPIN_P_H
