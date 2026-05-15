#include "qsstest.h"
#include <QDebug>
#include <QPushButton>

QssTest::QssTest()
{

}

void QssTest::testQssParser()
{
    QString qss =
        "QPushButton {"
        "   color: red;"
        "   background: rgba(1, 0, 0, 0);"
        "   image: url(:/res/aaa.png);"
        "}"
        "QPushButton:hover {"
        "   color: blue;"
        "   background: rgba(1, 0, 0, 0);"
        "   image: url(:/res/aaa.png);"
        "}"
        "QPushButton::up-arrow {"
        "   color: red1;"
        "   background: rgba(1, 0, 0, 0);"
        "   image: url(:/res/aaa.png);"
        "}"
        "QPushButton::up-arrow:hover {"
        "   color: red2;"
        "   background: rgba(1, 0, 0, 0);"
        "   image: url(:/res/aaa.png);"
        "}"
        "#Widget QPushButton {"
        "   color: red;"
        "   background: rgba(1, 0, 0, 0);"
        "   image: url(:/res/aaa.png);"
        "}"
        "#Widget #PushButton {"
        "   color: red;"
        "   background: rgba(1, 0, 0, 0);"
        "   image: url(:/res/aaa.png);"
        "}"
        "QWidget #PushButton {"
        "   color: red6;"
        "   background: rgba(1, 0, 0, 0);"
        "   image: url(:/res/aaa.png);"
        "}"
        "";


    auto items = QhQssParser::parser(qss);
    for (auto item: items) {
        qDebug() << "#####################################";

        QString selectorsText;
        for (auto selector: item->selectors) {
            if (!selectorsText.isEmpty())
                selectorsText.append(" ");
            if (!selector.className.isEmpty())
                selectorsText.append(selector.className);
            if (!selector.objectId.isEmpty()) {
                selectorsText.append("#");
                selectorsText.append(selector.objectId);
            }

            if (!selector.propertyKey.isEmpty()) {
                selectorsText += QString("[%1=\"%2\"]")
                    .arg(selector.propertyKey)
                    .arg(selector.propertyValue);
            }
        }

        if (!item->subControl.isEmpty()) {
            selectorsText.append("::");
            selectorsText.append(item->subControl);
        }

        if (!item->pseudoState.isEmpty()) {
            selectorsText.append(":");
            selectorsText.append(item->pseudoState);
        }

        qDebug() << selectorsText;
        qDebug() << "{";
        for (auto it = item->attributes.begin(); it != item->attributes.end(); ++it) {
            qDebug() << "    " << it.key() << ": " << it.value() << ";";
        }
        qDebug() << "}";
    }

    auto *w = new QPushButton;
    qDebug() << "#####################################";
    qDebug() << "color: " << QhQssParser::attributeValue(w, items, "", "", "color");
    qDebug() << "up-arrow hover color: " << QhQssParser::attributeValue(w, items, "", "hover", "color");
    qDebug() << "up-arrow color: " << QhQssParser::attributeValue(w, items, "up-arrow", "", "color");
    qDebug() << "up-arrow:hover color: " << QhQssParser::attributeValue(w, items, "up-arrow", "hover", "color");
    w->deleteLater();
}
