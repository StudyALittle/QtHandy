#include "qhutil.h"
#include <QOperatingSystemVersion>
#ifdef Q_OS_WIN
#include <windows.h>
#include <lmcons.h>
#else
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#endif

#pragma comment (lib,"Advapi32.lib")

QString QhUtil::systemLoginUserName()
{
#ifdef Q_OS_WIN
    WCHAR username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    if (GetUserName(username, &username_len))
        return QString::fromWCharArray(username);
#else
    struct passwd *pw = getpwuid(getuid());
    if (pw)
        return QString(pw->pw_name);
#endif
    return QString();
}

int QhUtil::windowsVersion()
{
    auto ver = QOperatingSystemVersion::current();

    if (ver < QOperatingSystemVersion::Windows8)
        return 7; // Windows 7 or earlier
    else if (ver < QOperatingSystemVersion::Windows10)
        return 8; // Windows 8/8.1
    else {
        if (ver.microVersion() >= 22000)
            return 11; // Windows 11;
        else
            return 10; // Windows 10;
    }
}
