#include "qhqssparser.h"
#include <QApplication>
#include <QRegularExpression>
#include <QDebug>

QhQssParser::QhQssParser()
{

}

QVector<QhQssParser::Item::Ptr> QhQssParser::parser(QWidget *w)
{
    QString qss;
    getAllQss(qss, w);

    // qDebug() << "#############################################################";
    // qDebug() << qss;
    return parser(qss);
}

void QhQssParser::findBlockEnds(QVector<int> &idxs, const QString &qss, int pos)
{
    int idx = qss.indexOf("}", pos);
    if (idx < 0) {
        return;
    }

    idxs.append(idx);
    findBlockEnds(idxs, qss, idx + 1);
}

QVector<QhQssParser::Item::Ptr> QhQssParser::parser(const QString &qss)
{
    /// example:
    ///
    /// /* */
    /// QPushButton {}
    /// /* */
    /// QPushButton:hover {}

    QString strNew = qss;
    /// remove comments
    QRegularExpression regex("/\\*[^*]*\\*+([^/*][^*]*\\*+)*/");
    strNew.remove(regex);

    QVector<Item::Ptr> items;

    QVector<int> idxs;
    findBlockEnds(idxs, strNew);

#if 0
    int lastIdx = 0;
    for (int n = 0; n < idxs.size(); ++n) {
        auto idx = idxs.at(n);
        QString str = qss.mid(lastIdx, idx - lastIdx + 1);
        auto item = parserItem(str);
        lastIdx = idx + 1;

        if (!item || item->attributes.isEmpty())
            continue;
        items.append(item);
    }
#else
    for (int n = idxs.size() - 1; n >= 0; --n) {
        auto lastIdx = (n == 0 ? 0 : (idxs.at(n - 1) + 1));
        auto idx = idxs.at(n);

        QString str = strNew.mid(lastIdx, idx - lastIdx + 1);
        auto item = parserItems(str);

        if (item.isEmpty())
            continue;
        items.append(item);
    }
#endif

    return items;
}

QVector<QhQssParser::Item::Ptr> QhQssParser::parserItems(const QString &qss)
{
    /// example:
    /// QWidget QPushButton:hover {
    ///     color: red;
    ///     background: rgba(0, 0, 0, 0);
    ///     image: url(:/res/xxx.png);
    /// }

    int idxBg = qss.indexOf("{");
    int idxEd = qss.lastIndexOf("}");
    if (idxBg <= 0 || idxEd <= 0)
        return {};

    QString selectorStr = qss.left(idxBg).simplified();

    QString attributesStr = qss.mid(idxBg + 1, idxEd - idxBg - 1);
    attributesStr.remove("}").simplified();

    if (attributesStr.isEmpty())
        return {};

    QVector<QhQssParser::Item::Ptr> items;
    auto selectorStrs = selectorStr.split(",", QString::SkipEmptyParts);
    for (int n = selectorStrs.size() - 1; n >= 0; --n) {
        auto str = selectorStrs.at(n);
        auto item = parserItem(str, attributesStr);
        if (!item || item->attributes.isEmpty())
            continue;
        items.append(item);
    }
    return items;
}

QhQssParser::Item::Ptr QhQssParser::parserItem(const QString &selectorStr, const QString &attributesStr)
{
    auto item = Item::Ptr::create();
    auto selectorStrs = selectorStr.split(" ", QString::SkipEmptyParts);
    for (int n = 0; n < selectorStrs.size(); ++n) {
        auto str = selectorStrs.at(n);

        Selector selector;
        Matches matches = MatchesSelector;
        QString name;
        if (str == "*") {               // SelectorAll MatchesAll
            name = str;
            selector = SelectorAll;
            matches = MatchesAll;
        } else if (str.at(0) == ".") {  // SelectorClass MatchesClassNoChild
            name = str.mid(1);
            selector = SelectorClass;
            matches = MatchesClassNoChild;
        } else if (str.at(0) == "#") {  // SelectorID
            name = str.mid(1);
            selector = SelectorID;
        } else {                        // SelectorClass
            name = str;
            selector = SelectorClass;
        }

        if (n == selectorStrs.size() - 1) {
            auto idxSubControl = name.indexOf("::");
            auto idxPseudoState = name.indexOf(":", idxSubControl < 0 ? 0 : (idxSubControl + 2));

            if (idxSubControl > 0 && idxPseudoState > 0) {
                item->subControl = name.mid(idxSubControl + 2, idxPseudoState - idxSubControl - 2);
                item->pseudoState = name.mid(idxPseudoState + 1);
                name = name.left(idxSubControl);
            } else if (idxSubControl > 0) {
                item->subControl = name.mid(idxSubControl + 2);
                name = name.left(idxSubControl);
            } else if (idxPseudoState > 0) {
                item->pseudoState = name.mid(idxPseudoState + 1);
                name = name.left(idxPseudoState);
            }
        }

        SelectorItem selectorItem;
        int idxp1 = name.indexOf("[");
        int idxp2 = name.indexOf("]");
        if (idxp1 > 0 && idxp2 > 0) {
            matches = MatchesProperty;

            QString propertyStr = name.mid(idxp1 + 1, idxp2 - idxp1 - 1);
            auto strs = propertyStr.split("=", QString::SkipEmptyParts);
            if (strs.size() == 2) {
                selectorItem.propertyKey = strs.at(0);
                selectorItem.propertyValue = strs.at(1);
            }

            name = name.left(idxp1);
        } else {
            if (selectorStrs.size() > 1)
                matches = MatchesDescendant;
        }

        selectorItem.selector = selector;
        selectorItem.matches = matches;
        if (selector == SelectorClass) {
            selectorItem.className = name;
        } else if (selector == SelectorID) {
            selectorItem.objectId = name;
        }

        item->selectors.append(selectorItem);
    }

    auto attributesStrs = attributesStr.split(";", QString::SkipEmptyParts);
    for (int n = 0; n < attributesStrs.size(); ++n) {
        auto str = attributesStrs.at(n).simplified();
        int idx = str.indexOf(":");
        if (idx <= 0)
            continue;

        QString key = str.left(idx);
        QString value = str.mid(idx + 1).simplified();
        if (value.startsWith("\""))
            value.remove(0, 1);
        if (value.endsWith("\""))
            value.remove(value.size() - 1, 1);
        item->attributes.insert(key, value);
    }

    return item;
}

void QhQssParser::getAllQss(QString &qss, QWidget *w)
{
    if (qss.isEmpty())
        qss = qApp->styleSheet();

    if (!w) {
        return;
    }

    getAllQss(qss, w->parentWidget());
    qss += w->styleSheet();
}

QWidget *QhQssParser::parentWidget(QWidget *w, const QhQssParser::SelectorItem &selector)
{
    if (!w)
        return nullptr;

    auto *pw = w->parentWidget();
    if (!pw)
        return nullptr;

    if (isMatcheSingle(pw, selector)) {
        return pw;
    }
    return parentWidget(pw, selector);
}

bool QhQssParser::isMatcheSingle(QWidget *w, const SelectorItem &selector)
{
    QString className = w->metaObject()->className();
    QString objectId = w->objectName();

    switch (selector.selector) {
    case SelectorClass: {
        if (className != selector.className)
            return false;
        break;
    }
    case SelectorID: {
        if (!selector.className.isEmpty() && className != selector.className)
            return false;
        if (objectId != selector.objectId)
            return false;
        break;
    }
    default:
        break;
    }

    switch (selector.matches) {
    case MatchesAll: {             /// *
        break;
    }
    case MatchesProperty: {        /// QPushButton[flat="false"]
        if (w->property(selector.propertyKey.toStdString().c_str()).toString()
                != selector.propertyValue)
            return false;
        break;
    }
    case MatchesClassNoChild: {    /// .QPushButton
        break;
    }
    case MatchesDescendant: {      /// QDialog QPushButton
        break;
    }
    case MatchesChild: {           /// QDialog > QPushButton
        break;
    }
    default:
        break;
    }

    return true;
}

QString QhQssParser::attributeValue(QWidget *w, const QVector<Item::Ptr> &items,
    const QString &subControl, const QString &pseudoState, const QString &attribute)
{
    for (auto item: items) {
        if ((!subControl.isEmpty() && subControl != item->subControl)
                || (subControl.isEmpty() && !item->subControl.isEmpty()))
            continue;
        if ((!pseudoState.isEmpty() && pseudoState != item->pseudoState)
                || (pseudoState.isEmpty() && !item->pseudoState.isEmpty()))
            continue;

        int size = item->selectors.size();
        int bgidx = item->selectors.size() - 1;
        QWidget *pw = w;

        for (int n = bgidx; n >= 0; --n) {
            const auto &selector = item->selectors.at(n);
            if ((size == 1 || n == 0) && isMatcheSingle(pw, selector)) {
                QString value = item->attributes.contains(attribute) ?
                    item->attributes.value(attribute) : QString();
                if (value.isEmpty())
                    break;
                return value;
            }

            pw = parentWidget(pw, selector);
            if (!pw)
                break;

            if (MatchesClassNoChild) {  /// .QPushButton （Matches instances of QPushButton, but not of its subclasses.）
                /// DOTO: Currently, we are not considering this situation
            } else if (MatchesChild) {  /// QDialog > QPushButton
                /// DOTO: Currently, we are not considering this situation
            }
        }
    }

    return QString();
}

QString QhQssParser::attributeValue(QWidget *w, const QVector<Item::Ptr> &items,
    const QString &pseudoState, const QString &attribute)
{
    return attributeValue(w, items, QString(), pseudoState, attribute);
}

bool QhQssParser::containsAttribute(QWidget *w, const QVector<Item::Ptr> &items,
    const QString &subControl, const QString &pseudoState, const QString &attribute)
{
    for (auto item: items) {
        if ((!subControl.isEmpty() && subControl != item->subControl)
                || (subControl.isEmpty() && !item->subControl.isEmpty()))
            continue;
        if ((!pseudoState.isEmpty() && pseudoState != item->pseudoState)
                || (pseudoState.isEmpty() && !item->pseudoState.isEmpty()))
            continue;

        int size = item->selectors.size();
        int bgidx = item->selectors.size() - 1;
        QWidget *pw = w;

        for (int n = bgidx; n >= 0; --n) {
            const auto &selector = item->selectors.at(n);
            if ((size == 1 || n == 0) && isMatcheSingle(pw, selector)) {
                QString value = item->attributes.contains(attribute) ?
                    item->attributes.value(attribute) : QString();
                if (value.isEmpty())
                    break;
                return true;
            }

            pw = parentWidget(pw, selector);
            if (!pw)
                break;

            if (MatchesClassNoChild) {  /// .QPushButton （Matches instances of QPushButton, but not of its subclasses.）
                /// DOTO: Currently, we are not considering this situation
            } else if (MatchesChild) {  /// QDialog > QPushButton
                /// DOTO: Currently, we are not considering this situation
            }
        }
    }

    return false;
}











