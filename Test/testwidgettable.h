#ifndef TESTWIDGETTABLE_H
#define TESTWIDGETTABLE_H

#include <qhtablewidget.h>

class TestWidgetTable : public QWidget
{
    Q_OBJECT

public:
    TestWidgetTable();

private:
    QhTableWidget *tableWidget = nullptr;
};

#endif // TESTWIDGETTABLE_H
