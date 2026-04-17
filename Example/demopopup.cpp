#include "demopopup.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <qhlabel.h>
#include <qhfloating.h>
#include "qhmessagebox.h"
#include "popupway1.h"
#include "popupway2.h"

DemoPopup::DemoPopup(QWidget *parent):
    QWidget(parent)
{
    auto *ly = new QVBoxLayout(this);
    {
        auto *btn = new QPushButton("FramelessWidget/PopupWay1");
        connect(btn, &QPushButton::clicked, this, []() {
            PopupWay1 dlg("PopupWay1");
            dlg.initFramelessWindow(12);
            // dlg.setBorderWidth(1);
            // dlg.setBorderColor(Qt::gray);
            dlg.setShadowWidth(8);
            dlg.exec();
        });
        ly->addWidget(btn);
    }

    {
        auto *btn = new QPushButton("FramelessWidget/PopupWay2");
        connect(btn, &QPushButton::clicked, this, []() {
            PopupWay2::exec("PopupWay2");
        });
        ly->addWidget(btn);
    }

    {
        auto *btn = new QPushButton("FramelessWidget/PopupWay3");
        connect(btn, &QPushButton::clicked, this, []() {
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
            dlg.exec();
        });
        ly->addWidget(btn);
    }

    {
        QhMessageBox::setRoundedBorder(12);

        auto *btn = new QPushButton("QhMessageBox information");
        connect(btn, &QPushButton::clicked, this, []() {
            QhMessageBox::information(nullptr, tr("test"), "This is a information message");
        });
        ly->addWidget(btn);
    }

    {
        auto *btn = new QPushButton("QhMessageBox warning");
        connect(btn, &QPushButton::clicked, this, []() {
            QhMessageBox::warning(nullptr, tr("test"), "This is a warning message");
        });
        ly->addWidget(btn);
    }

    {
        auto *btn = new QPushButton("QhMessageBox critical");
        connect(btn, &QPushButton::clicked, this, []() {
            QhMessageBox::critical(nullptr, tr("test"), "This is a critical message");
        });
        ly->addWidget(btn);
    }

    {
        auto *btn = new QPushButton("QhMessageBox Custom display buttons");
        connect(btn, &QPushButton::clicked, this, []() {
            auto btn = QhMessageBox::information(nullptr, tr("test"), "This is custom display buttons",
                QhMessageBox::Buttons(QhMessageBox::ButtonOk | QhMessageBox::ButtonCancel));
            if (btn == QhMessageBox::ButtonOk) {
                QhMessageBox::information(nullptr, tr("prompt"), "The \"ok\" button has been clicked");
            } else if (btn == QhMessageBox::ButtonCancel) {
                QhMessageBox::information(nullptr, tr("prompt"), "The \"cancel\" button has been clicked");
            }
        });
        ly->addWidget(btn);
    }

    {
        auto *btn = new QPushButton("QhFloating");
        connect(btn, &QPushButton::clicked, this, [btn]() {
            auto *floating = new QhFloating;
            connect(floating, &QhFloating::closed, [floating]() {
                floating->deleteLater();
            });

            floating->setStyleSheet("QhFloating { background: white; }");
            {
                auto *ly = new QVBoxLayout(floating);
                ly->addWidget(new QhLabel(tr("Click outside the window or lose focus to close the interface")));

                auto *btn = new QPushButton(tr("click close"));
                connect(btn, &QPushButton::clicked, [floating]() {
                    emit floating->closed();
                });
                ly->addWidget(btn);
            }
            // floating->setIgnoreWidgets({btn4});
            floating->adjustSize();
            floating->open(btn->mapToGlobal(QPoint(0, btn->height())));
        });
        ly->addWidget(btn);
    }

    {
        auto *btn = new QPushButton("QhFloating (parent)");
        connect(btn, &QPushButton::clicked, this, [this, btn]() {
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
            floating->setIgnoreWidgets({btn});
            floating->adjustSize();
            floating->open(QPoint(btn->x(), btn->y() + btn->height()));
        });
        ly->addWidget(btn);
    }

    ly->addStretch(1);
}
