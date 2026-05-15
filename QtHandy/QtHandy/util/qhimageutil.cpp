#include "qhimageutil.h"
#include <QPainter>
#include <QSvgRenderer>

QPixmap QhImageUtil::pixmap(const QString &path, const QSize &size,
    Qt::AspectRatioMode aspectMode, Qt::TransformationMode mode)
{
    QPixmap pixmap(path);
    if (size.isValid()) {
        pixmap = pixmap.scaled(size, aspectMode, mode);
    }
    return pixmap;
}

QPixmap QhImageUtil::svgToPixmap(const QString &svgPath,
    const QColor &color, const QSize &size)
{
    QImage image(size.isValid() ? size : QSize(20, 20),
        QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);

    QPainter painter(&image);

    QSvgRenderer svg(svgPath);
    painter.setBrush(color);
    painter.setPen(color);
    svg.render(&painter);

    auto img = QPixmap::fromImage(image);

    QPainter qp(&img);
    qp.setCompositionMode(QPainter::CompositionMode_SourceIn);
    qp.fillRect(img.rect(), QColor(color));
    qp.end();

    return img;
}

QIcon QhImageUtil::svgToIcon(const QString &svgPath,
    const QColor &color, const QSize &size)
{
    QPixmap img = svgToPixmap(svgPath, color, size);

    QIcon icon;
    icon.addPixmap(img, QIcon::Normal, QIcon::On);
    return icon;
}
