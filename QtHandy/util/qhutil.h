#ifndef QHUTIL_H
#define QHUTIL_H

#include <QObject>
#include <QString>
#include "QH_global.h"

class QTHANDY_EXPORT QhUtil
{
public:
    /// @brief Login system username
    static QString systemLoginUserName();

    /// @brief windows version(7/8/10/11)
    static int windowsVersion();
};

#endif // QHUTIL_H
