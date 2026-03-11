#ifndef DEMOLINEEDIT_H
#define DEMOLINEEDIT_H

#include <qhlineedit.h>
#include <qhpage.h>

class DemoLineEdit: public QWidget, public QhPage
{
    Q_OBJECT

public:
    DemoLineEdit(QWidget *parent = nullptr);
};

#endif // DEMOLINEEDIT_H
