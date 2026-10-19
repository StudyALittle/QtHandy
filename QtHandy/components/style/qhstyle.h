#ifndef QHSTYLE_H
#define QHSTYLE_H

/**
 * @file       qhstyle.h
 * @brief      样式器
 *
 * @author     wmz
 * @date       2026/09/30
 * @history
 */

#include "QH_global.h"

class QTHANDY_EXPORT QhStyle
{
public:
    enum PseudoState {
        SPS_Normal,
        SPS_Active,      // This state is set when the widget resides in an active window.
        SPS_AdjoinsItem, // This state is set when the ::branch of a QTreeView is adjacent to an item.
        SPS_Alternate,   // This state is set for every alternate row whe painting the row of a QAbstractItemView when
                         // QAbstractItemView::alternatingRowColors() is set to true.
        SPS_Bottom,  // The item is positioned at the bottom. For example, a QTabBar that has its tabs positioned at the
                     // bottom.
        SPS_Checked, // The item is checked. For example, the checked state of QAbstractButton.
        SPS_Closable,  // The items can be closed. For example, the QDockWidget has the QDockWidget::DockWidgetClosable
                       // feature turned on.
        SPS_Closed,    // The item is in the closed state. For example, an non-expanded item in a QTreeView
        SPS_Default,   // The item is the default. For example, a default QPushButton or a default action in a QMenu.
        SPS_Disabled,  // The item is disabled.
        SPS_Editable,  // The QComboBox is editable.
        SPS_EditFocus, // The item has edit focus (See QStyle::State_HasEditFocus). This state is available only for Qt
                       // Extended applications.
        SPS_Enabled,   // The item is enabled.
        SPS_Exclusive, // The item is part of an exclusive item group. For example, a menu item in a exclusive
                       // QActionGroup.
        SPS_First,     // The item is the first (in a list). For example, the first tab in a QTabBar.
        SPS_Flat,      // The item is flat. For example, a flat QPushButton.
        SPS_Floatable, // The items can be floated. For example, the QDockWidget has the
                       // QDockWidget::DockWidgetFloatable feature turned on.
        SPS_Focus,     // The item has input focus.
        SPS_HasChildren,   // The item has children. For example, an item in a QTreeView that has child items.
        SPS_HasSiblings,   // The item has siblings. For example, an item in a QTreeView that siblings.
        SPS_Horizontal,    // The item has horizontal orientation
        SPS_Hover,         // The mouse is hovering over the item.
        SPS_Indeterminate, // The item has indeterminate state. For example, a QCheckBox or QRadioButton is partially
                           // checked.
        SPS_Last,          // The item is the last (in a list). For example, the last tab in a QTabBar.
        SPS_Left,      // The item is positioned at the left. For example, a QTabBar that has its tabs positioned at the
                       // left.
        SPS_Maximized, // The item is maximized. For example, a maximized QMdiSubWindow.
        SPS_Middle, // The item is in the middle (in a list). For example, a tab that is not in the beginning or the end
                    // in a QTabBar.
        SPS_Minimized,    // The item is minimized. For example, a minimized QMdiSubWindow.
        SPS_Movable,      // The item can be moved around. For example, the QDockWidget has the
                          // QDockWidget::DockWidgetMovable feature turned on.
        SPS_NoFrame,      // The item has no frame. For example, a frameless QSpinBox or QLineEdit.
        SPS_NonExclusive, // The item is part of a non-exclusive item group. For example, a menu item in a non-exclusive
                          // QActionGroup.
        SPS_Off,          // For items that can be toggled, this applies to items in the "off" state.
        SPS_On,           // For items that can be toggled, this applies to widgets in the "on" state.
        SPS_OnlyOne,      // The item is the only one (in a list). For example, a lone tab in a QTabBar.
        SPS_Open, // The item is in the open state. For example, an expanded item in a QTreeView, or a QComboBox or
                  // QPushButton with an open menu.
        SPS_NextSelected, // The next item (in a list) is selected. For example, the selected tab of a QTabBar is next
                          // to this item.
        SPS_Pressed,      // The item is being pressed using the mouse.
        SPS_PreviousSelected, // The previous item (in a list) is selected. For example, a tab in a QTabBar that is next
                              // to the selected tab.
        SPS_ReadOnly,         // The item is marked read only or non-editable. For example, a read only QLineEdit or a
                              // non-editable QComboBox.
        SPS_Right,    // The item is positioned at the right. For example, a QTabBar that has its tabs positioned at the
                      // right.
        SPS_Selected, // The item is selected. For example, the selected tab in a QTabBar or the selected item in a
                      // QMenu.
        SPS_Top, // The item is positioned at the top. For example, a QTabBar that has its tabs positioned at the top.
        SPS_Unchecked, // The item is unchecked.
        SPS_Vertical,  // The item has vertical orientation.
        SPS_Window,    // The widget is a window (i.e top level widget)
    };

    QhStyle();

    static void setQss(const QStringList &qssFiles);
    static void setQss(QWidget *w, const QStringList &qssFiles);

    /// @brief string "0 0 0 0" or "0px 0px 0px 0px" to QMargins
    static QMargins stringToMargins(const QString &str);

    /// @brief string "0 0" or "0px 0px" to QSize
    static QSize stringToSize(const QString &str);

    /// QMargins to string "0px 0px 0px 0px"
    static QString marginsToString(const QMargins &mgs);

    /// @brief string "0" or "0px" to qreal
    static qreal stringToQreal(QString str);

    /// @brief string "false", "true", "0", and not equal to zero to bool
    static bool stringToBool(const QString &str);

    /// @brief string "#FFFFFF" or "red" to QColor
    static QColor stringToColor(const QString &str);

    /// @brief enum PseudoState to string
    static QString stateToString(PseudoState state);

    /// @brief string "top"... to Qt::Alignment
    static Qt::Alignment stringToAlignment(const QString &str);

    /// @brief 绘制指示器圆环
    /// @param p: QPainter
    /// @param center: 圆中心点
    /// @param color: 填充颜色
    /// @param radius: 圆半径
    /// @param rw: 圆环宽度
    static void drawIndicatorRing(
        QPainter *p, const QPointF &center, const QColor &color, qreal radius, qreal rw = 4.0f);
};

#endif // QHSTYLE_H
