#ifndef TESTLOGGER_H
#define TESTLOGGER_H

#include <qhlogger.h>

class TestLogger: public QObject
{
    Q_OBJECT

public:
    TestLogger();

    void waitStopLogger(int ms);
    void test();
    void testMainLogger();
    void testMainLoggerQPS();
    void testSubLogger();
};

#endif // TESTLOGGER_H
