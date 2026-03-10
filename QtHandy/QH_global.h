#ifndef QH_GLOBAL_H
#define QH_GLOBAL_H

#include <QtCore/qglobal.h>
#include "qhmacro.h"
#include "qhdefine.h"

#if defined(QTHANDY_LIBRARY)
#  define QTHANDY_EXPORT Q_DECL_EXPORT
#else
#  define QTHANDY_EXPORT Q_DECL_IMPORT
#endif

#endif // QH_GLOBAL_H
