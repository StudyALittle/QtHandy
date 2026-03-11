#ifndef DEMOWIDGET_H
#define DEMOWIDGET_H

#include <QStackedWidget>
#include <QWidget>
#include <QMap>
#include <qhpagemanager.h>
#include "demonavbarproxy.h"

class DemoWidget: public QWidget, public QhPageManager
{
    Q_OBJECT

public:
    DemoWidget();

protected:
    QWidget *createPage(qint64 id) override;

private:
    QStackedWidget *m_stackedWidget = nullptr;
};

#endif // DEMOWIDGET_H
