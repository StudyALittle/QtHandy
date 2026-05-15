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

    virtual QWidget *enterPage(qint64 id);
    virtual void leavePage(qint64 id);

    /// @brief Create page window
    /// Warring: Must inherit QhPage
    virtual QWidget *createPage(qint64 id) = 0;

    QWidget *getPage(qint64 id);
    qint64 pageID(QWidget *w);
    void insertPage(qint64 id, QWidget *page);
    QWidget *takePage(qint64 id);
};

#endif // QHPAGEMANAGER_H
