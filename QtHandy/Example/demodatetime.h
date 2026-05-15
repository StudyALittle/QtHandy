#ifndef DEMODATETIME_H
#define DEMODATETIME_H

#include <qhtimepicker.h>
#include <qhdatepicker.h>
#include <qhdatetimepicker.h>
#include <qhpage.h>

class DemoDateTime: public QWidget, public QhPage
{
    Q_OBJECT

public:
    DemoDateTime(QWidget *parent = nullptr);
};

#endif // DEMODATETIME_H
