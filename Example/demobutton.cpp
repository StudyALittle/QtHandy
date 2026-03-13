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

    }
    ly->addStretch(1);
}
