#ifndef QHPAGEMANAGER_H
#define QHPAGEMANAGER_H

/**
 * @file       Qhpagemanager.h
 * @brief      {文件说明}
 *
 * @author     wmz
 * @date       2026/02/28
 * @history
 */

#include <QWidget>
#include <QStackedWidget>
#include "QH_global.h"

class QhPageManagerPrivate;

class QTHANDY_EXPORT QhPageManager
{
    Q_PRIVATE_VARIABLE(QhPageManager)

public:
    QhPageManager(QStackedWidget *stackedWidget = nullptr);
    ~QhPageManager();

    QStackedWidget *stackedWidget() const;
    void setStackedWidget(QStackedWidget *sw);

    virtual QWidget *enterPage(int id);
    virtual void leavePage(int id);

    /// @brief Create page window
    /// Warring: Must inherit QhPage
    virtual QWidget *createPage(int id) = 0;

    QWidget *getPage(int id);
    int pageID(QWidget *w);
    void insertPage(int id, QWidget *page);
    QWidget *takePage(int id);
};

#endif // QHPAGEMANAGER_H
