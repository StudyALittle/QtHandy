#ifndef DEMOBUTTON_H
#define DEMOBUTTON_H

#include <qhpushbutton.h>
#include <qhpage.h>

class DemoButton: public QWidget, public QhPage
{
    Q_OBJECT

public:
    DemoButton(QWidget *parent = nullptr);
};

#endif // DEMOBUTTON_H
