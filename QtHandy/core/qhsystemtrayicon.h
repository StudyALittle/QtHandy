#ifndef QHSYSTEMTRAYICON_H
#define QHSYSTEMTRAYICON_H

#include <QSystemTrayIcon>
#include <QSharedPointer>
#include <QMenu>
#include <QAction>
#include <QEvent>
#include <QIcon>
#include "QH_global.h"

class QhSystemTrayIconPrivate;
class QhSystemTrayIconItemPrivate;

class QTHANDY_EXPORT QhSystemTrayIconItem: public QObject
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhSystemTrayIconItem)

public:
    using Ptr = QSharedPointer<QhSystemTrayIconItem>;

    QhSystemTrayIconItem(QObject *parent = nullptr);
    QhSystemTrayIconItem(int id, const QString &name, QObject *parent = nullptr);
    QhSystemTrayIconItem(bool bSeparator, QObject *parent = nullptr);
    ~QhSystemTrayIconItem();

    bool isSeparator() const;
    int id() const;
    QString name() const;
    QAction *action();

    void setSeparator(bool b);
    void setId(int id);
    void setName(const QString &name);
    void setAction(QAction *action);
};

class QTHANDY_EXPORT QhSystemTrayIcon: public QSystemTrayIcon
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhSystemTrayIcon)

public:
    enum ID {
        ExitProgram = 0,    // 退出程序
        OpenMainWindow,     // 打开主窗口
        CustomID = 10       // 自定义ID
    };

    QhSystemTrayIcon(QObject *parent = nullptr);
    QhSystemTrayIcon(const QIcon &icon, QObject *parent = nullptr);

    ~QhSystemTrayIcon();

    void setItems(const QList<QhSystemTrayIconItem*> &items);

    void setIcon(const QIcon &icon);
    void setFlickerIcon(const QIcon &icon);

    QhSystemTrayIconItem *item(int id);
    QIcon flickerIcon() const;

    void startFlickerIcon(int msec = 500);
    void stopFlickerIcon();

signals:
    void itemClicked(int id);
};

#endif // QHSYSTEMTRAYICON_H
