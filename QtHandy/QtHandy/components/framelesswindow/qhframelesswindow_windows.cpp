#include "qhframelesswindow_p.h"
#ifdef Q_OS_WIN
#include <QApplication>
#include <QMouseEvent>
#include <QDebug>
#include <windows.h>
#include <WinUser.h>
#include <windowsx.h>
#include <dwmapi.h>
#include <objidl.h>
#include <gdiplus.h>
#include "qhwidgetmoveresize.h"

#pragma comment(lib, "Dwmapi.lib")
#pragma comment(lib, "user32.lib")

QhFramelessWindowPrivate::QhFramelessWindowPrivate(QhFramelessWindow *q, QWidget *widget) :
    q_ptr(q), widget(widget), moveResizeHelpre(new QhWidgetMoveResize(q))
{
}
QhFramelessWindowPrivate::~QhFramelessWindowPrivate()
{
}

bool QhFramelessWindowPrivate::nativeEventEx(
    const QByteArray &eventType, void *message, NATIVATEEVENTFUNC_3PARAM_TYPE *result)
{
    Q_UNUSED(eventType)

    if (this->borderRadius > 0) {
        moveResizeHelpre->windowsNativeEventMove(message);
        return false;
    }

    auto composition_enabled = []() -> bool {
        BOOL composition_enabled = FALSE;
        bool success = ::DwmIsCompositionEnabled(&composition_enabled) == S_OK;
        return composition_enabled && success;
    };

    MSG *msg = reinterpret_cast<MSG *>(message);
    switch (msg->message) {
    case WM_NCACTIVATE: {
        if (!composition_enabled()) {
            *result = TRUE;
            return true;
        }
        break;
    }
    case WM_NCCALCSIZE: {
        if (this->shadowWidth <= 0) {
            NCCALCSIZE_PARAMS &params = *reinterpret_cast<NCCALCSIZE_PARAMS *>(msg->lParam);
            bool bMax = ::IsZoomed(msg->hwnd);
            if (bMax) {
                // 修正最大化时内容超出屏幕问题
                auto monitor = MonitorFromWindow(msg->hwnd, MONITOR_DEFAULTTONEAREST);
                MONITORINFO info;
                info.cbSize = sizeof(MONITORINFO);
                if (GetMonitorInfo(monitor, &info)) {
                    const auto workRect = info.rcWork;
                    params.rgrc[0].left = qMax(params.rgrc[0].left, long(workRect.left));
                    params.rgrc[0].top = qMax(params.rgrc[0].top, long(workRect.top));
                    params.rgrc[0].right = qMin(params.rgrc[0].right, long(workRect.right));
                    params.rgrc[0].bottom = qMin(params.rgrc[0].bottom, long(workRect.bottom));
                }
            } else {
                // sz->rgrc[0] 的值必须跟原来的不同, 否则拉伸左/上边框缩放窗口时,
                // 会导致右/下侧出现空白区域 (绘制抖动)
                // 窗口下边框失去1像素对视觉影响最小, 因此底部减少1像素
                params.rgrc[0].bottom += 1;
            }
        }

        *result = WVR_REDRAW;
        return true;
    }
    case WM_NCLBUTTONDBLCLK:
    case WM_LBUTTONDBLCLK: { // 双击事件
        POINT cursor{GET_X_LPARAM(msg->lParam), GET_Y_LPARAM(msg->lParam)};

        // support highdpi
        double dpr = widget->devicePixelRatioF();
        if (moveResizeHelpre->isInTitleBar(QPoint(cursor.x / dpr, cursor.y / dpr))) {
            if (this->bMaxNormalAtTitleBar) {
                if (widget->isMaximized())
                    widget->showNormal();
                else
                    widget->showMaximized();
                widget->update();
            }
            return true;
        }
        break;
    }
    case WM_NCHITTEST: { // 拖动缩放事件
        *result = 0;

        if (this->bResizeable) {
            RECT winrect;
            HWND hwhd = HWND(widget->winId());
            ::GetWindowRect(hwhd, &winrect);

            long x = GET_X_LPARAM(msg->lParam);
            long y = GET_Y_LPARAM(msg->lParam);

            *result = moveResizeHelpre->calcMousePos(
                QRect(winrect.left + shadowWidth, winrect.top + shadowWidth,
                    winrect.right - winrect.left - shadowWidth * 2, winrect.bottom - winrect.top - shadowWidth * 2),
                QPoint(x, y));
        }

        // 大小拉升大小事件
        if (0 != *result) {
            return true;
        }

        // 拖动窗口
        if (!bMoveable || (!titleBar && titleHeight <= 0))
            break;

        POINT cursor{GET_X_LPARAM(msg->lParam), GET_Y_LPARAM(msg->lParam)};

        // support highdpi
        double dpr = widget->devicePixelRatioF();
        if (moveResizeHelpre->isInTitleBar(QPoint(cursor.x / dpr, cursor.y / dpr))) {
            *result = HTCAPTION;
            return true;
        }
        break;
    }
    case WM_GETMINMAXINFO: { // 最大化事件
        // bool bMin = ::IsIconic(msg->hwnd);
        // bool bMax = ::IsZoomed(msg->hwnd);
        break;
    }
    case WM_PAINT: {
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
        /// Qt6.5.3无边框最大化存在问题,
        /// 界面会超出屏幕大小，通过布局器修正最大化时的问题
        /// Qt5.12版本目前不存在此问题，不清楚其它Qt6版本是否会存在此问题
        // bool bMax = ::IsZoomed(msg->hwnd);
        // reviseRestoreMax(bMax);
#endif
        break;
    }
    default:
        break;
    }
    return false;
}

#endif
