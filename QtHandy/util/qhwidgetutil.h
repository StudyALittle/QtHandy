#ifndef QHWIDGETUTIL_H
#define QHWIDGETUTIL_H

#include <QScreen>
#include <QWidget>
#include <QWindow>
#include <QAbstractButton>
#include "QH_global.h"

class QTHANDY_EXPORT QhWidgetUtil
{
public:
    /// @brief 移动窗口到屏幕中间
    static void moveToScreenCenter(QWidget *w, QScreen *screen = nullptr);

    /// @brief 返回顶层窗口（没有父类的窗口）
    static QWidget *topParentWidget(QWidget *w);

    /// @brief 判断parent是不是w的父窗口 (w == parent 时返回true)
    static bool isParentWidget(QWidget *parent, QWidget *w);

    /// @brief 在窗口下面的屏幕
    static QScreen *screenUnderWidget(QWidget *w);

    /// @brief 激活窗口
    static void activateWindow(QWidget *w);

    /// @brief 刷新qss样式
    static void updateQssStyle(QWidget *w);

    /// @brief 刷新qss样式
    static void updateQssStyles(const QList<QWidget*> &ws);

    /// @brief 清除layout下的所有布局和窗口
    /// @param layout：要清除的布局器
    /// @param bDelWidget：是否删除窗口
    /// @param ignoreDelLys：不删除的布局器
    /// @return 返回布局器中的widget
    static QList<QWidget*> clearLayout(
            QLayout *layout, bool bDelWidget = true,
            const QList<QLayout*> &ignoreDelLys = {});

    /// 返回布局器全部窗口
    static QList<QWidget*> layoutWidgets(QLayout *layout);

    /// 如果qss样式不生效，需要在paintEvent事件中调用此函数
    static void paintEventQssStyleReset(QWidget *w);

    /// @brief w相对于最顶层父类topw的位置
    static QPoint posAtTopWidget(QWidget *w, QWidget **topw = nullptr);

    /// @brief 隐藏窗口时保留大小
    static void hideRetainSize(QWidget *w);

    /// @brief 设置按钮焦点
    static void setButtonFocus(QAbstractButton *btn,
        const QList<QKeySequence> &keySequences = {
            QKeySequence::InsertParagraphSeparator,
            Qt::Key_Enter, Qt::Key_Return});

    /// @brief 删除layout的item
    static void layoutDestroyItemAt(QLayout *ly, int index);
};

#endif // QHWIDGETUTIL_H
