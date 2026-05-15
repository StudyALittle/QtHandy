#include "qhqss.h"
#include "qhqss_p.h"
#include "qhfileutil.h"

#define QSS_PATH(FileName) QString(":/QhResource/qss/%1.css").arg(FileName)

QhQss::QhQss(QWidget *parent):
    QObject(parent),
    d(new QhQssPrivate(this, parent))
{

}

QhQss::~QhQss()
{

}

void QhQss::init(std::function<void ()> cbFuncQssReloaded)
{
    d->init(cbFuncQssReloaded);
}

QWidget *QhQss::widget() const
{
    return d->widget;
}

QVector<QhQssParser::Item::Ptr> QhQss::items()
{
    return d->qssItems;
}

QString QhQss::attributeValue(
    const QString &subControl, const QString &pseudoState, const QString &attribute) const
{
    return QhQssParser::attributeValue(
        d->widget, d->qssItems, subControl, pseudoState, attribute);
}

QString QhQss::attributeValue(const QString &pseudoState, const QString &attribute) const
{
    return QhQssParser::attributeValue(
        d->widget, d->qssItems, QString(), pseudoState, attribute);
}

bool QhQss::containsAttribute(SubControl subControl, PseudoState state, const QString &key) const
{
    return QhQssParser::containsAttribute(
        d->widget, d->qssItems, subControlToString(subControl), stateToString(state), key);
}

bool QhQss::containsAttribute(SubControl subControl, PseudoState state, Attribute key) const
{
    return QhQssParser::containsAttribute(
        d->widget, d->qssItems, subControlToString(subControl), stateToString(state), attributeToString(key));
}

#define SET_TYPES(Value, StrKey, Func) \
{ \
    QString str = attributeValue(strSub, strState, StrKey); \
    if (!str.isEmpty()) \
        Value = Func(str); \
}

QhQss::PropertyTypes QhQss::attributes(SubControl subControl, PseudoState pseudoState)
{
    PropertyTypes types;

    QString strSub = subControlToString(subControl);
    QString strState = stateToString(pseudoState);

    SET_TYPES(types.visible, "visible", stringToBool)
    SET_TYPES(types.align, "alignment", stringToAlignment)
    SET_TYPES(types.padding, "padding", stringToMargins)
    SET_TYPES(types.width, "width", stringToQreal)
    SET_TYPES(types.space, "space", stringToQreal)
    SET_TYPES(types.color, "color", stringToColor)
    SET_TYPES(types.backgroundColor, "background-color", stringToColor)
    SET_TYPES(types.imagePath, "image-path", )
    SET_TYPES(types.imageColor, "image-color", stringToColor)
    SET_TYPES(types.imageSize, "image-size", stringToSize)
    SET_TYPES(types.relativePos, "relative-pos", stringToRelativePosition)

    return types;
}

QMargins QhQss::stringToMargins(const QString &str)
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

QSize QhQss::stringToSize(const QString &str)
{
    QSize size;
    auto ss = str.split(" ", QString::SkipEmptyParts);
    if (ss.size() == 1) {
        int val = stringToQreal(ss.first());
        size = QSize(val, val);
    } else if (ss.size() >= 2) {
        int val1 = stringToQreal(ss.first());
        int val2 = stringToQreal(ss.last());
        size = QSize(val1, val2);
    }
    return size;
}

QString QhQss::marginsToString(const QMargins &mgs)
{
    return QString("%1px %2px %3px %4px")
        .arg(mgs.top()).arg(mgs.right())
        .arg(mgs.bottom()).arg(mgs.left());
}

qreal QhQss::stringToQreal(QString str)
{
    if (str.isEmpty())
        return 0;

    return str.remove("px").toDouble();
}

bool QhQss::stringToBool(const QString &str)
{
    if (str == "false" || str == "0")
        return false;
    return true;
}

QColor QhQss::stringToColor(const QString &str)
{
    return QColor(str.simplified());
}

Qt::Alignment QhQss::stringToAlignment(const QString &str)
{
    Qt::Alignment align;

    QString newStr = str.simplified();
    if (newStr.contains("top")) align | Qt::AlignTop;
    if (newStr.contains("bottom")) align | Qt::AlignBottom;
    if (newStr.contains("left")) align | Qt::AlignLeft;
    if (newStr.contains("right")) align | Qt::AlignRight;
    if (newStr.contains("center")) align | Qt::AlignCenter;

    return align;
}

QhQss::RelativePosition QhQss::stringToRelativePosition(const QString &str)
{
    // "near-border" or "follow-text"
    QString newStr = str.simplified();
    if (newStr == "near-border")
        return NearBorder;
    else
        return FollowText;
}

QString QhQss::stateToString(PseudoState state)
{
    switch (state) {
    case SPS_Active:        { return "active"; }
    case SPS_AdjoinsItem:   { return "adjoins-item"; }
    case SPS_Alternate:     { return "alternate"; }
    case SPS_Bottom:        { return "bottom"; }
    case SPS_Checked:       { return "checked"; }
    case SPS_Closable:      { return "closable"; }
    case SPS_Closed:        { return "closed"; }
    case SPS_Default:       { return "default"; }
    case SPS_Disabled:      { return "disabled"; }
    case SPS_Editable:      { return "editable"; }
    case SPS_EditFocus:     { return "edit-focus"; }
    case SPS_Enabled:       { return "enabled"; }
    case SPS_Exclusive:     { return "exclusive"; }
    case SPS_First:         { return "first"; }
    case SPS_Flat:          { return "flat"; }
    case SPS_Floatable:     { return "floatable"; }
    case SPS_Focus:         { return "focus"; }
    case SPS_HasChildren:   { return "has-children"; }
    case SPS_HasSiblings:   { return "has-siblings"; }
    case SPS_Horizontal:    { return "horizontal"; }
    case SPS_Hover:         { return "hover"; }
    case SPS_Indeterminate: { return "indeterminate"; }
    case SPS_Last:          { return "last"; }
    case SPS_Left:          { return "left"; }
    case SPS_Maximized:     { return "maximized"; }
    case SPS_Middle:        { return "middle"; }
    case SPS_Minimized:     { return "minimized"; }
    case SPS_Movable:       { return "movable"; }
    case SPS_NoFrame:       { return "no-frame"; }
    case SPS_NonExclusive:  { return "non-exclusive"; }
    case SPS_Off:           { return "off"; }
    case SPS_On:            { return "on"; }
    case SPS_OnlyOne:       { return "only-one"; }
    case SPS_Open:          { return "open"; }
    case SPS_NextSelected:  { return "next-selected"; }
    case SPS_Pressed:       { return "pressed"; }
    case SPS_PreviousSelected: { return "previous-selected"; }
    case SPS_ReadOnly:      { return "read-only"; }
    case SPS_Right:         { return "right"; }
    case SPS_Selected:      { return "selected"; }
    case SPS_Top:           { return "top"; }
    case SPS_Unchecked:     { return "unchecked"; }
    case SPS_Vertical:      { return "vertical"; }
    case SPS_Window:        { return "window"; }
    default: return QString();
    }
}

QString QhQss::subControlToString(SubControl sub)
{
    switch (sub) {
    case SSC_Left: { return "left"; }
    case SSC_Right: { return "right"; }
    default: return QString();
    }
}

QString QhQss::attributeToString(Attribute attr)
{
    switch (attr) {
    case ATTR_Visible:      { return "visible"; }
    case ATTR_Alignment:    { return "alignment"; }
    case ATTR_Pdding:       { return "pdding"; }
    case ATTR_Width:        { return "width"; }
    case ATTR_Space:        { return "space"; }
    case ATTR_Color:        { return "color"; }
    case ATTR_BackgroundColor: { return "background-color"; }
    case ATTR_ImagePath:    { return "image-path"; }
    case ATTR_ImageColor:   { return "image-color"; }
    case ATTR_ImageSize:    { return "image-size"; }
    case ATTR_RelativePos:  { return "relative-pos"; }
    default: break;
    }
    return QString();
}

void QhQss::setPropertyTypes(SubControl subControl, PseudoState state, const PropertyTypes &types)
{
    d->propertyTypes[subControl][state] = types;
    emit propertyTypesChanged();
}

void QhQss::setPropertyTypes(SubControl subControl, const QVector<PseudoState> &states, const PropertyTypes &types)
{
    for (auto state: states)
        d->propertyTypes[subControl][state] = types;
    emit propertyTypesChanged();
}

void QhQss::setPropertyTypes(SubControl subControl, const QVector<PseudoState> &states)
{
    auto typeNormal = attributes(subControl, QhQss::SPS_Normal);
    d->propertyTypes[subControl][QhQss::SPS_Normal] = typeNormal;

    for (auto state: states) {
        if (state == QhQss::SPS_Normal)
            continue;

        auto typeinfo = attributes(subControl, state);
        setDefaultAttribute(subControl, state, typeNormal, typeinfo);
        d->propertyTypes[subControl][state] = typeinfo;
    }
    emit propertyTypesChanged();
}

void QhQss::setPropertyTypes(PseudoState state, const PropertyTypes &types)
{
    d->propertyTypes[SSC_Not][state] = types;
    emit propertyTypesChanged();
}

QhQss::PropertyTypes QhQss::propertyTypes(SubControl subControl, PseudoState state) const
{
    if (containsPropertyTypes(subControl, state))
        return d->propertyTypes[subControl][state];
    return PropertyTypes();
}

QhQss::PropertyTypes QhQss::propertyTypes(PseudoState state) const
{
    return propertyTypes(SSC_Not, state);
}

bool QhQss::containsPropertyTypes(SubControl subControl, PseudoState state) const
{
    return (d->propertyTypes.contains(subControl)
        && d->propertyTypes[subControl].contains(state)) ? true : false;
}

bool QhQss::containsPropertyTypes(PseudoState state) const
{
    return containsPropertyTypes(SSC_Not, state);
}

void QhQss::setDefaultAttribute(SubControl subControl, PseudoState state, const PropertyTypes &src, PropertyTypes &out)
{
    if (!containsAttribute(subControl, state, QhQss::ATTR_Visible))
        out.visible = src.visible;
    if (!containsAttribute(subControl, state, QhQss::ATTR_Alignment))
        out.align = src.align;
    if (!containsAttribute(subControl, state, QhQss::ATTR_Pdding))
        out.padding = src.padding;
    if (!containsAttribute(subControl, state, QhQss::ATTR_Width))
        out.width = src.width;
    if (!containsAttribute(subControl, state, QhQss::ATTR_Space))
        out.space = src.space;
    if (!containsAttribute(subControl, state, QhQss::ATTR_Color))
        out.color = src.color;
    if (!containsAttribute(subControl, state, QhQss::ATTR_BackgroundColor))
        out.backgroundColor = src.backgroundColor;
    if (!containsAttribute(subControl, state, QhQss::ATTR_ImagePath))
        out.imagePath = src.imagePath;
    if (!containsAttribute(subControl, state, QhQss::ATTR_ImageColor))
        out.imageColor = src.imageColor;
    if (!containsAttribute(subControl, state, QhQss::ATTR_ImageSize))
        out.imageSize = src.imageSize;
    if (!containsAttribute(subControl, state, QhQss::ATTR_RelativePos))
        out.relativePos = src.relativePos;
}

void QhQss::readAttribute(SubControl subControl, PseudoState state, QFont &font)
{
    // font: bold(weight) italic(style) large(size) "Times New Roman"(family)
    // font-family
    // font-size
    // font-style
    // font-weight

    if (containsAttribute(subControl, state, "font-family")) {
        font.setFamily(attributeValue(
            QhQss::stateToString(state), "font-family"));
    } else if (state != SPS_Normal
            && containsAttribute(subControl, SPS_Normal, "font-family")) {
        font.setFamily(attributeValue(
            QhQss::stateToString(state), "font-family"));
    }

    if (containsAttribute(subControl, state, "font-size")) {
        font.setPixelSize(QhQss::stringToQreal(attributeValue(
            QhQss::stateToString(state), "font-size")));
    } else if (state != SPS_Normal
            && containsAttribute(subControl, SPS_Normal, "font-size")) {
        font.setPixelSize(QhQss::stringToQreal(attributeValue(
            QhQss::stateToString(state), "font-size")));
    }

    if (containsAttribute(subControl, state, "font-weight")) {
        font.setWeight(QhQss::stringToQreal(attributeValue(
            QhQss::stateToString(state), "font-weight")) / 10);
    } else if (state != SPS_Normal
            && containsAttribute(subControl, SPS_Normal, "font-weight")) {
        font.setWeight(QhQss::stringToQreal(attributeValue(
            QhQss::stateToString(state), "font-weight")) / 10);
    }
}

QhQssPrivate::QhQssPrivate(QhQss *p, QWidget *widget):
    widget(widget), ptr(p)
{

}

void QhQssPrivate::init(std::function<void()> cbFuncQssReloaded)
{
    funcQssReloaded = cbFuncQssReloaded;
    parserQss();
    connect(widget, &QWidget::objectNameChanged, this, &QhQssPrivate::onObjectNameChanged);
    widget->installEventFilter(this);
}

void QhQssPrivate::parserQss()
{
    qssItems = QhQssParser::parser(widget);
    if (funcQssReloaded)
        funcQssReloaded();
}

bool QhQssPrivate::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::StyleChange
            && obj == widget) {
        parserQss();
        widget->update();
    }
    return QObject::eventFilter(obj, event);
}

void QhQssPrivate::onObjectNameChanged(const QString &objectName)
{
    widget->update();
    if (funcQssReloaded)
        funcQssReloaded();
}
