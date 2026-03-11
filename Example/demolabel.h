#ifndef DEMOLABEL_H
#define DEMOLABEL_H

#include <qhlabel.h>
#include <qhpage.h>

class DemoLabel: public QWidget, public QhPage
{
    Q_OBJECT

public:
    DemoLabel(QWidget *parent = nullptr);
};

#endif // DEMOLABEL_H
