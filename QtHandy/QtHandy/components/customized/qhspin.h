#ifndef QHSPIN_H
#define QHSPIN_H

/**
 * @file       qhspin.h
 * @brief      旋转（一般用于加载控件）
 *
 * @author     wmz
 * @date       2026/03/17
 * @history
 */

#include <QLabel>
#include <QColor>
#include "QH_global.h"

class QhSpinPrivate;

class QTHANDY_EXPORT QhSpin : public QLabel
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhSpin)

public:
    enum Style {
        StyleLabel,        // 原生QLabel
        StyleDotSS,        // 圆点旋转(每个圆点大小一样)
        StyleDotDS,        // 圆点旋转(每个圆点大小不一样)
        StyleRing,         // 圆环加载 DOTO: 待实现
        StyleHorizonLine,  // 水平线 DOTO: 待实现
        StyleVerticalLine, // 垂直线 DOTO: 待实现
    };

    QhSpin(QWidget *parent = nullptr);
    QhSpin(Style style, QWidget *parent = nullptr);
    ~QhSpin();

    /// @brief 设置样式
    void setStyle(Style style);

    /// @brief 设置颜色 displayColor: 显示颜色 undersideColor: 底色
    void setColor(const QColor &displayColor, const QColor &undersideColor);

    /// @brief 设置圆点数量
    void setDotNum(int dotNum);

    /// @brief 设置宽度比例（圆点时，圆点直径与正方形半径比例）
    void setWidthRatio(qreal wr);

    /// @brief 设置最大宽度（圆点时，代表直径）
    void setMaxWidth(int maxw);

    /// @brief 设置最小宽度（圆点时，代表直径）
    void setMinWidth(int minw);

    /// @brief 开始旋转
    void start(int ms = 200);

    /// @brief 停止旋转
    void stop();

protected:
    void paintEvent(QPaintEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;
};

#endif // QHSPIN_H
