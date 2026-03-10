#include "demobutton.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <qhlabel.h>
#include <qhimageutil.h>
#include <qhqss.h>

DemoButton::DemoButton(QWidget *parent):
    QWidget(parent)
{
    auto *ly = new QVBoxLayout(this);
    {
        auto *label = new QhLabel("Icon PushButton");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");
        ly->addWidget(label);

#if 0
        {
            auto *hly = new QHBoxLayout;

            auto *btn = new QhPushButton;
            btn->setIcon(QIcon(QhImageUtil::svgToIcon(
                ":/resources/imgs/icon1.svg", Qt::black, QSize(16, 16))));

            auto *btn2 = new QhPushButton;
            btn2->setIcon(QIcon(QhImageUtil::svgToIcon(
                ":/resources/imgs/icon2.svg", Qt::black, QSize(16, 16))));

            auto *btn3 = new QhPushButton;
            btn3->setIcon(QIcon(QhImageUtil::svgToIcon(
                ":/resources/imgs/icon3.svg", Qt::black, QSize(16, 16))));

            hly->addWidget(btn);
            hly->addWidget(btn2);
            hly->addWidget(btn3);
            hly->addStretch(1);
            ly->addLayout(hly);
        }
#endif

        {
            auto *btn = new QhPushButton("two icons (qss style)");
            btn->setImageMode(true);
            // Reference resource file: ":/resources/qss/button.css"
            ly->addWidget(btn);
        }

        {
            auto *btn = new QhPushButton("two icons 2 (qss style)");
            btn->setObjectName("HandyPushButton");
            btn->setImageMode(true);
            // Reference resource file: ":/resources/qss/button.css"
            ly->addWidget(btn);
        }

#if 1
        {
            auto *btn = new QhPushButton("an icon");
            btn->setImageMode(true);

            {
                QhQss::PropertyTypes styles;
                styles.color = Qt::black;
                styles.padding = QMargins(12, 6, 12, 6);
                styles.space = 4;
                btn->handyQss()->setPropertyTypes(QhQss::SSC_Not, QhQss::SPS_Normal, styles);

                styles.color = Qt::gray;
                btn->handyQss()->setPropertyTypes(QhQss::SSC_Not, QhQss::SPS_Disabled, styles);

                styles.color = Qt::blue;
                btn->handyQss()->setPropertyTypes(QhQss::SSC_Not, QhQss::SPS_Hover, styles);

                styles.color = Qt::red;
                btn->handyQss()->setPropertyTypes(QhQss::SSC_Not, QhQss::SPS_Pressed, styles);

                styles.color = Qt::yellow;
                btn->handyQss()->setPropertyTypes(QhQss::SSC_Not, QhQss::SPS_Checked, styles);
            }

            // left
            {
                QhQss::PropertyTypes styles;
                styles.imagePath = ":/resources/imgs/icon2.svg";
                styles.imageColor = Qt::black;
                styles.imageSize = QSize(16, 16);
                styles.relativePos = QhQss::NearBorder;
                btn->handyQss()->setPropertyTypes(QhQss::SSC_Left, QhQss::SPS_Normal, styles);

                styles.imageColor = Qt::gray;
                btn->handyQss()->setPropertyTypes(QhQss::SSC_Left, QhQss::SPS_Disabled, styles);

                styles.imageColor = Qt::blue;
                btn->handyQss()->setPropertyTypes(QhQss::SSC_Left, QhQss::SPS_Hover, styles);

                styles.imageColor = Qt::red;
                btn->handyQss()->setPropertyTypes(QhQss::SSC_Left, QhQss::SPS_Pressed, styles);

                styles.imageColor = Qt::yellow;
                btn->handyQss()->setPropertyTypes(QhQss::SSC_Left, QhQss::SPS_Checked, styles);
            }

            // right
            {
                QhQss::PropertyTypes styles;
                styles.visible = false;
                btn->handyQss()->setPropertyTypes(QhQss::SSC_Right,
                    {QhQss::SPS_Normal, QhQss::SPS_Disabled, QhQss::SPS_Hover,
                     QhQss::SPS_Pressed, QhQss::SPS_Checked}, styles);
            }

            ly->addWidget(btn);
        }
#endif

#if 0
        {
            auto *btn = new QhPushButton("two icons");
            btn->setImageMode(true);

            {
                QhQss::PropertyTypes styles;
                styles.color = Qt::black;
                styles.padding = QMargins(12, 6, 12, 6);
                styles.space = 4;
                btn->handyQss()->setPropertyTypes(QhQss::SSC_Not, QhQss::SPS_Normal, styles);

                styles.color = Qt::gray;
                btn->handyQss()->setPropertyTypes(QhQss::SSC_Not, QhQss::SPS_Disabled, styles);

                styles.color = Qt::blue;
                btn->handyQss()->setPropertyTypes(QhQss::SSC_Not, QhQss::SPS_Hover, styles);

                styles.color = Qt::red;
                btn->handyQss()->setPropertyTypes(QhQss::SSC_Not, QhQss::SPS_Pressed, styles);

                styles.color = Qt::yellow;
                btn->handyQss()->setPropertyTypes(QhQss::SSC_Not, QhQss::SPS_Checked, styles);
            }

            // left
            {
                QhQss::PropertyTypes styles;
                styles.imagePath = ":/resources/imgs/icon2.svg";
                styles.imageColor = Qt::black;
                styles.imageSize = QSize(16, 16);
                styles.relativePos = QhQss::NearBorder;
                btn->handyQss()->setPropertyTypes(QhQss::SSC_Left, QhQss::SPS_Normal, styles);

                styles.imageColor = Qt::gray;
                btn->handyQss()->setPropertyTypes(QhQss::SSC_Left, QhQss::SPS_Disabled, styles);

                styles.imageColor = Qt::blue;
                btn->handyQss()->setPropertyTypes(QhQss::SSC_Left, QhQss::SPS_Hover, styles);

                styles.imageColor = Qt::red;
                btn->handyQss()->setPropertyTypes(QhQss::SSC_Left, QhQss::SPS_Pressed, styles);

                styles.imageColor = Qt::yellow;
                btn->handyQss()->setPropertyTypes(QhQss::SSC_Left, QhQss::SPS_Checked, styles);
            }

            // right
            {
                QhQss::PropertyTypes styles;
                styles.imagePath = ":/resources/imgs/icon3.svg";
                styles.imageColor = Qt::black;
                styles.imageSize = QSize(16, 16);
                styles.relativePos = QhQss::NearBorder;
                btn->handyQss()->setPropertyTypes(QhQss::SSC_Right, QhQss::SPS_Normal, styles);

                styles.imageColor = Qt::gray;
                btn->handyQss()->setPropertyTypes(QhQss::SSC_Right, QhQss::SPS_Disabled, styles);

                styles.imageColor = Qt::blue;
                btn->handyQss()->setPropertyTypes(QhQss::SSC_Right, QhQss::SPS_Hover, styles);

                styles.imageColor = Qt::red;
                btn->handyQss()->setPropertyTypes(QhQss::SSC_Right, QhQss::SPS_Pressed, styles);

                styles.imageColor = Qt::yellow;
                btn->handyQss()->setPropertyTypes(QhQss::SSC_Right, QhQss::SPS_Checked, styles);
            }

            ly->addWidget(btn);
        }
#endif
    }
    ly->addStretch(1);
}
