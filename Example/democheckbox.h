#ifndef DEMOCHECKBOX_H
#define DEMOCHECKBOX_H

#include <qhcheckbox.h>
#include <qhpage.h>

class DemoCheckBox: public QWidget, public QhPage
{
    Q_OBJECT

public:
    DemoCheckBox(QWidget *parent = nullptr);
};

#endif // DEMOCHECKBOX_H
