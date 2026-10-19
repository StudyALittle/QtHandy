#include "qhimageutil.h"
#include <QPainter>
#include <QSvgRenderer>
#include <QScreen>
#include <QGuiApplication>
#ifdef WIN32
#include <Windows.h>

#pragma comment(lib, "gdi32.lib")
#endif

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

QColor QhImageUtil::getScreenColorAt(const QPoint &pos)
{
#ifdef WIN32
#if 0
    HDC hdc = GetDC(nullptr);
    COLORREF cr = GetPixel(hdc, pos.x(), pos.y());
    ReleaseDC(nullptr, hdc);
    if (cr == CLR_INVALID)
        return QColor();
    return QColor(GetRValue(cr), GetGValue(cr), GetBValue(cr));
#else
    HDC hdcScreen = GetDC(nullptr);
    HDC hdcMem = CreateCompatibleDC(hdcScreen);
    HBITMAP hbm = CreateCompatibleBitmap(hdcScreen, 1, 1);
    HGDIOBJ old = SelectObject(hdcMem, hbm);

    // 把屏幕 (x, y) 处的 1x1 像素拷贝到内存 DC
    BitBlt(hdcMem, 0, 0, 1, 1, hdcScreen, pos.x(), pos.y(), SRCCOPY);

    // 从内存位图取像素
    COLORREF cr = GetPixel(hdcMem, 0, 0);

    SelectObject(hdcMem, old);
    DeleteObject(hbm);
    DeleteDC(hdcMem);
    ReleaseDC(nullptr, hdcScreen);

    if (cr == CLR_INVALID)
        return QColor();
    return QColor(GetRValue(cr), GetGValue(cr), GetBValue(cr));
#endif
#else
    QScreen *screen = QGuiApplication::screenAt(pos);
    if (!screen) {
        screen = QGuiApplication::primaryScreen();
    }

    // 将全局坐标转换为该屏幕的本地坐标
    QPoint localPos = screen->geometry().topLeft();
    int localX = pos.x() - localPos.x();
    int localY = pos.y() - localPos.y();

    // 截取 1x1 像素
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    QPixmap pixmap = screen->grab(QRect(localX, localY, 1, 1));
#else
    QPixmap pixmap = screen->grabWindow(0, localX, localY, 1, 1);
#endif

    // 转换为 QImage 并读取颜色
    QImage image = pixmap.toImage();
    if (image.isNull() || image.width() < 1 || image.height() < 1)
        return QColor();

    int cx = image.width() / 2;
    int cy = image.height() / 2;
    return QColor(image.pixel(cx, cy));
#endif
}
