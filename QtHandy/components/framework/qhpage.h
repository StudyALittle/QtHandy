#ifndef QHPAGE_H
#define QHPAGE_H

/**
 * @file       Qhpage.h
 * @brief      page class
 * @details    This class represents a page in an application, providing functionality to enter and leave the page,
 *             whether it is the first time entering the page. 
 * 
 * @example    
 *  class Widget: public QWidget, public QhPage 
 * {
 * public:
 *     void enterPage() override { // do something, such as timer start }
 *     void leavePage() override { // do something, such as timer stop }
 * }
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

    /// @brief Set whether it is the first time entering the page
    void setFirstEnterPage(bool b);
};

#endif // QHPAGE_H
