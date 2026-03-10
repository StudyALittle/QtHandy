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
    /**
     * @brief moveToScreenCenter：移动窗口到屏幕中间
     * @param w
     * @param screen
     */
    static void moveToScreenCenter(QWidget *w, QScreen *screen = nullptr);

    /**
     * @brief topParentWidget：顶层窗口（没有父类的窗口）
     * @param w
     * @return
     */
    static QWidget *topParentWidget(QWidget *w);

    /**
     * @brief isParentWidget：是不是父窗口
     * @param parent：父窗口
     * @param w：判断是不是parent的子窗口
     * @return （parent == w,返回true）
     */
    static bool isParentWidget(QWidget *parent, QWidget *w);

    /**
     * @brief screenUnderWidget：窗口下面的屏幕
     * @param w
     * @return
     */
    static QScreen *screenUnderWidget(QWidget *w);

    /**
     * @brief activateWindow：激活窗口
     * @param w
     */
    static void activateWindow(QWidget *w);

    /**
     * @brief updateQssStyle：刷新qss样式
     * @param w
     */
    static void updateQssStyle(QWidget *w);

    /**
     * @brief updateQssStyles：刷新qss样式
     * @param ws
     */
    static void updateQssStyles(const QList<QWidget*> &ws);

    /**
     * @brief clearLayout：清除layout下的所有布局和窗口
     * @param layout：要清除的布局器
     * @param bDelWidget：是否删除窗口
     * @param ignoreDelLys：不删除的布局器
     * @return 返回布局器中的widget
     */
    static QList<QWidget*> clearLayout(
            QLayout *layout, bool bDelWidget = true,
            const QList<QLayout*> &ignoreDelLys = {});

    /**
     * @brief layoutWidgets：返回布局器全部窗口
     * @param layout
     * @return
     */
    static QList<QWidget*> layoutWidgets(QLayout *layout);

    /**
     * @brief paintEventQssStyleEx：如果qss样式不生效，需要在paintEvent事件中调用此函数
     * @param widget：窗口句柄
     */
    static void paintEventQssStyleReset(QWidget *w);

    /**
     * @brief posAtTopWidget：w相对于最顶层父类topw的位置
     * @param w
     * @param topw
     * @return
     */
    static QPoint posAtTopWidget(QWidget *w, QWidget **topw = nullptr);

    /**
     * @brief hideRetainSize：隐藏窗口时保留大小
     * @param w
     */
    static void hideRetainSize(QWidget *w);

    /**
     * @brief setButtonFocus：设置按钮焦点
     * @param btn
     */
    static void setButtonFocus(QAbstractButton *btn,
        const QList<QKeySequence> &keySequences = {
            QKeySequence::InsertParagraphSeparator,
            Qt::Key_Enter, Qt::Key_Return});
};

#endif // QHWIDGETUTIL_H
