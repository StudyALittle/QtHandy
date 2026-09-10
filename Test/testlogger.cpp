#include "testlogger.h"
#include <QDebug>
#include <QCoreApplication>
#include <QDateTime>

enum LMode { LOGModeSub = LoggerMCustom + 1 };

TestLogger::TestLogger()
{

}

void TestLogger::test()
{
    /// Enable main module log by default
    {
        QhLoggerConfig logConfig;
        logConfig.bStart = true;
        logConfig.storageDirectory = QCoreApplication::applicationDirPath() + "/logger/modeMain";
        gHLOGgers->addModule()->start(logConfig, true);
    }

    /// Add submodule log
    {
        QhLoggerConfig logConfig;
        logConfig.bStart = true;
        logConfig.bSubThreadWrite = false;
        logConfig.storageDirectory = QCoreApplication::applicationDirPath() + "/logger/modeSub";
        gHLOGgers->addModule(LOGModeSub)->start(logConfig, false);
    }

    /// The log is written to the main module
    HLOG_DEBUG("app start...");
    qDebug() << "app start";

    /// Write logs to sub-modules
    HLOGMD_INFO(LOGModeSub, "sub mode message");
    HLOGMD_INFO(LOGModeSub, "sub mode message 2");

    {
        auto bms = QDateTime::currentMSecsSinceEpoch();
        for (int n = 0; n < 10000*20; ++n) {
            HLOG_DEBUG("test message index " + QString::number(n + 1));
        }
        auto ems = QDateTime::currentMSecsSinceEpoch();
        HLOG_DEBUG("write time space(ms): " + QString::number(ems - bms));
    }

    // QhLoggers::instance()->deleteAllModules(true);
}
