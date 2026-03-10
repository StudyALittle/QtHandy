#ifndef QHFLOATING_H
#define QHFLOATING_H

/**
 * @file       Qhfloating.h
 * @brief      Floating window, close the current window when losing focus
 *
 * @author     wmz
 * @date       2026/02/27
 * @history
 */

#include <QWidget>
#include "qhframelesswindow.h"
#include "QH_global.h"

class QhFloatingPrivate;

class QTHANDY_EXPORT QhFloating: public QhFramelessWidget
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhFloating)

public:
    QhFloating(QWidget *parent = nullptr);
    QhFloating(bool bBase, QWidget *parent = nullptr);
    ~QhFloating();

    /// @brief The "closed()" signal is sent, when losing focus, or click outside the window with the mouse
    /// default: true
    /// note: takes effect when true
    bool isCloseAtFocusOut() const;

    /// @brief Ignore focus loss window.
    /// note: isCloseAtFocusOut() takes effect when true
    QVector<QWidget*> ignoreWidgets() const;

    void setCloseAtFocusOut(bool b);
    void setIgnoreWidgets(const QVector<QWidget*> &ws);

    void open(const QPoint &pos);
    void openShadowEffect();

signals:
    void closed();

protected:
    bool eventFilter(QObject *o, QEvent *e) override;
};

#endif // QHFLOATING_H
