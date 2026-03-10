#include "demolineeditdatetime.h"
#include <QVBoxLayout>
#include <qhlabel.h>
#include <qhwidgetutil.h>

DemoLineEditDateTime::DemoLineEditDateTime(QWidget *parent):
    QWidget(parent)
{
    auto *ly = new QVBoxLayout(this);
    {
        auto *label = new QhLabel("LineEdit Time");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");

        auto *lineEdit = new QhLineEditDateTime(QhLineEditDateTime::Time);
        ly->addWidget(label);
        ly->addWidget(lineEdit);
    }

    {
        auto *label = new QhLabel("LineEdit Date");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");

        auto *lineEdit = new QhLineEditDateTime(QhLineEditDateTime::Date);
        ly->addWidget(label);
        ly->addWidget(lineEdit);
    }

    {
        auto *label = new QhLabel("LineEdit DateRange");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");

        auto *lineEdit = new QhLineEditDateTime(QhLineEditDateTime::DateRange);
        ly->addWidget(label);
        ly->addWidget(lineEdit);
    }

    {
        auto *label = new QhLabel("LineEdit DateTime");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");

        auto *lineEdit = new QhLineEditDateTime(QhLineEditDateTime::DateTime);
        ly->addWidget(label);
        ly->addWidget(lineEdit);
    }

    {
        auto *label = new QhLabel("LineEdit DateTimeRange");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");

        auto *lineEdit = new QhLineEditDateTime(QhLineEditDateTime::DateTimeRange);
        ly->addWidget(label);
        ly->addWidget(lineEdit);
    }

    ly->addStretch(1);
}
