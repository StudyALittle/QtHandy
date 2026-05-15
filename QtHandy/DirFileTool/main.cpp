#include <QApplication>
#include <QStandardPaths>
#include <QIcon>
#include <qhqssmanager.h>
#include "ui/homeui.h"
#include "db/dbmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    DBManager::instance().initDB(appDataPath + "/dirfiletool.db");

    QhQssManager::setQss({
        ":/resource/css/style.css",
    });

    qApp->setWindowIcon(QIcon(":/resource/app.svg"));

    HomeUi w;
    w.resize(800, 600);
    w.show();
    return a.exec();
}
