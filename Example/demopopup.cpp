#include "demopopup.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <qhlabel.h>
#include <qhfloating.h>
#include "popupway1.h"
#include "popupway2.h"

DemoPopup::DemoPopup(QWidget *parent):
    QWidget(parent)
{
    auto *btn1 = new QPushButton("FramelessWidget/PopupWay1");
    connect(btn1, &QPushButton::clicked, this, []() {
        PopupWay1 dlg("PopupWay1");
        dlg.initFramelessWindow(12);
        // dlg.setBorderWidth(1);
        // dlg.setBorderColor(Qt::gray);
        dlg.setShadowWidth(8);
        dlg.setStyleSheet("PopupWay1 {"
                          "qproperty-widgetTitleSpace: 66;"
                          "qproperty-widgetTitleMargins: \"6px 6px 6px 6px;\";"
                          "background: white;"
                          "}");
        dlg.exec();
    });

    auto *btn2 = new QPushButton("FramelessWidget/PopupWay2");
    connect(btn2, &QPushButton::clicked, this, []() {
        PopupWay2::exec("PopupWay2");
    });

    auto *btn3 = new QPushButton("FramelessWidget/PopupWay3");
    connect(btn3, &QPushButton::clicked, this, []() {
        QhBasePopup dlg(tr("Flexible content"));
        auto *widget = new QWidget;
        {
            auto *gly = new QGridLayout(widget);
            gly->addWidget(new QLabel("name: "), 0, 0);
            gly->addWidget(new QLabel("Qh"), 0, 1);
            gly->addWidget(new QLabel("Description: "), 1, 0);
            gly->addWidget(new QLabel("Qh is a convenient component library"), 1, 1);
            gly->setContentsMargins(24, 24, 24, 24);
        }
        dlg.setContentWidget(widget);
        dlg.setButtons(QhBasePopup::ButtonOk);
        dlg.initFramelessWindow();
        dlg.setStyleSheet("QhBasePopup{ background: white; }");
        dlg.exec();
    });

    auto *btn4 = new QPushButton("QhFloating");
    connect(btn4, &QPushButton::clicked, this, [btn4]() {
        auto *floating = new QhFloating;
        connect(floating, &QhFloating::closed, floating, [floating]() {
            floating->deleteLater();
        });

        floating->setStyleSheet("QhFloating { background: white; }");
        {
            auto *ly = new QVBoxLayout(floating);
            ly->addWidget(new QhLabel(tr("Click outside the window or lose focus to close the interface")));

            auto *btn = new QPushButton(tr("click close"));
            connect(btn, &QPushButton::clicked, btn, [floating]() {
                emit floating->closed();
            });
            ly->addWidget(btn);
        }
        // floating->setIgnoreWidgets({btn4});
        floating->adjustSize();
        floating->open(btn4->mapToGlobal(QPoint(0, btn4->height())));
    });

    auto *btn5 = new QPushButton("QhFloating (parent)");
    connect(btn5, &QPushButton::clicked, this, [this, btn5]() {
        static QhFloating *floating = nullptr;
        if (floating)
            return;

        floating = new QhFloating(this);
        connect(floating, &QhFloating::closed, floating, []() {
            floating->deleteLater();
            floating = nullptr;
        });

        floating->setStyleSheet("QhFloating { background: white; border-radius: 8px; }");
        {
            auto *ly = new QVBoxLayout(floating);
            ly->addWidget(new QhLabel(tr("Click outside the window or lose focus to close the interface")));

            auto *btn = new QPushButton(tr("click close"));
            connect(btn, &QPushButton::clicked, btn, []() {
                emit floating->closed();
            });
            ly->addWidget(btn);
        }
        floating->setIgnoreWidgets({btn5});
        floating->adjustSize();
        floating->open(QPoint(btn5->x(), btn5->y() + btn5->height()));
    });

    auto *ly = new QVBoxLayout(this);
    ly->addWidget(btn1);
    ly->addWidget(btn2);
    ly->addWidget(btn3);
    ly->addWidget(btn4);
    ly->addWidget(btn5);
    ly->addStretch(1);
}
