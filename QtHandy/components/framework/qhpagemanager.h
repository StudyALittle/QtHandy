#ifndef QHPAGEMANAGER_H
#define QHPAGEMANAGER_H

/**
 * @file       Qhpagemanager.h
 * @brief      page manager class
 * @details    This class manages pages in an application, providing functionality to enter and leave pages,
 *            create page windows, and manage page switch animations. It also provides functionality to insert
 *            and take page widgets, as well as to check if page switch animations are enabled.
 * 
 * @example    
 *  class WidgetManager: public QWidget, public QhPageManager
 *  {
 *  public:
 *      QWidget *createPage(qint64 id) override { // create and return a page widget }
 *      void leavePage(qint64 id) override 
 *      { 
 *          // if too many pages, we can delete the page, such as:
 *          if (pages().size() > 10)  {
 *              QWidget *page = takePage(id);
 *              page->deleteLater();
 *          }
 *      }
 *  };
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

    /// @brief Get stacked widget
    QStackedWidget *stackedWidget() const;

    /// @brief Set stacked widget
    void setStackedWidget(QStackedWidget *sw);

    /// @brief Get all pages in the page manager
    QMap<qint64, QWidget*> pages() const;

    /// @brief  enter page
    virtual QWidget *enterPage(qint64 id);

    /// @brief  leave page
    virtual void leavePage(qint64 id);

    /// @brief Create page window
    /// Warring: Must inherit QhPage
    virtual QWidget *createPage(qint64 id) = 0;

    /// @brief Get page widget
    QWidget *getPage(qint64 id);

    /// @brief Get page id
    qint64 pageID(QWidget *w);

    /// @brief Insert page widget
    /// Warring: Must inherit QhPage
    void insertPage(qint64 id, QWidget *page);

    /// @brief Take page widget
    QWidget *takePage(qint64 id);

    /// @brief Whether page switch animation is enabled  
    bool isPageSwitchAnim() const;

    /// @brief  Set page switch animation 
    void setPageSwitchAnim(bool anim);

    /// @brief page switch animation
    virtual void pageSwitchAnim(QWidget *leavePage, QWidget *enterPage);
};

#endif // QHPAGEMANAGER_H
