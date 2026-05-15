#ifndef QHQSSPARSER_H
#define QHQSSPARSER_H

#include <QWidget>
#include <QString>
#include <QMap>
#include "QH_global.h"

class QTHANDY_EXPORT QhQssParser
{
public:
    enum Selector
    {
        SelectorAll,
        SelectorClass,
        SelectorID
    };

    enum Matches
    {
        MatchesAll,             /// *
        MatchesProperty,        /// QPushButton[flat="false"]
        MatchesClassNoChild,    /// .QPushButton
        MatchesDescendant,      /// QDialog QPushButton
        MatchesChild,           /// QDialog > QPushButton
        MatchesSelector
    };

    struct SelectorItem
    {
        Selector selector;
        Matches matches;
        QString className;
        QString objectId;
        QString propertyKey;
        QString propertyValue;
    };

    struct Item
    {
        using Ptr = QSharedPointer<Item>;

        /// @brief selectors
        QVector<SelectorItem> selectors;

        /// @brief example "::item ::up-arrow ..."
        QString subControl;

        /// @brief example ":pressed :hover ..."
        QString pseudoState;

        /// @brief key: attribute name; value: attribute value
        QMap<QString, QString> attributes;
    };

    QhQssParser();

    static QVector<Item::Ptr> parser(QWidget *w);
    static QVector<Item::Ptr> parser(const QString &qss);
    static QVector<Item::Ptr> parserItems(const QString &qss);
    static Item::Ptr parserItem(const QString &selectorStr, const QString &attributesStr);

    static QString attributeValue(QWidget *w, const QVector<Item::Ptr> &items, const QString &subControl,
        const QString &pseudoState, const QString &attribute);
    static QString attributeValue(QWidget *w, const QVector<Item::Ptr> &items,
        const QString &pseudoState, const QString &attribute);
    static bool containsAttribute(QWidget *w, const QVector<Item::Ptr> &items, const QString &subControl,
        const QString &pseudoState, const QString &attribute);

    static void getAllQss(QString &qss, QWidget *w);
    static void findBlockEnds(QVector<int> &idxs, const QString &qss, int pos = 0);
    static QWidget *parentWidget(QWidget *w, const SelectorItem &selector);
    static bool isMatcheSingle(QWidget *w, const SelectorItem &selector);
};

#endif // QHQSSPARSER_H
