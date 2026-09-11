#include <QApplication>
#include <QDebug>
#include <qhradarchart.h>
#include <qhdtwrapper.h>
#include <qhsingletonprocess.h>
#include <qhwidgetutil.h>
#include "widget.h"
#include "qsstest.h"
#include "testwidgettable.h"
#include "qhmcomboboxtest.h"
#include "testlogger.h"

#define TEST_LOGGER

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QssTest::testQssParser();

#ifdef TEST_LOGGER
    TestLogger tlogger;
    tlogger.test();
    return 0;
#endif

#if 0
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
#endif

#if 1
    if (!QhSingletonProcess::instance().bind("test")) {
        qWarning() << "Process is already running.";
        QhSingletonProcess::instance().sendMessage(QhSingletonProcess::MT_Activated);
        QhSingletonProcess::instance().unbind();
        return 0;
    }
#endif

#if 0
    Widget w;
    w.show();
#elif 0
    TestWidgetTable w;
    w.show();
#elif 1
    QhMComboBoxTest w;
    w.show();

    QObject::connect(&QhSingletonProcess::instance(), &QhSingletonProcess::receivedMessage,
            [&w](int type, const QString &data) {
        qDebug() << "Message received:" << type << data;
        if (type == QhSingletonProcess::MT_Activated) {
            QhWidgetUtil::activateWindow(&w);
        }
    });
#elif 1
    TestWidgetTable w;
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
    bool ret = a.exec();
    QhSingletonProcess::instance().unbind();
    return ret;
}

//#include "main.moc"
