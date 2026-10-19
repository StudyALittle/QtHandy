#include "qhstyle.h"
#include <QPainter>
#include <QApplication>
#include <QWidget>
#include <QDebug>
#include "qhfileutil.h"

QhStyle::QhStyle()
{
}

void QhStyle::setQss(const QStringList &qssFiles)
{
    QString qss;
    for (auto &fileName : qssFiles) qss.append(QhFileUtil::readFileText(fileName));

#ifdef QT_DEBUG
    qDebug() << "Qss: " << qss;
#endif
    qApp->setStyleSheet(qss);
}

void QhStyle::setQss(QWidget *w, const QStringList &qssFiles)
{
    QString qss;
    for (auto &fileName : qssFiles) qss.append(QhFileUtil::readFileText(fileName));
    w->setStyleSheet(qss);
}

QMargins QhStyle::stringToMargins(const QString &str)
{
    // examples:
    // 10px;                /* 10px on all sides */
    // 10px 20px;           /* 10px for top/bottom, 20px for left/right */
    // 10px 20px 30px;      /* 10px top, 20px left/right, 30px bottom */
    // 10px 20px 30px 40px; /* 10px top, 20px right, 30px bottom, 40px left */
    QMargins mgs;
    auto ss = str.split(" ", QString::SkipEmptyParts);
    if (ss.size() == 1) {
        int val = stringToQreal(ss.first());
        return QMargins(val, val, val, val);
    } else if (ss.size() == 2) {
        int val1 = stringToQreal(ss.first());
        int val2 = stringToQreal(ss.last());
        return QMargins(val2, val1, val2, val1);
    } else if (ss.size() == 3) {
        int val1 = stringToQreal(ss.first());
        int val2 = stringToQreal(ss.at(1));
        int val3 = stringToQreal(ss.last());
        return QMargins(val2, val1, val2, val3);
    } else if (ss.size() == 4) {
        int val1 = stringToQreal(ss.first());
        int val2 = stringToQreal(ss.at(1));
        int val3 = stringToQreal(ss.at(2));
        int val4 = stringToQreal(ss.last());
        return QMargins(val4, val1, val2, val3);
    }
    return mgs;
}

QString QhStyle::marginsToString(const QMargins &mgs)
{
    return QString("%1px %2px %3px %4px").arg(mgs.top()).arg(mgs.right()).arg(mgs.bottom()).arg(mgs.left());
}

qreal QhStyle::stringToQreal(QString str)
{
    if (str.isEmpty())
        return 0;

    return str.remove("px").toDouble();
}

bool QhStyle::stringToBool(const QString &str)
{
    if (str == "false" || str == "0")
        return false;
    return true;
}

QColor QhStyle::stringToColor(const QString &str)
{
    return QColor(str.simplified());
}

Qt::Alignment QhStyle::stringToAlignment(const QString &str)
{
    Qt::Alignment align;

    QString newStr = str.simplified();
    if (newStr.contains("top"))
        align | Qt::AlignTop;
    if (newStr.contains("bottom"))
        align | Qt::AlignBottom;
    if (newStr.contains("left"))
        align | Qt::AlignLeft;
    if (newStr.contains("right"))
        align | Qt::AlignRight;
    if (newStr.contains("center"))
        align | Qt::AlignCenter;

    return align;
}

QString QhStyle::stateToString(PseudoState state)
{
    switch (state) {
    case SPS_Active: {
        return "active";
    }
    case SPS_AdjoinsItem: {
        return "adjoins-item";
    }
    case SPS_Alternate: {
        return "alternate";
    }
    case SPS_Bottom: {
        return "bottom";
    }
    case SPS_Checked: {
        return "checked";
    }
    case SPS_Closable: {
        return "closable";
    }
    case SPS_Closed: {
        return "closed";
    }
    case SPS_Default: {
        return "default";
    }
    case SPS_Disabled: {
        return "disabled";
    }
    case SPS_Editable: {
        return "editable";
    }
    case SPS_EditFocus: {
        return "edit-focus";
    }
    case SPS_Enabled: {
        return "enabled";
    }
    case SPS_Exclusive: {
        return "exclusive";
    }
    case SPS_First: {
        return "first";
    }
    case SPS_Flat: {
        return "flat";
    }
    case SPS_Floatable: {
        return "floatable";
    }
    case SPS_Focus: {
        return "focus";
    }
    case SPS_HasChildren: {
        return "has-children";
    }
    case SPS_HasSiblings: {
        return "has-siblings";
    }
    case SPS_Horizontal: {
        return "horizontal";
    }
    case SPS_Hover: {
        return "hover";
    }
    case SPS_Indeterminate: {
        return "indeterminate";
    }
    case SPS_Last: {
        return "last";
    }
    case SPS_Left: {
        return "left";
    }
    case SPS_Maximized: {
        return "maximized";
    }
    case SPS_Middle: {
        return "middle";
    }
    case SPS_Minimized: {
        return "minimized";
    }
    case SPS_Movable: {
        return "movable";
    }
    case SPS_NoFrame: {
        return "no-frame";
    }
    case SPS_NonExclusive: {
        return "non-exclusive";
    }
    case SPS_Off: {
        return "off";
    }
    case SPS_On: {
        return "on";
    }
    case SPS_OnlyOne: {
        return "only-one";
    }
    case SPS_Open: {
        return "open";
    }
    case SPS_NextSelected: {
        return "next-selected";
    }
    case SPS_Pressed: {
        return "pressed";
    }
    case SPS_PreviousSelected: {
        return "previous-selected";
    }
    case SPS_ReadOnly: {
        return "read-only";
    }
    case SPS_Right: {
        return "right";
    }
    case SPS_Selected: {
        return "selected";
    }
    case SPS_Top: {
        return "top";
    }
    case SPS_Unchecked: {
        return "unchecked";
    }
    case SPS_Vertical: {
        return "vertical";
    }
    case SPS_Window: {
        return "window";
    }
    default:
        return QString();
    }
}

void QhStyle::drawIndicatorRing(QPainter *p, const QPointF &center, const QColor &color, qreal radius, qreal rw)
{
    qreal gr = 1.5f;
    qreal rr = rw / 2.0f;

    // 外圈阴影
    p->setPen(QPen(QColor(0, 0, 0, 20), gr * 2.0f));
    p->setBrush(Qt::NoBrush);
    p->drawEllipse(center, radius - gr, radius - gr);

    // 外圈白色
    p->setPen(QPen(QColor(0xFF, 0xFF, 0xFF), rw));
    p->drawEllipse(center, radius - rr - gr, radius - rr - gr);

    // 内圈显示当前 alpha 下的颜色
    p->setPen(Qt::NoPen);
    p->setBrush(color);
    p->drawEllipse(center, radius - rw, radius - rw);
}
