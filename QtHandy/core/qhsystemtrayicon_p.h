#ifndef QHSYSTEMTRAYICON_P_H
#define QHSYSTEMTRAYICON_P_H

#include <QAbstractNativeEventFilter>
#include <QTimer>
#ifdef Q_OS_WIN
#include <windows.h>
#endif
#include "qhsystemtrayicon.h"

class QhSystemTrayIconItemPrivate: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhSystemTrayIconItemPrivate)

public:
    QhSystemTrayIconItemPrivate();
    ~QhSystemTrayIconItemPrivate();

    bool bSeparator = false; // 是不是分割线
    int id;
    QString name;

    QAction *action = nullptr;
};

class QhSystemTrayIconPrivate: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhSystemTrayIconPrivate)

public:
    QhSystemTrayIconPrivate(QhSystemTrayIcon *sysTrayIcon);
    ~QhSystemTrayIconPrivate();

    QhSystemTrayIcon *systemTrayIcon;
    QList<QhSystemTrayIconItem*> items;

    QIcon normalIcon;
    QIcon flickerIcon;          // 闪烁的图标
    bool flickerState = false;
    QTimer *flickerTimer = nullptr;

    QMenu *menu = nullptr;

#ifdef Q_OS_WIN
    HHOOK mouseHook = NULL;
#endif

    bool bMouseInTray = false;
    static QList<QhSystemTrayIcon*> s_systemTrayIcons;
};

#endif // QHSYSTEMTRAYICON_P_H
