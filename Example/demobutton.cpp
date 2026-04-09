#include "demobutton.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTimer>
#include <qhlabel.h>
#include <qhimageutil.h>
#include <qhloadingbutton.h>

DemoButton::DemoButton(QWidget *parent) : QWidget(parent)
{
    auto *ly = new QVBoxLayout(this);
    {
        auto *label = new QhLabel("Loading Button");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");

        auto *button = new QhLoadingButton("loading");
        button->spinLeft()->setFixedSize(20, 20);
        connect(button, &QhLoadingButton::clicked, this, [button]() {
            button->start();
            button->setEnabled(false);

            QTimer::singleShot(5000, [button]() {
                button->stop();
                button->setEnabled(true);
            });
        });

        ly->addWidget(label);
        ly->addWidget(button);
    }


    ly->addStretch(1);
}
