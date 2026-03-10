#include "demolabel.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

DemoLabel::DemoLabel(QWidget *parent):
    QWidget(parent)
{
    auto *ly = new QVBoxLayout(this);
    {
        auto *label = new QhLabel("Normal Labels");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");

        auto *label1 = new QhLabel("1. Label");

        auto *label2 = new QhLabel("2. Test display ellipses when the display is incomplete");
        label2->setMaximumWidth(200);
        label2->setEllipsis(true);

        auto *label3 = new QhLabel("3. Test the display of wrapped text for extremely long texts, "
                                        "and display ellipses when the display is incomplete");
        label3->setAlignment(Qt::AlignLeft | Qt::AlignTop);
        label3->setWordWrap(true);
        label3->setMaxLine(3);
        label3->setEllipsis(true);

        ly->addWidget(label);
        ly->addWidget(label1);
        ly->addWidget(label2);
        ly->addWidget(label3);
    }

    {
        auto *label = new QhLabel("Required Labels");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");

        auto *label1 = new QhLabel("Required field label");
        label1->setRequiredMode(QhLabel::Required);

        auto *label2 = new QhLabel("Required item label placeholder");
        label2->setRequiredMode(QhLabel::RequiredPlaceholder);

        auto *label3 = new QhLabel("Test the display of wrapped text for extremely long texts, "
                                        "and display ellipses when the display is incomplete");
        label3->setAlignment(Qt::AlignLeft | Qt::AlignTop);
        label3->setWordWrap(true);
        label3->setMaxLine(3);
        label3->setEllipsis(true);
        label3->setRequiredMode(QhLabel::Required);

        auto *label4 = new QhLabel("Test display ellipses when the display is incomplete");
        label4->setMaximumWidth(200);
        label4->setEllipsis(true);
        label4->setRequiredMode(QhLabel::Required);

        ly->addWidget(label);
        ly->addWidget(label1);
        ly->addWidget(label2);
        ly->addWidget(label3);
        ly->addWidget(label4);
    }
    ly->addStretch(1);
}
