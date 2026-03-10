#ifndef QHPAGE_H
#define QHPAGE_H

/**
 * @file       Qhpage.h
 * @brief      {文件说明}
 *
 * @author     wmz
 * @date       2026/02/28
 * @history
 */

#include <QWidget>
#include "QH_global.h"

class QhPagePrivate;

class QTHANDY_EXPORT QhPage
{
    Q_PRIVATE_VARIABLE(QhPage)

public:
    QhPage();
    ~QhPage();

    /// @brief enter page
    virtual void enterPage();
    /// @brief leave page
    virtual void leavePage();

    /// @brief Time interval since leaving the page(ms)
    qint64 leavePageInterval() const;
    /// @brief Time interval for entering the page(ms)
    qint64 enterPageInterval() const;

    /// @brief Is this the first time you have entered the page
    bool isFirstEnterPage() const;

    void setFirstEnterPage(bool b);
};

#endif // QHPAGE_H
