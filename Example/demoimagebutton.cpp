#include "demoimagebutton.h"
#include <QVBoxLayout>
#include <QVariant>
#include "qhlabel.h"

DemoImageButton::DemoImageButton(QWidget *parent):
    QWidget(parent)
{
    auto *ly = new QVBoxLayout(this);
    {
        auto *label = new QhLabel("Image Button (Two icon)");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");

        auto *button = new QhImageButton("Image Button");
        ly->addWidget(label);
        ly->addWidget(button);
    }

    {
        auto *label = new QhLabel("Image Button  (Right icon)");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");

        auto *button = new QhImageButton("Image Button");
        button->setLeftIconVisible(false);
        ly->addWidget(label);
        ly->addWidget(button);
    }

    {
        auto *label = new QhLabel("Image Button  (Left icon)");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");

        auto *button = new QhImageButton("Image Button");
        button->setRightIconVisible(false);
        ly->addWidget(label);
        ly->addWidget(button);
    }

    {
        auto *label = new QhLabel("Image Button (Text offset relative to image)");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");

        auto *button = new QhImageButton("Image Button");
        button->setProperty("type", "offset");
        ly->addWidget(label);
        ly->addWidget(button);
    }

    ly->addStretch(1);
}
