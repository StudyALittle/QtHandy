#ifndef DEMOWIDGET_H
#define DEMOWIDGET_H

#include <QStackedWidget>
#include <QWidget>
#include <QMap>
#include "demonavbarproxy.h"

class DemoWidget: public QWidget
{
    Q_OBJECT

public:
    DemoWidget();

protected:
    QWidget *createPage(qint64 id);

protected slots:
    void toPage(qint64 id);

private:
    QStackedWidget *m_stackedWidget = nullptr;
    QMap<qint64, QWidget*> m_pages;
};

#endif // DEMOWIDGET_H
