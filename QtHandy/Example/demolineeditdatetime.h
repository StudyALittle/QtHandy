#ifndef DEMOLINEEDITDATETIME_H
#define DEMOLINEEDITDATETIME_H

#include <qhlineeditdatetime.h>
#include <qhpage.h>

class DemoLineEditDateTime: public QWidget, public QhPage
{
    Q_OBJECT

public:
    DemoLineEditDateTime(QWidget *parent = nullptr);
};

#endif // DEMOLINEEDITDATETIME_H
