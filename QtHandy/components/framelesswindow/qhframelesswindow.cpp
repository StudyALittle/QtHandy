#include "qhframelesswindow.h"
#include "qhframelesswindow_p.h"
#include <QApplication>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QWindowStateChangeEvent>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QLinearGradient>
#include <QtMath>

#ifdef Q_OS_WIN
#include <windows.h>
#include <WinUser.h>
#include <windowsx.h>
#include <dwmapi.h>
#include <objidl.h>
#include <gdiplus.h>

#pragma comment (lib,"Dwmapi.lib")
#pragma comment (lib,"user32.lib")
#endif

/////////////////////////// QhFramelessWindowPrivate ///////////////////////////

void QhFramelessWindowPrivate::initFramelessWindow(int borderRadius)
{
    setBorderRadius(borderRadius);

    // 无边框
    widget->setWindowFlags(
        widget->windowFlags()
        | Qt::FramelessWindowHint
        | Qt::WindowSystemMenuHint);

    // 鼠标移动不受子控件影响
    widget->setAttribute(Qt::WA_Hover);

#ifdef Q_OS_WIN
    if (borderRadius > 0) {
        // 设置背景透明，重新绘制背景
        widget->setAttribute(Qt::WA_TranslucentBackground);
        widget->setAttribute(Qt::WA_NoSystemBackground);
    } else {
        HWND hwnd = (HWND)widget->winId();
        DWORD style = ::GetWindowLong(hwnd, GWL_STYLE);

        // 此行代码可以带回Aero效果，同时也带回了标题栏和边框
        // 在nativeEvent()会再次去掉标题栏，保留阴影
        ::SetWindowLong(hwnd, GWL_STYLE, style | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);

        // 保留区域绘制系统阴影
        const MARGINS wshadow = { 1, 1, 1, 1 };
        DwmExtendFrameIntoClientArea(hwnd, &wshadow);
    }
#elif defined(Q_OS_LINUX)
    if (borderRadius > 0) {
        widget->setAttribute(Qt::WA_TranslucentBackground);
        widget->setAttribute(Qt::WA_NoSystemBackground);
    }
#endif
}

void QhFramelessWindowPrivate::setResizeable(bool b)
{
    bResizeable = b;
}

void QhFramelessWindowPrivate::setMoveable(bool b)
{
    bMoveable = b;
}

void QhFramelessWindowPrivate::setMaxNormalAtTitleBar(bool b)
{
    bMaxNormalAtTitleBar = b;
}

void QhFramelessWindowPrivate::setUseMacSystemButtom(bool b)
{
    bUseMacSystemButtom = b;
    widget->update();
}

void QhFramelessWindowPrivate::setTitleHeight(int n)
{
    titleHeight = n;
}

void QhFramelessWindowPrivate::setTitleBar(QWidget *w)
{
    titleBar = w;
}

void QhFramelessWindowPrivate::setTitleBarEnableChilds(const QList<QWidget*> &ws)
{
    titleBarEnableChilds = ws;
}

void QhFramelessWindowPrivate::setTitleBarDisableChilds(const QList<QWidget*> &ws)
{
    titleBarDisableChilds = ws;
}

void QhFramelessWindowPrivate::setBorderWidth(qreal n)
{
    borderWidth = n;
    widget->update();
}

void QhFramelessWindowPrivate::setBorderRadius(int n)
{
    borderRadius = n;
    widget->update();
}

void QhFramelessWindowPrivate::setBorderColor(const QColor &color)
{
    borderColor = color;
    widget->update();
}

void QhFramelessWindowPrivate::setBackgroundColor(const QColor &color)
{
    backgroundColor = color;
    widget->update();
}

void QhFramelessWindowPrivate::setShadowWidth(int n)
{
    shadowWidth = n;
    widget->update();
}

bool QhFramelessWindowPrivate::eventEx(QEvent *e)
{
    if (borderRadius > 0)
        return moveResizeHelpre->proccessEvent(e);
    return false;
}

void QhFramelessWindowPrivate::paintEventEx(QPaintEvent *e)
{
    Q_UNUSED(e)

    QPainter p(widget);

    // 设置去锯齿
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::SmoothPixmapTransform, true);
    // 绘制阴影
    paintShadowHelper(&p);
    // 绘制背景
    paintBackgroundHelper(&p);
    // 绘制边框
    paintBorderHelper(&p);
}

void QhFramelessWindowPrivate::paintShadowHelper(QPainter *p)
{
    if (widget->isMaximized() || widget->isFullScreen()
        || widget->isMinimized() || this->shadowWidth <= 0)
        return;

    // 绘制阴影
    p->save();
    // 绘制阴影
    auto fillAngle = [](QPainter &p, qreal radius,
            const QRectF &rectF,
            const QRectF &subRectF1,
            const QRectF &subRectF2,
            QRadialGradient &radiaColor)
    {
        QPainterPath path;
        path.addRoundedRect(rectF, radius, radius);

        QPainterPath subPath;
        subPath.addRect(subRectF1);
        subPath.addRect(subRectF2);
        path -= subPath;

        radiaColor.setFocalPoint(rectF.center());
        radiaColor.setCenter(rectF.center());
        p.fillPath(path, QBrush(radiaColor));
    };

    auto fillBorder = [](QPainter &p, const QRectF &rectF,
                        QLinearGradient &lineGrad)
    {
        QPainterPath path;
        path.addRect(rectF);
        p.fillPath(path, QBrush(lineGrad));
    };

    auto brds = this->borderRadius;
    qreal sw = this->shadowWidth;
    auto rect = QRect(sw, sw, widget->width() - sw * 2, widget->height() - sw * 2);

    QColor colStart, colCenter, colCenter2, colStop;
    if (widget->isActiveWindow()) {
        colStart = QColor(0, 0, 0, 32);
        colCenter = QColor(0, 0, 0, 16);
        colCenter2 = QColor(0, 0, 0, 8);
        colStop = QColor(0, 0, 0, 2);
    } else {
        colStart = QColor(0, 0, 0, 20);
        colCenter = QColor(0, 0, 0, 10);
        colCenter2 = QColor(0, 0, 0, 5);
        colStop = QColor(0, 0, 0, 0);
    }

    // hypotenuse: 斜边长度
    // angleDeg:   斜边与邻边夹角（单位：度）
//    auto calcAdjacent = [](qreal hypotenuse, qreal angleDeg) -> qreal
//    {
//        double angleRad = qDegreesToRadians(angleDeg);
//        return hypotenuse * qCos(angleRad);
//    };

    int w = widget->width();
    int h = widget->height();

    qreal radius = sw + this->borderRadius;
    qreal len = radius * 2.0;

    qreal colAtBg = 1.0 - sw/radius;
    QRadialGradient radiaColor;
    radiaColor.setRadius(radius);
    radiaColor.setCenterRadius(radius);
    radiaColor.setColorAt(0, colStart);
    radiaColor.setColorAt(colAtBg, colStart);
    radiaColor.setColorAt(colAtBg + 0.3 * (sw/radius), colCenter);
    radiaColor.setColorAt(colAtBg + 0.5 * (sw/radius), colCenter2);
    radiaColor.setColorAt(1, colStop);

    QRectF rectLeftTop(0, 0, len, len);
    QRectF rectLeftBottom(0, h - len, len, len);
    QRectF rectRightTop(w - len, 0, len, len);
    QRectF rectRightBottom(w - len, h - len, len, len);

    // 左上角
    fillAngle(*p, radius, rectLeftTop,
              QRectF(radius, 0, radius, len),
              QRectF(0, radius, radius, radius),
              radiaColor);

    // 右上角
    fillAngle(*p, radius, rectRightTop,
              QRectF(w - len, 0, radius, len),
              QRectF(w - radius, radius, radius, radius),
              radiaColor);

    // 左下角
    fillAngle(*p, radius, rectLeftBottom,
              QRectF(0, h - len, radius, radius),
              QRectF(radius, h - len, radius, len),
              radiaColor);

    // 右下角
    fillAngle(*p, radius, rectRightBottom,
              QRectF(w - len, h - len, radius, len),
              QRectF(w - radius, h - len, radius, radius),
              radiaColor);

    QLinearGradient lineGrad;
    lineGrad.setColorAt(0, colStart);
    lineGrad.setColorAt(0.3, colCenter);
    lineGrad.setColorAt(0.5, colCenter2);
    lineGrad.setColorAt(1, colStop);

    // 左边
    lineGrad.setStart(sw, 0);
    lineGrad.setFinalStop(0, 0);
    fillBorder(*p, QRectF(0, rect.y() + brds, sw, rect.height() - brds*2), lineGrad);

    // 右边
    lineGrad.setStart(rect.right(), 0);
    lineGrad.setFinalStop(w, 0);
    fillBorder(*p, QRectF(w - sw, sw + brds, sw, rect.height() - brds*2), lineGrad);

    // 上边
    lineGrad.setStart(0, sw);
    lineGrad.setFinalStop(0, 0);
    fillBorder(*p, QRectF(rect.x() + brds, 0, rect.width() - brds*2, sw), lineGrad);

    // 下边
    lineGrad.setStart(0, h - sw);
    lineGrad.setFinalStop(0, h);
    fillBorder(*p, QRectF(sw + brds, h - sw, rect.width() - brds*2, sw), lineGrad);

    p->restore();
}

void QhFramelessWindowPrivate::paintBorderHelper(QPainter *p)
{
    if (widget->isMaximized() || widget->isFullScreen()
        || widget->isMinimized() || this->borderWidth <= 0)
        return;

    p->save();
    p->setPen(QPen(this->borderColor, this->borderWidth));
    if (this->borderRadius <= 0) {
        // 绘制边框
        p->drawRect(
            QRectF(this->borderWidth, this->borderWidth,
                widget->width() - this->borderWidth * 2,
                widget->height() - this->borderWidth * 2
#ifdef Q_OS_WIN
                   - 1 // 窗口下边框底部减少1像素
#endif
                   ));
    } else {
        auto sw = this->shadowWidth;
        bool bMax = widget->isMaximized() || widget->isFullScreen();
        if (bMax)
            sw = 0;
        auto rectF = QRectF(this->borderWidth + sw, this->borderWidth + sw,
            widget->width() - this->borderWidth * 2 - sw * 2,
            widget->height() - this->borderWidth * 2 - sw * 2);
        QPainterPath path;
        path.addRoundedRect(rectF, this->borderRadius, this->borderRadius);
        // 绘制圆角边框
        p->drawPath(path);
    }
    p->restore();
}

void QhFramelessWindowPrivate::paintBackgroundHelper(QPainter *p)
{
    if (this->borderRadius <= 0)
        return;

    auto sw = this->shadowWidth;
    bool bMax = widget->isMaximized() || widget->isFullScreen();
    if (bMax)
        sw = 0;
    auto rectF = QRectF(this->borderWidth + sw, this->borderWidth + sw,
        widget->width() - this->borderWidth * 2 - sw * 2,
        widget->height() - this->borderWidth * 2 - sw * 2);

    p->save();
    QPainterPath path;
    if (bMax)
        path.addRect(rectF);
    else
        path.addRoundedRect(rectF, this->borderRadius, this->borderRadius);
    p->fillPath(path, p->background());
    p->restore();
}

/////////////////////////// QhFramelessWindowPrivate end ///////////////////////////


QhFramelessWindow::QhFramelessWindow(QWidget *widget):
    d(new QhFramelessWindowPrivate(this, widget))
{

}

QhFramelessWindow::~QhFramelessWindow()
{

}

void QhFramelessWindow::initFramelessWindow(int borderRadius)
{
    d->initFramelessWindow(borderRadius);
}

bool QhFramelessWindow::isFramelessWindow()
{
    return d->bFramelessWindow;
}

bool QhFramelessWindow::isResizeable()
{
    return d->bResizeable;
}

bool QhFramelessWindow::isMoveable()
{
    return d->bMoveable;
}

bool QhFramelessWindow::isMaxNormalAtTitleBar()
{
    return d->bMaxNormalAtTitleBar;
}

bool QhFramelessWindow::isUseMacSystemButtom()
{
    return d->bUseMacSystemButtom;
}

int QhFramelessWindow::titleHeight()
{
    return d->titleHeight;
}

QWidget *QhFramelessWindow::titleBar()
{
    return d->titleBar;
}

QList<QWidget*> QhFramelessWindow::titleBarEnableChilds()
{
    return d->titleBarEnableChilds;
}

QList<QWidget*> QhFramelessWindow::titleBarDisableChilds()
{
    return d->titleBarDisableChilds;
}

qreal QhFramelessWindow::borderWidth()
{
    return d->borderWidth;
}

int QhFramelessWindow::borderRadius()
{
    return d->borderRadius;
}

QColor QhFramelessWindow::borderColor()
{
    return d->borderColor;
}

QColor QhFramelessWindow::backgroundColor()
{
    return d->backgroundColor;
}

int QhFramelessWindow::shadowWidth()
{
    return d->shadowWidth;
}

void QhFramelessWindow::setResizeable(bool b)
{
    d->setResizeable(b);
}

void QhFramelessWindow::setMoveable(bool b)
{
    d->setMoveable(b);
}

void QhFramelessWindow::setMaxNormalAtTitleBar(bool b)
{
    d->setMaxNormalAtTitleBar(b);
}

void QhFramelessWindow::setUseMacSystemButtom(bool b)
{
    d->setUseMacSystemButtom(b);
}

void QhFramelessWindow::setTitleHeight(int n)
{
    d->setTitleHeight(n);
}

void QhFramelessWindow::setTitleBar(QWidget *w)
{
    d->setTitleBar(w);
}

void QhFramelessWindow::setTitleBarEnableChilds(const QList<QWidget*> &ws)
{
    d->setTitleBarEnableChilds(ws);
}

void QhFramelessWindow::setTitleBarDisableChilds(const QList<QWidget*> &ws)
{
    d->setTitleBarDisableChilds(ws);
}

void QhFramelessWindow::setBorderWidth(qreal n)
{
    d->setBorderWidth(n);
}

void QhFramelessWindow::setBorderRadius(int n)
{
    d->setBorderRadius(n);
}

void QhFramelessWindow::setBorderColor(const QColor &color)
{
    d->setBorderColor(color);
}

void QhFramelessWindow::setBackgroundColor(const QColor &color)
{
    d->setBackgroundColor(color);
}

void QhFramelessWindow::setShadowWidth(int n)
{
    d->setShadowWidth(n);
}

QWidget *QhFramelessWindow::widget()
{
    return d->widget;
}

#define FUNC_NATIVEEVENT(Widget) \
    if (d->nativeEventEx(eventType, message, result)) \
        return true; \
    return Widget::nativeEvent(eventType, message, result)

#define FUNC_EVENT(Widget) \
    if (d->eventEx(e)) \
        return true; \
    return Widget::event(e)

#define FUNC_PAINTEVENT(Widget) \
    if (this->borderRadius() <= 0) \
        Widget::paintEvent(e); \
    d->paintEventEx(e)

QhFramelessMainWindow::QhFramelessMainWindow(QWidget *parent):
    QMainWindow(parent), QhFramelessWindow(this)
{

}

bool QhFramelessMainWindow::nativeEvent(const QByteArray &eventType, void *message, NATIVATEEVENTFUNC_3PARAM_TYPE *result)
{
    FUNC_NATIVEEVENT(QMainWindow);
}

bool QhFramelessMainWindow::event(QEvent *e)
{
    FUNC_EVENT(QMainWindow);
}

void QhFramelessMainWindow::paintEvent(QPaintEvent *e)
{
    FUNC_PAINTEVENT(QMainWindow);
}

QhFramelessWidget::QhFramelessWidget(QWidget *parent):
    QWidget(parent), QhFramelessWindow(this)
{

}

bool QhFramelessWidget::nativeEvent(const QByteArray &eventType, void *message, NATIVATEEVENTFUNC_3PARAM_TYPE *result)
{
    FUNC_NATIVEEVENT(QWidget);
}

bool QhFramelessWidget::event(QEvent *e)
{
    FUNC_EVENT(QWidget);
}

void QhFramelessWidget::paintEvent(QPaintEvent *e)
{
    FUNC_PAINTEVENT(QWidget);
}

QhFramelessDialog::QhFramelessDialog(QWidget *parent):
    QDialog(parent), QhFramelessWindow(this)
{

}

bool QhFramelessDialog::nativeEvent(const QByteArray &eventType, void *message, NATIVATEEVENTFUNC_3PARAM_TYPE *result)
{
    FUNC_NATIVEEVENT(QDialog);
}

bool QhFramelessDialog::event(QEvent *e)
{
    FUNC_EVENT(QDialog);
}

void QhFramelessDialog::paintEvent(QPaintEvent *e)
{
    FUNC_PAINTEVENT(QDialog);
}
