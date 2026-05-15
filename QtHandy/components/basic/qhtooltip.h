#ifndef QHTOOLTIP_H
#define QHTOOLTIP_H

#include <QWidget>
#include "QH_global.h"

class QhToolTipPrivate;

class QTHANDY_EXPORT QhToolTip : public QWidget
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhToolTip)

public:
    /// @brief 气泡框位置
    enum Placement {
        Top,         // 顶部（中心）
        Left,        // 左边（中心）
        Right,       // 右边（中心）
        Bottom,      // 底部（中心）
        TopLeft,     // 顶部靠左
        TopRight,    // 顶部靠右
        BottomLeft,  // 底部靠左
        BottomRight, // 低部靠右
        LeftTop,     // 左边靠顶部
        LeftBottom,  // 左边靠底部
        RightTop,    // 右边靠顶部
        RightBottom, // 右边靠底部
    };

    ~QhToolTip();

    /// @brief 显示文本
    /// @param w: 要显示tooltip的查看
    /// @param placement: 相对w的位置
    /// @param text: 显示文本
    /// @param rect: 显示有效区域
    /// @param msecDisplayTime: 显示时间
    static void showText(
        QWidget *w, Placement placement, const QString &text, const QRect &rect = QRect(), int msecDisplayTime = 0);

    /// @brief 显示文本
    /// @param pos: 显示位置（没有父类）
    /// @param text: 显示文本
    /// @param rect: 显示有效区域
    /// @param msecDisplayTime: 显示时间
    static void showText(const QPoint &pos, const QString &text, const QRect &rect = QRect(), int msecDisplayTime = 0);

    /// @brief 隐藏文本
    static void hideText();

    /// @brief 文本
    static QString text();

protected:
    QhToolTip(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;
};

#endif // QHTOOLTIP_H
