#include <QDebug>
#include <QApplication>
#include <qhqssmanager.h>
#include <qhlogger.h>
#include "demowidget.h"

#pragma execution_character_set("utf-8")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /// logger
#if 1
    enum LMode { LOGModeSub = LoggerMCustom + 1 };

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
#endif

    a.setFont(QFont("微软雅黑", 10));

    QhQssManager::setQss({
        ":/resources/qss/imagebutton.css",
        ":/resources/qss/lineedit.css",
        ":/resources/qss/textedit.css",
        ":/resources/qss/datetime.css",
        ":/resources/qss/menu.css",
    });

    DemoWidget w;
    w.resize(1000, 600);
    w.show();

    auto ret = a.exec();

    HLOG_DEBUG("app stop...");
    gHLOGgers->deleteAllModules(true);

    return ret;
}
