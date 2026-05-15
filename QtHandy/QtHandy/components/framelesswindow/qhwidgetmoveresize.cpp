#include "qhwidgetmoveresize.h"
#include "qhwidgetmoveresize_p.h"
#include <QApplication>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QWindowStateChangeEvent>
#include <QPainter>
#include <QTimer>
#include <QLinearGradient>
#include <QDebug>

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

#ifndef HTLEFT
#define HTLEFT 1
#endif
#ifndef HTRIGHT
#define HTRIGHT 2
#endif
#ifndef HTBOTTOM
#define HTBOTTOM 3
#endif
#ifndef HTTOP
#define HTTOP 4
#endif
#ifndef HTBOTTOMLEFT
#define HTBOTTOMLEFT 5
#endif
#ifndef HTTOPRIGHT
#define HTTOPRIGHT 6
#endif
#ifndef HTBOTTOMRIGHT
#define HTBOTTOMRIGHT 7
#endif
#ifndef HTTOPLEFT
#define HTTOPLEFT 8
#endif

QhWidgetMoveResize::QhWidgetMoveResize(QhFramelessWindow *fwidget):
    d(new QhWidgetMoveResizePrivate(this, fwidget))
{

}

QhWidgetMoveResize::~QhWidgetMoveResize()
{
    delete d;
}

bool QhWidgetMoveResize::proccessEvent(QEvent *event)
{
    return d->proccessEvent(event);
}

void QhWidgetMoveResize::windowsNativeEventMove(void *message)
{
    d->windowsNativeEventMove(message);
}

void QhWidgetMoveResize::moveResize(const QPoint &pos)
{
    d->moveResize(pos);
}

bool QhWidgetMoveResize::isInTitleBar(QPoint pos, bool *bInTitleWidget)
{
    return d->isInTitleBar(pos, bInTitleWidget);
}

long QhWidgetMoveResize::calcMousePos(const QRect &rect, const QPoint &pos)
{
    return d->calcMousePos(rect, pos);
}

bool QhWidgetMoveResizePrivate::proccessEvent(QEvent *event)
{
    switch (event->type()) {
    case QEvent::Show: {
        updateWindowState();
        break;
    }
    case QEvent::Resize: {
        break;
    }
    case QEvent::WindowStateChange: {
        auto *sev = static_cast<QWindowStateChangeEvent*>(event);
        proccessWindowStateChange(sev);
        break;
    }
    case QEvent::WindowDeactivate: {
        proccessWindowDeactivate();
        break;
    }
    case QEvent::MouseButtonPress: {
        auto *mev = static_cast<QMouseEvent*>(event);
        proccessMouseButtonPress(mev);
        break;
    }
    case QEvent::MouseButtonRelease: {
        auto *mev = static_cast<QMouseEvent*>(event);
        proccessMouseButtonRelease(mev);
        break;
    }
    case QEvent::HoverLeave:{
        auto *hev = static_cast<QHoverEvent*>(event);
        proccessMouseButtonRelease(hev);
        break;
    }
    case QEvent::MouseMove: {
#ifndef Q_OS_WIN
        auto *mev = static_cast<QMouseEvent*>(event);
        if (mev->flags() == Qt::MouseEventCreatedDoubleClick)
            break;
        moveResize(mev->pos());
#endif
        break;
    }
    case QEvent::HoverMove: {
#ifndef Q_OS_WIN
        auto *hev = static_cast<QHoverEvent*>(event);
        moveResize(hev->pos());
#endif
        break;
    }
    case QEvent::MouseButtonDblClick: {
        proccessMouseDoubleClicked();
        break;
    }
    default: break;
    }
    return false;
}

void QhWidgetMoveResizePrivate::moveResize(const QPoint &pos)
{
    verifyResize(pos);

    if ((!framelessWidget->isResizeable()
         && !framelessWidget->isMoveable()) || !m_bLeftPress)
        return;

    bool bInTitleWidget = false;
    auto *widget = framelessWidget->widget();
    bool bFirstWillMove = (m_optState == ENothing && framelessWidget->isMoveable()
        && m_mouseBorderPos == 0 && !widget->isFullScreen()
        && isInTitleBar(widget->mapToGlobal(m_leftPressMousePos), &bInTitleWidget));

    if (bFirstWillMove || m_optState == EMove) {
        // 移动
        m_optState = EMove;
        auto gpos = widget->mapToGlobal(pos);
        if (bFirstWillMove && widget->isMaximized()) {
            int oldWidth = widget->width();
            int oldHeight = widget->height();
            // 显示正常大小
            widget->showNormal();
            // 窗口定位到鼠标位置
            // 计算鼠标相对于标题栏位置
            int x = widget->width() * ((qreal)m_leftPressMousePos.x() / (qreal)oldWidth);
            int y = widget->height() * ((qreal)m_leftPressMousePos.y() / (qreal)oldHeight);
            if (bInTitleWidget) {
                // TODO: 待优化（不能超出标题栏，也不能在按钮上）
            }
            widget->setGeometry(
                gpos.x() - x,
                gpos.y() - y,
                widget->width(), widget->height());
            m_leftPressMousePos = QPoint(x, y);
        } else {
            // 移动时保证鼠标在窗口同一个位置
            widget->setGeometry(
                gpos.x() - m_leftPressMousePos.x(),
                gpos.y() - m_leftPressMousePos.y(),
                widget->width(), widget->height());
        }
    } else if ((m_optState == ENothing
            && framelessWidget->isResizeable()
            && m_mouseBorderPos != 0)
            || m_optState == EResize) {
        // 拉升大小
        startResize(pos);
    }
}

void QhWidgetMoveResizePrivate::windowsNativeEventMove(void *message)
{
#ifdef Q_OS_WIN
    MSG* msg = reinterpret_cast<MSG*>(message);
    if (msg->message == WM_MOUSEMOVE) {
        POINT cursor {
            GET_X_LPARAM(msg->lParam),
            GET_Y_LPARAM(msg->lParam)
        };
        double dpr = framelessWidget->widget()->devicePixelRatioF();
        this->moveResize(QPoint(cursor.x / dpr, cursor.y / dpr));
    }
#endif
}

bool QhWidgetMoveResizePrivate::isInTitleBar(QPoint pos, bool *bInTitleWidget)
{
    if (bInTitleWidget)
        *bInTitleWidget = false;

    QWidget* child = nullptr;
    QRect rtContent;

    auto *titleBar = framelessWidget->titleBar();
    auto titleHeight = framelessWidget->titleHeight();
    auto shadowWidth = framelessWidget->shadowWidth();

    if (titleHeight <= 0 && !titleBar)
        return false;

    auto *widget = framelessWidget->widget();
    if (pos.isNull()) {
        QPoint globalPos = QCursor::pos();
        pos = widget->mapFromGlobal(globalPos);
    }

    // 高度判断
    if (framelessWidget->titleHeight() > 0) {
        int w = widget->width();
        rtContent = QRect(shadowWidth, shadowWidth,
                        w - shadowWidth * 2, titleHeight);
        if (rtContent.contains(pos)) {
            child = widget->childAt(pos);
            if (child && framelessWidget->titleBarDisableChilds().contains(child))
                return false;
            return true;
        }
    }

    // 标题栏判断
    if (titleBar) {
        if (titleBar == widget) {
            int w = widget->width();
            int h = widget->height();
            rtContent = QRect(shadowWidth, shadowWidth,
                w - shadowWidth * 2, h - shadowWidth * 2);
        } else {
            rtContent = titleBar->rect();
        }

        pos = titleBar->mapFromGlobal(pos);
        if (!rtContent.contains(pos))
            return false;

        child = titleBar->childAt(pos);
        if (child) {
            if (framelessWidget->titleBarEnableChilds().contains(child)) {
                if (bInTitleWidget)
                    *bInTitleWidget = true;
                return true;
            }
            return false;
        }
        if (bInTitleWidget)
            *bInTitleWidget = true;
        return true;
    }

    return false;
}

void QhWidgetMoveResizePrivate::updateWindowState()
{
    auto *widget = framelessWidget->widget();
    auto state = widget->windowState();
    if (framelessWidget->borderRadius() > 0
            && framelessWidget->shadowWidth() > 0) {
        if ((state & Qt::WindowMaximized) || (state & Qt::WindowFullScreen)) {
            widget->setContentsMargins(0, 0, 0, 0);
        } else {
            auto sw = framelessWidget->shadowWidth();
            widget->setContentsMargins(sw, sw, sw, sw);
            widget->adjustSize();
            widget->update();
        }
    }
}

void QhWidgetMoveResizePrivate::proccessWindowStateChange(QWindowStateChangeEvent *e)
{
    Q_UNUSED(e)

    updateWindowState();
}

void QhWidgetMoveResizePrivate::proccessMouseButtonPress(QMouseEvent *e)
{
    if (!framelessWidget->isResizeable()
            && !framelessWidget->isMoveable())
        return;

    if (e->button() == Qt::LeftButton) {
        m_bLeftPress = true;
        m_leftPressMousePos = e->pos();
        m_leftPressRect = framelessWidget->widget()->geometry();
        if (isEnableResize())
            resizePressPrepare(e->pos());
    }
}

void QhWidgetMoveResizePrivate::proccessMouseButtonRelease(QMouseEvent *e)
{
    if (!framelessWidget->isResizeable()
            && !framelessWidget->isMoveable())
        return;

    if (e->button() == Qt::LeftButton) {
        m_bLeftPress = false;
        m_optState = ENothing;
        stopResize();
        verifyResize(e->pos());
    }
}

void QhWidgetMoveResizePrivate::proccessMouseButtonRelease(QHoverEvent *e)
{
    Q_UNUSED(e)

    if (!framelessWidget->isResizeable()
            && !framelessWidget->isMoveable())
        return;

    m_bLeftPress = false;
    m_optState = ENothing;
    stopResize();
    verifyResize(e->pos());
}

void QhWidgetMoveResizePrivate::proccessMouseDoubleClicked()
{
    auto *widget = framelessWidget->widget();
    if (framelessWidget->isMaxNormalAtTitleBar() &&
            isInTitleBar(widget->mapToGlobal(m_leftPressMousePos))) {
        if (widget->isMaximized() && !widget->isFullScreen())
            widget->setWindowState(Qt::WindowNoState);
        else
            widget->setWindowState(Qt::WindowMaximized);
    }
}

void QhWidgetMoveResizePrivate::proccessWindowDeactivate()
{
    if (m_optState != ENothing)
        framelessWidget->widget()->setCursor(Qt::ArrowCursor);
    m_bLeftPress = false;
    m_optState = ENothing;
    stopResize();
}

void QhWidgetMoveResizePrivate::verifyResize(const QPoint &pos)
{
    if (!framelessWidget->isResizeable()
        || framelessWidget->widget()->isMaximized()
        || framelessWidget->widget()->isFullScreen()) {
        verifyResize(0);
        return;
    }

    // 鼠标所在窗口边框位置
    if (m_bLeftPress && isEnableResize())
        return;

    verifyResize(calcMousePos(framelessWidget->widget()->rect(), pos));
}

void QhWidgetMoveResizePrivate::verifyResize(long pos)
{
    auto cursorShape = [this]()
    {
        auto *widget = framelessWidget->widget();
        auto cursor = widget->cursor(); /*QApplication::overrideCursor()*/;
        // return cursor ? cursor->shape() : Qt::ArrowCursor;
        return cursor.shape();
    };

    if (m_optState == EResize)
        return;

    if (!framelessWidget->isResizeable()) {
        m_mouseBorderPos = 0;
        return;
    }

    m_mouseBorderPos = pos;
    auto *widget = framelessWidget->widget();
    switch (m_mouseBorderPos) {
    case HTLEFT:        // left border
    case HTRIGHT: {     // right border
        if (cursorShape() != Qt::SizeHorCursor)
            widget->setCursor(Qt::SizeHorCursor);
        break;
    }
    case HTBOTTOM:      // bottom border
    case HTTOP: {       // top border
        if (cursorShape() != Qt::SizeVerCursor)
            widget->setCursor(Qt::SizeVerCursor);
        break;
    }
    case HTBOTTOMLEFT:      // bottom left corner
    case HTTOPRIGHT: {      // top right corner
        if (cursorShape() != Qt::SizeBDiagCursor)
            widget->setCursor(Qt::SizeBDiagCursor);
        break;
    }
    case HTBOTTOMRIGHT:     // bottom right corner
    case HTTOPLEFT: {       // top left corner
        if (cursorShape() != Qt::SizeFDiagCursor)
            widget->setCursor(Qt::SizeFDiagCursor);
        break;
    }
    default: {
        widget->setCursor(Qt::ArrowCursor);
        break;
    }
    }
}

long QhWidgetMoveResizePrivate::calcMousePos(const QRect &rect, const QPoint &pos)
{
    long result = 0;

    long x = pos.x();
    long y = pos.y();

    auto nAreaWidth = framelessWidget->shadowWidth() + 6;
    auto *widget = framelessWidget->widget();
    bool resizeWidth = widget->minimumWidth() != widget->maximumWidth();
    bool resizeHeight = widget->minimumHeight() != widget->maximumHeight();

    if (resizeWidth) {
        //left border
        if (x >= rect.left() && x < rect.left() + nAreaWidth)
            result = HTLEFT;
        //right border
        if (x < rect.right() && x >= rect.right() - nAreaWidth) {
            result = HTRIGHT;
        }
    }
    if (resizeHeight) {
        //bottom border
        if (y < rect.bottom() && y >= rect.bottom() - nAreaWidth)
            result = HTBOTTOM;
        //top border
        if (y >= rect.top() && y < rect.top() + nAreaWidth)
            result = HTTOP;
    }
    if (resizeWidth && resizeHeight) {
        //bottom left corner
        if (x >= rect.left() && x < rect.left() + nAreaWidth &&
            y < rect.bottom() && y >= rect.bottom() - nAreaWidth)
            result = HTBOTTOMLEFT;
        //bottom right corner
        if (x < rect.right() && x >= rect.right() - nAreaWidth &&
            y < rect.bottom() && y >= rect.bottom() - nAreaWidth)
            result = HTBOTTOMRIGHT;
        //top left corner
        if (x >= rect.left() && x < rect.left() + nAreaWidth &&
            y >= rect.top() && y < rect.top() + nAreaWidth)
            result = HTTOPLEFT;
        //top right corner
        if (x < rect.right() && x >= rect.right() - nAreaWidth &&
            y >= rect.top() && y < rect.top() + nAreaWidth)
            result = HTTOPRIGHT;
    }
    return result;
}

bool QhWidgetMoveResizePrivate::isEnableResize()
{
    return framelessWidget->isResizeable()
            && !framelessWidget->widget()->isMaximized()
            && !framelessWidget->widget()->isFullScreen();
}

void QhWidgetMoveResizePrivate::resizePressPrepare(const QPoint &pos)
{
    int w = framelessWidget->widget()->width();
    int h = framelessWidget->widget()->height();

    m_pressVerBorderTopSpace = pos.y();
    m_pressVerBorderBottomSpace = h - pos.y();
    m_pressHorBorderLeftSpace =  pos.x();
    m_pressHorBorderRightSpace = w - pos.x();
}

void QhWidgetMoveResizePrivate::startResize(const QPoint &pos)
{
    auto funcDoResize = [this](long npos, const QPoint &pos)
    {
        auto sw = framelessWidget->shadowWidth();
        auto *widget = framelessWidget->widget();
        int w = widget->width();
        int h = widget->height();

        QRect winrect = QRect(sw, sw, w - sw * 2, h - sw * 2);
        long newpos = calcMousePos(winrect, pos);
        auto gpos = widget->mapToGlobal(pos);

        switch (npos) {
        case HTLEFT: {      // left border
            if (m_bResizeHPause && (newpos != HTLEFT && pos.x() > winrect.left()))
                break;
            m_bResizeHPause = false;

            QRect newRt = m_leftPressRect;
            newRt.setLeft(gpos.x() - m_pressHorBorderLeftSpace);
            if (newRt.width() < widget->minimumWidth()) {
                newRt.setLeft(newRt.left() - (widget->minimumWidth() - newRt.width()));
                m_bResizeHPause = true;
            }
            widget->setGeometry(newRt);
            m_leftPressRect = widget->geometry();
            break;
        }
        case HTRIGHT: {     // right area
            if (m_bResizeHPause && (newpos != HTRIGHT && pos.x() < winrect.right()))
                break;
            m_bResizeHPause = false;

            QRect newRt = m_leftPressRect;
            newRt.setRight(gpos.x() + m_pressHorBorderRightSpace);
            widget->setGeometry(newRt);
            if (widget->width() != newRt.width()) {
                m_bResizeHPause = true;
            }
            m_leftPressRect = widget->geometry();
            break;
        }
        case HTBOTTOM: {    // bottom border
            if (m_bResizeVPause && (newpos != HTBOTTOM && pos.y() < winrect.bottom()))
                break;
            m_bResizeVPause = false;

            QRect newRt = m_leftPressRect;
            newRt.setBottom(gpos.y() + m_pressVerBorderBottomSpace);
            widget->setGeometry(newRt);
            if (widget->height() != newRt.height()) {
                m_bResizeVPause = true;
            }
            m_leftPressRect = widget->geometry();
            break;
        }
        case HTTOP: {       // top border
            if (m_bResizeVPause && (newpos != HTTOP && pos.y() > winrect.top()))
                break;
            m_bResizeVPause = false;

            QRect newRt = m_leftPressRect;
            newRt.setTop(gpos.y() - m_pressVerBorderTopSpace);
            if (newRt.height() < widget->minimumHeight()) {
                newRt.setTop(newRt.top() - (widget->minimumHeight() - newRt.height()));
                m_bResizeVPause = true;
            }
            widget->setGeometry(newRt);
            m_leftPressRect = widget->geometry();
            break;
        }
        default:
            break;
        }
    };

    if (!isEnableResize() || !m_bLeftPress)
        return;

    m_optState = EResize;

    switch (m_mouseBorderPos) {
    case HTLEFT: {      // left border
        funcDoResize(HTLEFT, pos);
        break;
    }
    case HTRIGHT: {     // right area
        funcDoResize(HTRIGHT, pos);
        break;
    }
    case HTBOTTOM: {    // bottom border
        funcDoResize(HTBOTTOM, pos);
        break;
    }
    case HTTOP: {       // top border
        funcDoResize(HTTOP, pos);
        break;
    }
    case HTBOTTOMLEFT: {    // bottom left corner
        funcDoResize(HTLEFT, pos);
        funcDoResize(HTBOTTOM, pos);
        break;
    }
    case HTTOPRIGHT: {      // top right corner
        funcDoResize(HTRIGHT, pos);
        funcDoResize(HTTOP, pos);
        break;
    }
    case HTBOTTOMRIGHT: {   // bottom right corner
        funcDoResize(HTRIGHT, pos);
        funcDoResize(HTBOTTOM, pos);
        break;
    }
    case HTTOPLEFT: {       // top left corner
        funcDoResize(HTLEFT, pos);
        funcDoResize(HTTOP, pos);
        break;
    }
    }
}

void QhWidgetMoveResizePrivate::stopResize()
{
    m_optState = ENothing;
    m_bResizeVPause = false;
    m_bResizeHPause = false;
    m_pressVerBorderTopSpace = 0;
    m_pressVerBorderBottomSpace = 0;
    m_pressHorBorderLeftSpace = 0;
    m_pressHorBorderRightSpace = 0;
}
