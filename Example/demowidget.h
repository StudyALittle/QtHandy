#ifndef DEMOWIDGET_H
#define DEMOWIDGET_H

#include <QStackedWidget>
#include <QWidget>
#include <QMap>
#include <qhpagemanager.h>
#include <qhsystemtrayicon.h>
#include "demonavbarproxy.h"

class DemoWidget: public QWidget, public QhPageManager
{
    Q_OBJECT

public:
    DemoWidget();

protected:
    QWidget *createPage(qint64 id) override;

    void closeEvent(QCloseEvent *event) override;

private:
    QStackedWidget *m_stackedWidget = nullptr;

    QhSystemTrayIcon *m_systemTrayIcon = nullptr;
};

#endif // DEMOWIDGET_H
