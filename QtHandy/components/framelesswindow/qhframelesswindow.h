#ifndef QHFRAMELESSWINDOW_H
#define QHFRAMELESSWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QDialog>
#include "QH_global.h"

#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
#define NATIVATEEVENTFUNC_3PARAM_TYPE long
#else
#define NATIVATEEVENTFUNC_3PARAM_TYPE qintptr
#endif

#ifdef Q_OS_LINUX
class X11AbstractNativeEventFilter;
#endif

class QhFramelessWindowPrivate;

class QTHANDY_EXPORT QhFramelessWindow
{
public:
    QhFramelessWindow(QWidget *widget);
    ~QhFramelessWindow();

    /// @brief 初始化是否无边框（圆角边框必须初始化时设置）
    void initFramelessWindow(int borderRadius = 0);

    /// @brief 是否无边框
    bool isFramelessWindow();

    /// @brief 是否可拉升大小
    bool isResizeable();
    /// @brief 是否可移动窗口
    bool isMoveable();
    /// @brief 是否点击标题栏最大化/恢复正常(mac下只会最大化)
    bool isMaxNormalAtTitleBar();
    /// @brief 是否使用系统的关闭、最大化、最小化按钮（mac有效）
    bool isUseMacSystemButtom();

    /// @brief 标题栏高度
    int titleHeight();
    /// @brief 标题栏窗口
    QWidget *titleBar();
    /// @brief 标题栏在子窗口上，可以拖动
    QList<QWidget*> titleBarEnableChilds();
    /// @brief 标题栏在子窗口上，不可以拖动
    QList<QWidget*> titleBarDisableChilds();

    /// @brief 边框宽度
    qreal borderWidth();
    /// @brief 边框圆角
    int borderRadius();
    /// @brief 边框颜色
    QColor borderColor();
    /// @brief 背景颜色
    QColor backgroundColor();

    /// @brief 阴影宽度（windows下使用，配和borderRadius使用变成圆角边框窗口）
    int shadowWidth();

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

    QWidget *widget();

protected:
    QScopedPointer<QhFramelessWindowPrivate> d;
    Q_DISABLE_COPY(QhFramelessWindow)
    friend class QhFramelessWindowPrivate;
};

class QTHANDY_EXPORT QhFramelessMainWindow:
    public QMainWindow, public QhFramelessWindow
{
    Q_OBJECT

public:
    QhFramelessMainWindow(QWidget *parent = nullptr);

    bool nativeEvent(const QByteArray &eventType, void *message, NATIVATEEVENTFUNC_3PARAM_TYPE *result) override;
    bool event(QEvent *e) override;
    void paintEvent(QPaintEvent *e) override;
};

class QTHANDY_EXPORT QhFramelessWidget:
    public QWidget, public QhFramelessWindow
{
    Q_OBJECT

public:
    QhFramelessWidget(QWidget *parent = nullptr);

    bool nativeEvent(const QByteArray &eventType, void *message, NATIVATEEVENTFUNC_3PARAM_TYPE *result) override;
    bool event(QEvent *e) override;
    void paintEvent(QPaintEvent *e) override;
};

class QTHANDY_EXPORT QhFramelessDialog:
    public QDialog, public QhFramelessWindow
{
    Q_OBJECT

public:
    QhFramelessDialog(QWidget *parent = nullptr);

    bool nativeEvent(const QByteArray &eventType, void *message, NATIVATEEVENTFUNC_3PARAM_TYPE *result) override;
    bool event(QEvent *e) override;
    void paintEvent(QPaintEvent *e) override;
};

#endif // QHFRAMELESSWINDOW_H
