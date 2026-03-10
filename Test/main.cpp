#include <QApplication>
#include <QDebug>
#include "widget.h"
#include "qsstest.h"
#include "qhdtwrapper.h"

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

        QhDTWrapper<QString*> pd3(new QString("Test QhPackData 1"));
        qDebug() << "PData 3 isValid: " << pd3.isValid();
        qDebug() << "PData 3 value: " << *(pd3.value());

        QhDTWrapper<QString*> pd4;
        pd4 = new QString("Test QhPackData 2");
        qDebug() << "PData 4 isValid: " << pd4.isValid();
        qDebug() << "PData 4 value: " << *(pd4.value());

        QhDTWrapper<QString*> pd5;
        pd5 = pd4;
        qDebug() << "PData 5 isValid: " << pd5.isValid();
        qDebug() << "PData 5 value: " << *(pd5.value());
    }

    Widget w;
    w.show();
    return a.exec();
}
