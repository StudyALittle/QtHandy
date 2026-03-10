#ifndef QHFRAMELESSWINDOW_P_H
#define QHFRAMELESSWINDOW_P_H

#include "qhframelesswindow.h"
#include "qhwidgetmoveresize.h"
#include "QH_global.h"

class QhWidgetMoveResize;

class QhFramelessWindowPrivate: public QObject
{
    Q_OBJECT

    Q_DISABLE_COPY(QhFramelessWindowPrivate)
    Q_DECLARE_PUBLIC(QhFramelessWindow)

public:
    QhFramelessWindowPrivate(QhFramelessWindow *q, QWidget *widget):
        q_ptr(q), widget(widget), moveResizeHelpre(new QhWidgetMoveResize(q))
    { }

    /// @brief 是否无边框
    bool bFramelessWindow = false;

    /// @brief 是否可拉升大小
    bool bResizeable = false;
    /// @brief 是否可移动窗口
    bool bMoveable = true;
    /// @brief 是否点击标题栏最大化/恢复正常(mac下只会最大化)
    bool bMaxNormalAtTitleBar = true;
    /// @brief 是否使用系统的关闭、最大化、最小化按钮（mac有效）
    bool bUseMacSystemButtom = false;

    /// @brief 标题栏高度
    int titleHeight = 0;
    /// @brief 标题栏窗口
    QWidget *titleBar = nullptr;
    /// @brief 标题栏在子窗口上，可以拖动
    QList<QWidget*> titleBarEnableChilds;
    /// @brief 标题栏在子窗口上，不可以拖动
    QList<QWidget*> titleBarDisableChilds;

    /// @brief 边框宽度
    qreal borderWidth = 0;
    /// @brief 边框圆角
    int borderRadius = 0;
    /// @brief 边框颜色
    QColor borderColor;
    /// @brief 背景颜色
    QColor backgroundColor;

    /// @brief 阴影宽度（windows下使用，配和borderRadius使用变成圆角边框窗口）
    int shadowWidth = 0;

    /// @brief 初始化是否无边框（圆角边框必须初始化时设置）
    void initFramelessWindow(int borderRadius = 0);

    /// @brief 是否可拉升大小
    void setResizeable(bool b);
    /// @brief 是否可移动窗口
    void setMoveable(bool b);
    /// @brief 是否点击标题栏最大化/恢复正常(mac下只会最大化)
    void setMaxNormalAtTitleBar(bool b);
    /// @brief 是否使用系统的关闭、最大化、最小化按钮（mac有效）
    void setUseMacSystemButtom(bool b);

    /// @brief 标题栏高度
    void setTitleHeight(int n);
    /// @brief 标题栏窗口
    void setTitleBar(QWidget *w);
    /// @brief 标题栏在子窗口上，可以拖动
    void setTitleBarEnableChilds(const QList<QWidget*> &ws);
    /// @brief 标题栏在子窗口上，不可以拖动
    void setTitleBarDisableChilds(const QList<QWidget*> &ws);

    /// @brief 边框宽度
    void setBorderWidth(qreal n);
    /// @brief 边框圆角
    void setBorderRadius(int n);
    /// @brief 边框颜色
    void setBorderColor(const QColor &color);
    /// @brief 边框颜色
    void setBackgroundColor(const QColor &color);

    /// @brief 阴影宽度（windows下使用，配和borderRadius使用变成圆角边框窗口）
    void setShadowWidth(int n);

    bool nativeEventEx(const QByteArray &eventType, void *message, NATIVATEEVENTFUNC_3PARAM_TYPE *result);
    bool eventEx(QEvent *e);
    void paintEventEx(QPaintEvent *e);

    /// @brief 绘制阴影
    void paintShadowHelper(QPainter *p);
    /// @brief 绘制边框
    void paintBorderHelper(QPainter *p);
    /// @brief 绘制背景
    void paintBackgroundHelper(QPainter *p);

private:
    QhFramelessWindow *const q_ptr;
    QScopedPointer<QhWidgetMoveResize> moveResizeHelpre;
    QWidget *widget;
};

#endif // QHFRAMELESSWINDOW_P_H
