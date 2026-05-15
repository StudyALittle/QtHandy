#ifndef DEMOPOPUP_H
#define DEMOPOPUP_H

#include <QWidget>
#include <qhpage.h>

class DemoPopup: public QWidget, public QhPage
{
    Q_OBJECT

public:
    DemoPopup(QWidget *parent = nullptr);
};

#endif // DEMOPOPUP_H
