#ifndef QHSYSTEMTRAYICON_H
#define QHSYSTEMTRAYICON_H

/**
 * @file       qhsystemtrayicon.h
 * @brief      托盘功能，支持图标闪烁，支持鼠标移入托盘图标等功能
 *
 * @author     wmz
 * @date       2026/09/09
 * @history
 */

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

    /// @brief 开启图标闪烁
    void startFlickerIcon(int msec = 500);

    /// 停止图标闪烁
    void stopFlickerIcon();

    /// @brief 开启监听鼠标移入托盘消息（目前windows有效）
    bool startTrayMoveMessage();

    /// @brief 停止监听鼠标移入托盘消息（目前windows有效）
    void stopTrayMoveMessage();

signals:
    void itemClicked(int id);
    void entered();
    void leaved();

public:
    void setMouseInTray(bool b);
};

#endif // QHSYSTEMTRAYICON_H
