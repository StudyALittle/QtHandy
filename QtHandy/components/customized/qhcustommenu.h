#ifndef QHCUSTOMMENU_H
#define QHCUSTOMMENU_H

/**
 * @file       qhcustommenu.h
 * @brief      自定义菜单栏
 *
 * @author     wmz
 * @date       2026/09/10
 * @history
 */

#include <QAbstractButton>
#include "qhfloating.h"
#include "QH_global.h"

class QhCustomMenuPrivate;

class QTHANDY_EXPORT QhCustomMenu: public QhFloating
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhCustomMenu)

public:
    QhCustomMenu(QWidget *parent = nullptr);
    ~QhCustomMenu();

    QAbstractButton *button(int id);

    void addButton(QAbstractButton *button, int id = -1);
    QAbstractButton *addButton(const QString &text, int id = -1);

    void exec(const QPoint &pos);
    void exec(QWidget *alignWidget);

signals:
    void clicked(QAbstractButton *button, int id);
};

#endif // QHCUSTOMMENU_H
