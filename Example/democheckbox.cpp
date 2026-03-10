#include "democheckbox.h"
#include <QGridLayout>
#include <QLabel>

DemoCheckBox::DemoCheckBox(QWidget *parent):
    QWidget(parent)
{
    auto *gly = new QGridLayout(this);
    gly->addWidget(new QLabel("status checkbox:"), 0, 0);
    gly->addWidget(new QhCheckBox(true, "Lock the current state"), 0, 1);
    gly->addWidget(new QhCheckBox(false, "normal"), 0, 2);
}
