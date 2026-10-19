#include "qhscreencolorpicker.h"
#include "qhscreencolorpicker_p.h"
#include <QGuiApplication>
#include <QScreen>
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include "qhimageutil.h"

QhScreenColorPicker::QhScreenColorPicker():
    d(new QhScreenColorPickerPrivate(this))
{
    // 全屏、无边框、置顶、透明背景
    this->setWindowFlags(
        Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    this->setAttribute(Qt::WA_TranslucentBackground);
    // this->setAttribute(Qt::WA_NoSystemBackground, false);
    // this->setAttribute(Qt::WA_TransparentForMouseEvents, false);   // 确保不穿透

    this->setCursor(Qt::CrossCursor);
    this->setMouseTracking(true);

    // 覆盖所有屏幕
    QRect totalRect;
    for (auto &screen : QGuiApplication::screens())
        totalRect = totalRect.united(screen->geometry());
    this->setGeometry(totalRect);

    // 定时刷新放大镜
    d->timer = new QTimer(this);
    connect(d->timer, &QTimer::timeout, d.get(),
        &QhScreenColorPickerPrivate::updateMagnifier);
     d->timer->start(300);

    d->updateMagnifier();
}

QhScreenColorPicker::~QhScreenColorPicker()
{

}

void QhScreenColorPicker::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

#if 0
    if (!d->hasColor)
        return;

    // 半透明遮罩，让背景变暗，突出放大镜
    // painter.fillRect(rect(), QColor(0, 0, 0, 60));

    // 2. 画放大镜
    d->drawMagnifier(painter);

    // 3. 画颜色预览和十六进制文本
    QPoint pos = d->cursorPos - geometry().topLeft();

    QString hex = d->currentColor.name(QColor::HexRgb).toUpper();
    QString text = QString("%1  RGB(%2,%3,%4)")
       .arg(hex)
       .arg(d->currentColor.red())
       .arg(d->currentColor.green())
       .arg(d->currentColor.blue());

    QFont font = painter.font();
    font.setPointSize(10);
    painter.setFont(font);

    QFontMetrics fm(font);
    int textW = fm.horizontalAdvance(text) + 16;
    int textH = fm.height() + 10;

    // 文本放在放大镜下方
    QRect textRect(pos.x() - textW / 2,
                   pos.y() + d->kZoomRadius * d->kZoomFactor + 16,
                   textW, textH);

    // 防止超出屏幕
    QRect screenRect = QGuiApplication::screenAt(d->cursorPos)->geometry();
    QRect localScreenRect = screenRect.translated(-geometry().topLeft());
    if (textRect.right() > localScreenRect.right())
        textRect.moveRight(localScreenRect.right() - 4);
    if (textRect.left() < localScreenRect.left())
        textRect.moveLeft(localScreenRect.left() + 4);
    if (textRect.bottom() > localScreenRect.bottom())
        textRect.moveTop(pos.y() - textH - d->kZoomRadius * d->kZoomFactor - 16);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 180));
    painter.drawRoundedRect(textRect, 4, 4);

    painter.setPen(Qt::white);
    painter.drawText(textRect, Qt::AlignCenter, text);
#else
    if (!d->currentColor.isValid())
        return;

    // painter.fillRect(rect(), QColor(0, 0, 0, 1));
    painter.fillRect(QRect(d->cursorPos.x() - 6, d->cursorPos.y() - 6, 12, 12), Qt::gray);

    // 显示文本
    QString text = QString("%1 RGB(%2,%3,%4)")
       .arg(d->currentColor.name(QColor::HexRgb).toUpper())
       .arg(d->currentColor.red())
       .arg(d->currentColor.green())
       .arg(d->currentColor.blue());
    QFont font = painter.font();
    font.setPointSize(10);
    painter.setFont(font);

    QFontMetrics fm(font);
    int textW = fm.horizontalAdvance(text);
    int textH = fm.height();

    int cursorH = 36;
    int space = 12;
    QMargins mgs(6, 6, 6, 6);
    int colorRectSize = 26;

    int colorTextRectH = qMax(colorRectSize, textH) + mgs.top() + mgs.bottom();
    int colorTextRectW = colorRectSize + textW + space + mgs.left() + mgs.right();

    QRect colorTextRect(
        d->cursorPos.x() - colorTextRectW / 2,
        d->cursorPos.y() + cursorH,
        colorTextRectW, colorTextRectH);

    // 防止超出屏幕
    QRect screenRect = QGuiApplication::screenAt(d->cursorPos)->geometry();
    QRect localScreenRect = screenRect.translated(-geometry().topLeft());
    if (colorTextRect.right() > localScreenRect.right())
        colorTextRect.moveRight(localScreenRect.right() - 4);
    if (colorTextRect.left() < localScreenRect.left())
        colorTextRect.moveLeft(localScreenRect.left() + 4);
    if (colorTextRect.bottom() > localScreenRect.bottom())
        colorTextRect.moveTop(d->cursorPos.y() - colorTextRectH - 6);

    QRect colorRect(
        colorTextRect.x() + mgs.left(),
        colorTextRect.y() + (colorTextRectH - colorRectSize) / 2,
        colorRectSize, colorRectSize);

    QRect textRect(
        colorRect.x() + colorRect.width() + space,
        colorTextRect.y() + (colorTextRectH - textH) / 2,
        textW, textH);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 180));
    painter.drawRoundedRect(colorTextRect, 4, 4);

    painter.setPen(QColor(Qt::gray));
    painter.setBrush(d->currentColor);
    painter.drawRoundedRect(colorRect, 0, 0);

    painter.setPen(Qt::white);
    painter.drawText(textRect, Qt::AlignCenter, text);
#endif
}

void QhScreenColorPicker::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (d->hasColor) {
            emit colorPicked(d->currentColor);
        }
        close();
    } else if (event->button() == Qt::RightButton) {
        emit canceled();
        close();
    }
}

void QhScreenColorPicker::mouseMoveEvent(QMouseEvent *event)
{
    d->updateMagnifier();
    QWidget::mouseMoveEvent(event);
}

void QhScreenColorPicker::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        emit canceled();
        close();
    } else if (event->key() == Qt::Key_Return ||
               event->key() == Qt::Key_Enter) {
        if (d->hasColor)
            emit colorPicked(d->currentColor);
        close();
    }
}

QhScreenColorPickerPrivate::QhScreenColorPickerPrivate(QhScreenColorPicker *colorPicker):
    colorPicker(colorPicker)
{
    qApp->installEventFilter(this);
}

QhScreenColorPickerPrivate::~QhScreenColorPickerPrivate()
{

}

bool QhScreenColorPickerPrivate::eventFilter(QObject *obj, QEvent *event)
{
#if 1
    switch (event->type()) {
    case QEvent::MouseButtonPress: {
        auto *mouse = static_cast<QMouseEvent*>(event);
        if (mouse->button() == Qt::LeftButton) {
            if (hasColor) {
                emit colorPicker->colorPicked(currentColor);
            }
            colorPicker->close();
        } else if (mouse->button() == Qt::RightButton) {
            emit colorPicker->canceled();
            colorPicker->close();
        }
        break;
    }
    case QEvent::HoverMove:
    case QEvent::MouseMove: {
        updateMagnifier();
        break;
    }
    default:
        break;
    }
#endif
    return QObject::eventFilter(obj, event);
}

void QhScreenColorPickerPrivate::updateMagnifier()
{
    captureMode = true;
    colorPicker->update();
    QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);

    cursorPos = QCursor::pos();
    currentColor = QhImageUtil::getScreenColorAt(cursorPos);
    hasColor = currentColor.isValid();

    // 截取鼠标周围区域作为放大镜源图
    QScreen *screen = QGuiApplication::screenAt(cursorPos);
    if (!screen)
        screen = QGuiApplication::primaryScreen();

    QPoint localPos = screen->geometry().topLeft();
    int lx = cursorPos.x() - localPos.x();
    int ly = cursorPos.y() - localPos.y();

    int r = kZoomRadius;
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    magnifierPixmap = screen->grab(QRect(lx - r, ly - r, 2*r, 2*r));
#else
    magnifierPixmap = screen->grabWindow(0, lx - r, ly - r, 2*r, 2*r);
#endif

//    colorPicker->setWindowOpacity(1.0);
//    QCoreApplication::processEvents();

    captureMode = false;
    colorPicker->update();
    emit colorPicker->colorPicked(currentColor);
}

void QhScreenColorPickerPrivate::drawMagnifier(QPainter &p)
{
    if (magnifierPixmap.isNull())
        return;

    QPoint pos = cursorPos - colorPicker->geometry().topLeft();
    int size = kZoomRadius * 2 * kZoomFactor;

    // 放大镜区域
    QRect zoomRect(pos.x() - size / 2,
                   pos.y() - size / 2,
                   size, size);

    // 把源图放大
    QPixmap zoomed = magnifierPixmap.scaled(
        size, size, Qt::KeepAspectRatio, Qt::FastTransformation);

    // 裁剪成圆形
    QPainterPath clipPath;
    clipPath.addEllipse(zoomRect);
    p.save();
    p.setClipPath(clipPath);
    p.drawPixmap(zoomRect, zoomed);
    p.restore();

    // 边框
    p.setPen(QPen(Qt::white, 2));
    p.setBrush(Qt::NoBrush);
    p.drawEllipse(zoomRect);

    // 中心十字线
    p.setPen(QPen(Qt::white, 1));
    int cx = pos.x();
    int cy = pos.y();
    p.drawLine(cx - 8, cy, cx + 8, cy);
    p.drawLine(cx, cy - 8, cx, cy + 8);

    // 中心像素点（当前取到的颜色）
    p.setPen(QPen(QColor(0, 0, 0, 120), 1));
    p.setBrush(currentColor);
    int pixelSize = kZoomFactor;
    p.drawRect(QRect(cx - pixelSize / 2, cy - pixelSize / 2, pixelSize, pixelSize));
}
