#ifndef QHQSS_H
#define QHQSS_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QApplication>
#include <QWidget>
#include <functional>
#include "qhqssparser.h"
#include "QH_global.h"

class QhQssPrivate;
class QhQssLoader;

class QTHANDY_EXPORT QhQss: public QObject
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhQss)

public:
    enum PseudoState
    {
        SPS_Normal,
        SPS_Active,         // This state is set when the widget resides in an active window.
        SPS_AdjoinsItem,    // This state is set when the ::branch of a QTreeView is adjacent to an item.
        SPS_Alternate,      // This state is set for every alternate row whe painting the row of a QAbstractItemView when QAbstractItemView::alternatingRowColors() is set to true.
        SPS_Bottom,         // The item is positioned at the bottom. For example, a QTabBar that has its tabs positioned at the bottom.
        SPS_Checked,        // The item is checked. For example, the checked state of QAbstractButton.
        SPS_Closable,       // The items can be closed. For example, the QDockWidget has the QDockWidget::DockWidgetClosable feature turned on.
        SPS_Closed,         // The item is in the closed state. For example, an non-expanded item in a QTreeView
        SPS_Default,        // The item is the default. For example, a default QPushButton or a default action in a QMenu.
        SPS_Disabled ,      // The item is disabled.
        SPS_Editable,       // The QComboBox is editable.
        SPS_EditFocus,      // The item has edit focus (See QStyle::State_HasEditFocus). This state is available only for Qt Extended applications.
        SPS_Enabled,        // The item is enabled.
        SPS_Exclusive,      // The item is part of an exclusive item group. For example, a menu item in a exclusive QActionGroup.
        SPS_First,          // The item is the first (in a list). For example, the first tab in a QTabBar.
        SPS_Flat,           // The item is flat. For example, a flat QPushButton.
        SPS_Floatable,      // The items can be floated. For example, the QDockWidget has the QDockWidget::DockWidgetFloatable feature turned on.
        SPS_Focus,          // The item has input focus.
        SPS_HasChildren,    // The item has children. For example, an item in a QTreeView that has child items.
        SPS_HasSiblings,    // The item has siblings. For example, an item in a QTreeView that siblings.
        SPS_Horizontal,     // The item has horizontal orientation
        SPS_Hover,          // The mouse is hovering over the item.
        SPS_Indeterminate,  // The item has indeterminate state. For example, a QCheckBox or QRadioButton is partially checked.
        SPS_Last,           // The item is the last (in a list). For example, the last tab in a QTabBar.
        SPS_Left,           // The item is positioned at the left. For example, a QTabBar that has its tabs positioned at the left.
        SPS_Maximized,      // The item is maximized. For example, a maximized QMdiSubWindow.
        SPS_Middle,         // The item is in the middle (in a list). For example, a tab that is not in the beginning or the end in a QTabBar.
        SPS_Minimized,      // The item is minimized. For example, a minimized QMdiSubWindow.
        SPS_Movable,        // The item can be moved around. For example, the QDockWidget has the QDockWidget::DockWidgetMovable feature turned on.
        SPS_NoFrame,        // The item has no frame. For example, a frameless QSpinBox or QLineEdit.
        SPS_NonExclusive,   // The item is part of a non-exclusive item group. For example, a menu item in a non-exclusive QActionGroup.
        SPS_Off,            // For items that can be toggled, this applies to items in the "off" state.
        SPS_On,             // For items that can be toggled, this applies to widgets in the "on" state.
        SPS_OnlyOne,        // The item is the only one (in a list). For example, a lone tab in a QTabBar.
        SPS_Open,           // The item is in the open state. For example, an expanded item in a QTreeView, or a QComboBox or QPushButton with an open menu.
        SPS_NextSelected,   // The next item (in a list) is selected. For example, the selected tab of a QTabBar is next to this item.
        SPS_Pressed,        // The item is being pressed using the mouse.
        SPS_PreviousSelected, // The previous item (in a list) is selected. For example, a tab in a QTabBar that is next to the selected tab.
        SPS_ReadOnly,       // The item is marked read only or non-editable. For example, a read only QLineEdit or a non-editable QComboBox.
        SPS_Right,          // The item is positioned at the right. For example, a QTabBar that has its tabs positioned at the right.
        SPS_Selected,       // The item is selected. For example, the selected tab in a QTabBar or the selected item in a QMenu.
        SPS_Top,            // The item is positioned at the top. For example, a QTabBar that has its tabs positioned at the top.
        SPS_Unchecked,      // The item is unchecked.
        SPS_Vertical,       // The item has vertical orientation.
        SPS_Window,         // The widget is a window (i.e top level widget)
    };

    enum SubControl
    {
        SSC_Not = 0,
        SSC_Left,
        SSC_Right
    };

    enum Attribute
    {
        ATTR_Visible,
        ATTR_Alignment,
        ATTR_Pdding,
        ATTR_Width,
        ATTR_Space,
        ATTR_Color,
        ATTR_BackgroundColor,
        ATTR_ImagePath,
        ATTR_ImageColor,
        ATTR_ImageSize,
        ATTR_RelativePos,
    };

    /// @brief relative position
    enum RelativePosition
    {
        NearBorder,
        FollowText
    };

    struct PropertyTypes
    {
        bool visible;

        Qt::Alignment align = Qt::AlignLeft;

        QMargins padding = QMargins(12, 6, 12, 6);
        int space = 6;
        int width = 12;                 // QhLineEdit left\right width

        QColor color;
        QColor backgroundColor;

        QString imagePath;
        QColor imageColor;              // Only svg images are supported
        QSize imageSize;
        RelativePosition relativePos = NearBorder;
    };


    QhQss(QWidget *parent);
    ~QhQss();

    void init(std::function<void()> cbFuncQssReloaded);

    QWidget *widget() const;
    QVector<QhQssParser::Item::Ptr> items();

    QString attributeValue(const QString &subControl,
        const QString &pseudoState, const QString &attributeKey) const;
    QString attributeValue(
        const QString &pseudoState, const QString &attributeKey) const;
    bool containsAttribute(SubControl subControl, PseudoState state, const QString &key) const;
    bool containsAttribute(SubControl subControl, PseudoState state, Attribute key) const;

    /// @brief Get style attributes
    PropertyTypes attributes(SubControl subControl, PseudoState pseudoState);

    /// @brief Set attribute style
    void setPropertyTypes(SubControl subControl, PseudoState state, const PropertyTypes &types);
    void setPropertyTypes(SubControl subControl, const QVector<PseudoState> &states, const PropertyTypes &types);
    void setPropertyTypes(SubControl subControl, const QVector<PseudoState> &states);
    void setPropertyTypes(PseudoState state, const PropertyTypes &types);

    /// @brief Get attribute style
    PropertyTypes propertyTypes(SubControl subControl, PseudoState state) const;
    PropertyTypes propertyTypes(PseudoState state) const;

    /// @brief Does the style attribute exist
    bool containsPropertyTypes(SubControl subControl, PseudoState state) const;
    bool containsPropertyTypes(PseudoState state) const;

    void setDefaultAttribute(SubControl subControl, PseudoState state, const PropertyTypes &src, PropertyTypes &out);

    void readAttribute(SubControl subControl, PseudoState state, QFont &font);

signals:
    void propertyTypesChanged();

public:
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

    /// @brief string "top"... to Qt::Alignment
    static Qt::Alignment stringToAlignment(const QString &str);

    /// @brief string "near-border" or "follow-text" to RelativePosition
    static RelativePosition stringToRelativePosition(const QString &str);

    /// @brief enum PseudoState to string
    static QString stateToString(PseudoState state);

    /// @brief enum SubControl to string
    static QString subControlToString(SubControl sub);

    /// @brief enum Attribute to string
    static QString attributeToString(Attribute attr);
};

#endif // QHQSS_H
