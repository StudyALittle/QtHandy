#include "testlogger.h"
#include <QDebug>
#include <QCoreApplication>
#include <QDateTime>
#include <QEventLoop>
#include <QTimer>

#pragma execution_character_set("utf-8")

enum LMode { LOGModeSub = LoggerMCustom + 1 };

TestLogger::TestLogger()
{

}

void TestLogger::waitStopLogger(int ms)
{
    QEventLoop eloop;
    QTimer timer;
    connect(&timer, &QTimer::timeout, this, [&eloop]() {
        eloop.exit();
    });
    timer.start(ms);
    eloop.exec();

    QhLoggers::instance()->deleteAllModules(true);
}

void TestLogger::testMainLogger()
{
    QhLoggerConfig logConfig;
    logConfig.bStart = true;
    logConfig.maxCacheCount = 0;
    logConfig.bSubThreadWrite = true;
    logConfig.bOutConsole = true;
    logConfig.storageDirectory = QCoreApplication::applicationDirPath() + "/logger/modeMain";
    gHLOGgers->addModule()->start(logConfig, true);

    HLOG_DEBUG("test model main logger 1");
    qDebug() << "test model main logger 2";

    waitStopLogger(3*1000);
}

void TestLogger::testMainLoggerQPS()
{
    QhLoggerConfig logConfig;
    logConfig.bStart = true;
    logConfig.maxCacheCount = 0;
    logConfig.bSubThreadWrite = true;
    logConfig.bOutConsole = false;
    logConfig.storageDirectory = QCoreApplication::applicationDirPath() + "/logger/modeMain";
    gHLOGgers->addModule()->start(logConfig, true);

#if 1
    auto bms = QDateTime::currentMSecsSinceEpoch();
    for (int n = 0; n < 10000*100; ++n) {
        HLOG_DEBUG("test message index " + QString::number(n + 1));
    }
    auto ems = QDateTime::currentMSecsSinceEpoch();
    // about 1s
    HLOG_DEBUG("write time space(s): " + QString::number((qreal)(ems - bms) / 1000.0f));
#elif 0
    auto logger = QhLoggers::instance()->module(LoggerMMain);
    auto bms = QDateTime::currentMSecsSinceEpoch();
    for (int n = 0; n < 10000*100; ++n) {
        logger->write(LoggerLDebug, "main.cpp", "test", 0, "test message index");
    }
    auto ems = QDateTime::currentMSecsSinceEpoch();
    HLOG_DEBUG("write time space(ms): " + QString::number((qreal)(ems - bms) / 1000.0f));
#else
    auto logger = QhLoggers::instance()->module(LoggerMMain);
    auto msg = QSharedPointer<QhLoggerMessage>::create(LoggerLDebug, "main.cpp", "test", 0, "test message index");

    auto bms = QDateTime::currentMSecsSinceEpoch();
    for (int n = 0; n < 10000*100; ++n) {
        logger->write(msg);
    }
    auto ems = QDateTime::currentMSecsSinceEpoch();
    HLOG_DEBUG("write time space(ms): " + QString::number((qreal)(ems - bms) / 1000.0f));
#endif

    waitStopLogger(10*1000);
}

void TestLogger::testSubLogger()
{
    QhLoggerConfig logConfig;
    logConfig.bStart = true;
    logConfig.bSubThreadWrite = true;
    logConfig.storageDirectory = QCoreApplication::applicationDirPath() + "/logger/modeSub";
    gHLOGgers->addModule(LOGModeSub)->start(logConfig, false);

    /// Write logs to sub-modules
    HLOGMD_INFO(LOGModeSub, "sub mode message 1");
    HLOGMD_INFO(LOGModeSub, "sub mode message 2");
    qDebug() << "sub mode message 3";

    waitStopLogger(2*1000);
}

void TestLogger::test()
{
    // testMainLogger();
    testMainLoggerQPS();

    // testSubLogger();
}
