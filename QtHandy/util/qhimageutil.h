#ifndef QHIMAGEUTIL_H
#define QHIMAGEUTIL_H

#include <QIcon>
#include <QImage>
#include <QPixmap>
#include "QH_global.h"

class QTHANDY_EXPORT QhImageUtil
{
public:
    static QPixmap pixmap(const QString &path, const QSize &size = QSize(),
        Qt::AspectRatioMode aspectMode = Qt::KeepAspectRatio,
        Qt::TransformationMode mode = Qt::SmoothTransformation);

    static QPixmap svgToPixmap(const QString &svgPath,
        const QColor &color, const QSize &size = QSize());

    static QIcon svgToIcon(const QString &svgPath,
        const QColor &color = QColor(), const QSize &size = QSize());
};

#endif // QHIMAGEUTIL_H
