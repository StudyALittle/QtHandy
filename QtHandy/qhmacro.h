#ifndef QHMACRO_H
#define QHMACRO_H

#include <QObject>

#define Q_PRIVATE_VARIABLE(Class) \
private: \
    QScopedPointer<Class##Private> d; \
    Q_DISABLE_COPY(Class) \
    friend class Class##Private;

#define Q_PROPERTY_EX(TYPE, M)                                  \
    Q_PROPERTY(TYPE p##M READ get##M WRITE set##M NOTIFY p##M##Changed) \
public:                                                                 \
    Q_SIGNAL void p##M##Changed();

// Window and LINUX, the same code
#if defined(Q_OS_WIN) || defined(Q_OS_LINUX)
    #define WIN_UNIX_SAMECODE(WinAndUnixSrc, QtherSrc) WinAndUnixSrc
#else
    #define WIN_UNIX_SAMECODE(WinAndUnixSrc, QtherSrc) QtherSrc
#endif

// Window and MAC, the same code
#if defined(Q_OS_WIN) || defined(Q_OS_MAC)
    #define WIN_MAC_SAMECODE(WinAndMacSrc, QtherSrc) WinAndMacSrc
#else
    #define WIN_MAC_SAMECODE(WinAndMacSrc, QtherSrc) QtherSrc
#endif

// LINUX and MAC, the same code
#if defined(Q_OS_LINUX) || defined(Q_OS_MAC)
    #define UNIX_MAC_SAMECODE(UnixAndMacSrc, QtherSrc) UnixAndMacSrc
#else
    #define UNIX_MAC_SAMECODE(UnixAndMacSrc, QtherSrc) QtherSrc
#endif

#endif // QHMACRO_H
