#include <QApplication>
#include <QStandardPaths>
#include <QIcon>
#include <qhstyle.h>
#include "ui/homeui.h"
#include "db/dbmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    DBManager::instance().initDB(appDataPath + "/dirfiletool.db");

    QhStyle::setQss({
        ":/resource/css/style.css",
    });

    qApp->setWindowIcon(QIcon(":/resource/app.svg"));

    HomeUi w;
    w.resize(800, 600);
    w.show();
    return a.exec();
}
