#ifndef QHFILEUTIL_H
#define QHFILEUTIL_H

#include <QString>
#include "QH_global.h"

class QTHANDY_EXPORT QhFileUtil
{
public:
    static QString readFileText(const QString &fileName);
};

#endif // QHFILEUTIL_H
