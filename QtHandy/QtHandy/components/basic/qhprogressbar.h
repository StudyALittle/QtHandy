#ifndef QHPROGRESSBAR_H
#define QHPROGRESSBAR_H

#include <QProgressBar>
#include "QH_global.h"

class QhProgressBarPrivate;

class QTHANDY_EXPORT QhProgressBar : public QProgressBar
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhProgressBar)
    Q_PROPERTY_EX(QColor, Background)
    Q_PROPERTY_EX(QColor, ChunkBackground)

public:
    /// @brief 进度条类型
    enum Type {
        Default,  // 默认（QProgressBar）
        Line,     // 线性
        Circle,   // 圆环形（进度文本居中）
        Dashboard // 仪表盘
    };

    /// @brief 文本对齐（类型为“线性”有效）
    enum TextAlign {
        AlignFollowText,
        AlignLeft,
        AlignRight,
        AlignCenter,
    };

    /// @brief 渐变色
    struct GradientItem {
        qreal pos;
        QColor color;
    };

    QhProgressBar(QWidget *parent = nullptr);
    ~QhProgressBar();

    /// @brief 类型
    Type type() const;
    /// @brief 文本对齐
    TextAlign textAlign() const;
    /// @brief 圆环最小宽度
    int circleMinWidth() const;
    /// @brief 圆环最大宽度
    int circleMaxWidth() const;
    /// @brief 圆环宽度与圆半径的比例
    qreal circleWidthRatio() const;

    /// @brief 类型
    void setType(Type type);
    /// @brief 文本对齐
    void setTextAlign(TextAlign align);
    /// @brief 圆环最小宽度
    void setCircleMinWidth(int w);
    /// @brief 圆环最大宽度
    void setCircleMaxWidth(int w);
    /// @brief 圆环宽度与圆半径的比例
    void setCircleWidthRatio(qreal ratio);

    /// @brief 进度背景
    QColor getBackground() const;
    /// @brief 进度值背景
    QColor getChunkBackground() const;
    /// @brief 进度渐变色
    QVector<GradientItem> gradients() const;
    /// @brief 渐变色方向（线性类型有效）
    Qt::Orientation gradientOrientation() const;

    /// @brief 进度背景
    void setBackground(const QColor &color);
    /// @brief 进度值背景
    void setChunkBackground(const QColor &color);
    /// @brief 进度渐变色
    void setGradients(const QVector<GradientItem> &items);
    /// @brief 渐变色方向（线性类型有效）
    void setGradientOrientation(Qt::Orientation orientation);

protected:
    void paintEvent(QPaintEvent *e) override;
};

#endif // QHPROGRESSBAR_H
