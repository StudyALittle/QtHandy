#include <QApplication>
#include <QDebug>
#include <qhradarchart.h>
#include <qhdtwrapper.h>
#include "widget.h"
#include "qsstest.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QssTest::testQssParser();

    // qhpackdata
    {
        QhDTWrapper<int> pd1;
        qDebug() << "PData 1 isValid: " << pd1.isValid();
        pd1 = 1;
        qDebug() << "PData 1 isValid: " << pd1.isValid();
        qDebug() << "PData 1 value: " << pd1();

        QhDTWrapper<int> pd2(2);
        qDebug() << "PData 2 isValid: " << pd2.isValid();
        qDebug() << "PData 2 value: " << pd2.value();

        QhDTWrapper<QString *> pd3(new QString("Test QhPackData 1"));
        qDebug() << "PData 3 isValid: " << pd3.isValid();
        qDebug() << "PData 3 value: " << *(pd3.value());

        QhDTWrapper<QString *> pd4;
        pd4 = new QString("Test QhPackData 2");
        qDebug() << "PData 4 isValid: " << pd4.isValid();
        qDebug() << "PData 4 value: " << *(pd4.value());

        QhDTWrapper<QString *> pd5;
        pd5 = pd4;
        qDebug() << "PData 5 isValid: " << pd5.isValid();
        qDebug() << "PData 5 value: " << *(pd5.value());
    }

#if 1
    Widget w;
    w.show();
#else
    QhRadarChart cw;
    cw.setData({
        {"test1", 9},
        {"test2_123456789", 6},
        {"test3", 8},
        {"test4", 3},
        {"test5", 9},
        {"test6_123456789", 4},
        {"test7", 6},
        {"test8", 2},
    });
    cw.show();
#endif
    return a.exec();
}
