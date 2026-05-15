#include "qhframelesswindow_p.h"
#ifdef Q_OS_LINUX
#include <QDebug>
#include <QCoreApplication>
#include <QAbstractNativeEventFilter>
#include <QX11Info>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/extensions/shape.h>
// #include <X11/extensions/XInput2.h>
#include <xcb/xcb.h>
#include <xcb/xcbext.h>
#include <X11/X.h>
#include "xinput.h"

/// sudo apt-get install libxcb-xinput-dev

#ifndef _NET_WM_MOVERESIZE_SIZE_TOPLEFT
#define _NET_WM_MOVERESIZE_SIZE_TOPLEFT 0
#endif
#ifndef _NET_WM_MOVERESIZE_SIZE_TOP
#define _NET_WM_MOVERESIZE_SIZE_TOP 1
#endif
#ifndef _NET_WM_MOVERESIZE_SIZE_TOPRIGHT
#define _NET_WM_MOVERESIZE_SIZE_TOPRIGHT 2
#endif
#ifndef _NET_WM_MOVERESIZE_SIZE_RIGHT
#define _NET_WM_MOVERESIZE_SIZE_RIGHT 3
#endif
#ifndef _NET_WM_MOVERESIZE_SIZE_BOTTOMRIGHT
#define _NET_WM_MOVERESIZE_SIZE_BOTTOMRIGHT 4
#endif
#ifndef _NET_WM_MOVERESIZE_SIZE_BOTTOM
#define _NET_WM_MOVERESIZE_SIZE_BOTTOM 5
#endif
#ifndef _NET_WM_MOVERESIZE_SIZE_BOTTOMLEFT
#define _NET_WM_MOVERESIZE_SIZE_BOTTOMLEFT 6
#endif
#ifndef _NET_WM_MOVERESIZE_SIZE_LEFT
#define _NET_WM_MOVERESIZE_SIZE_LEFT 7
#endif
#ifndef _NET_WM_MOVERESIZE_MOVE
#define _NET_WM_MOVERESIZE_MOVE 8 /* movement only */
#endif
#ifndef _NET_WM_MOVERESIZE_SIZE_KEYBOARD
#define _NET_WM_MOVERESIZE_SIZE_KEYBOARD 9 /* size via keyboard */
#endif
#ifndef _NET_WM_MOVERESIZE_MOVE_KEYBOARD
#define _NET_WM_MOVERESIZE_MOVE_KEYBOARD 10 /* move via keyboard */
#endif
#ifndef _NET_WM_MOVERESIZE_CANCEL
#define _NET_WM_MOVERESIZE_CANCEL 11 /* cancel operation */
#endif

class X11MoveResizePrivate : public QAbstractNativeEventFilter
{
public:
    X11MoveResizePrivate(QhFramelessWindow *fWindow);

    void initXInput2(Display *display);

    /// @brief xcb display
    static Display *xDisplay();

    /// @brief xcb_connection_t
    static xcb_connection_t *xConnect();

    /// @brief to Qt Left and Right button
    static Qt::MouseButton toQtMouseBtn(int btn);
    static int toXMouseBtn(Qt::MouseButton btn);

    bool enableXInput2(int opCode) const;

    /// @brief xcb移动
    void xSendMove(QWidget *widget, Qt::MouseButton qbutton, int flag);

    /// @brief xcb按钮释放
    void xSendButtonRelease(QWidget *widget, const QPoint &pos, const QPoint &globalPos);

    /// @brief 判断窗口是否是最大化
    static bool xIsMaximized(Display *display, Window window);

    void mouseMove(int gx, int gy);
    void mousePress(int btn);
    void mouseRelease(int btn, const QPoint &pos = QPoint(), const QPoint &globalPos = QPoint());

    bool isMoveing() const;
    bool nativeEventFilter(const QByteArray &eventType, void *message, NATIVATEEVENTFUNC_3PARAM_TYPE *result) override;

private:
    enum State { StateNothing = 0, StatePreMove, StateMoveing, StatePreResize, StateResizeing };

    QhFramelessWindow *m_fWindow = nullptr;

    State m_state = StateNothing;
    int m_flag = -1;
    bool m_bLeftPress = false;

    bool m_xi2Enabled = false;
    uint8_t m_xiOpcode = 0;
    uint8_t m_xiFirstEvent = 0;
};

X11MoveResizePrivate::X11MoveResizePrivate(QhFramelessWindow *fWindow) :
    QAbstractNativeEventFilter(), m_fWindow(fWindow)
{
    if (!qEnvironmentVariableIsSet("QT_XCB_NO_XI2"))
        initXInput2(xDisplay());
}

void X11MoveResizePrivate::initXInput2(Display *display)
{
    int opcode, event, error;
    if (!XQueryExtension(display, "XInputExtension", &opcode, &event, &error)) {
        qWarning() << "XQueryExtension error: " << error;
        return;
    }

    //    int major = 0, minor = 0;
    //    int ret = XIQueryVersion(display, &major, &minor);
    //    if (ret != Success || major < 2) {
    //        qWarning() << "X server does not support XInput 2: " << ret;
    //        return;
    //    }
    //    qInfo() << QString("Using XInput version %1.%2").arg(major, minor);

    m_xi2Enabled = true;
    m_xiOpcode = opcode;
    m_xiFirstEvent = event;
}

Display *X11MoveResizePrivate::xDisplay()
{
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    if (auto *x11Application = qGuiApp->nativeInterface<QNativeInterface::QX11Application>()) {
        return x11Application->display();
        return nullptr;
#else
    return QX11Info::display();
#endif
    }

    xcb_connection_t *X11MoveResizePrivate::xConnect()
    {
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
        if (auto *x11Application = qGuiApp->nativeInterface<QNativeInterface::QX11Application>()) {
            return x11Application->connection();
            return nullptr;
#else
    return QX11Info::connection();
#endif
        }

        Qt::MouseButton X11MoveResizePrivate::toQtMouseBtn(int btn)
        {
            switch (btn) {
            case Button1:
                return Qt::LeftButton;
            case Button3:
                return Qt::RightButton;
            default:
                break;
            }
            return Qt::AllButtons;
        }

        int X11MoveResizePrivate::toXMouseBtn(Qt::MouseButton btn)
        {
            switch (btn) {
            case Qt::LeftButton: {
                return Button1;
            }
            case Qt::RightButton: {
                return Button3;
            }
            default:
                return AnyButton;
            }
        }

        bool X11MoveResizePrivate::enableXInput2(int opCode) const
        {
            return m_xi2Enabled && m_xiOpcode == opCode;
        }

        void X11MoveResizePrivate::xSendMove(QWidget * widget, Qt::MouseButton qbutton, int flag)
        {
            Display *display = xDisplay();
            int xbtn = toXMouseBtn(qbutton);

            // 解决电脑屏幕缩放后，拖动窗口问题
            qreal screenRadio = widget->devicePixelRatioF(); // QGuiApplication::primaryScreen()->devicePixelRatio();

            XEvent xev;
            memset(&xev, 0, sizeof(xev));
            const Atom net_move_resize = XInternAtom(display, "_NET_WM_MOVERESIZE", false);
            xev.xclient.type = ClientMessage;
            xev.xclient.message_type = net_move_resize;
            xev.xclient.display = display;
            xev.xclient.window = widget->winId();
            xev.xclient.format = 32;

            const auto global_position = QCursor::pos();
            xev.xclient.data.l[0] = global_position.x() * screenRadio;
            xev.xclient.data.l[1] = global_position.y() * screenRadio;
            xev.xclient.data.l[2] = flag;
            xev.xclient.data.l[3] = xbtn;
            xev.xclient.data.l[4] = 0;

            XUngrabPointer(display, CurrentTime);
            // m_fWindow->widget()->grabMouse();
            // m_fWindow->widget()->releaseMouse();

            // Get the root window for the current display.
            Window winRoot = XDefaultRootWindow(display);
            XSendEvent(display, winRoot, false, SubstructureRedirectMask | SubstructureNotifyMask, &xev);
            XFlush(display);
        }

        void X11MoveResizePrivate::xSendButtonRelease(QWidget * widget, const QPoint &pos, const QPoint &globalPos)
        {
            Display *display = xDisplay();

            XEvent xevent;
            memset(&xevent, 0, sizeof(XEvent));

            xevent.type = ButtonRelease;
            xevent.xbutton.button = Button1;
            xevent.xbutton.window = widget->effectiveWinId();
            xevent.xbutton.x = pos.x();
            xevent.xbutton.y = pos.y();
            xevent.xbutton.x_root = globalPos.x();
            xevent.xbutton.y_root = globalPos.y();
            xevent.xbutton.display = display;

            XSendEvent(display, widget->effectiveWinId(), False, ButtonReleaseMask, &xevent);
            XFlush(display);
        }

        bool X11MoveResizePrivate::xIsMaximized(Display * display, Window window)
        {
            static Atom _NET_WM_STATE = XInternAtom(display, "_NET_WM_STATE", false);
            static Atom _NET_WM_STATE_MAXIMIZED = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", false);
            Atom actual_type;
            int actual_format;
            unsigned long i, num_items, bytes_after;
            Atom *atoms = nullptr;
            XGetWindowProperty(display, window, _NET_WM_STATE, 0, 1024, False, XA_ATOM, &actual_type, &actual_format,
                &num_items, &bytes_after, (unsigned char **)&atoms);
            for (i = 0; i < num_items; ++i) {
                if (atoms[i] == _NET_WM_STATE_MAXIMIZED) {
                    XFree(atoms);
                    return true;
                }
            }
            if (atoms)
                XFree(atoms);
            return false;
        }

        void X11MoveResizePrivate::mouseMove(int gx, int gy)
        {
            Q_UNUSED(gx)
            Q_UNUSED(gy)

            auto fwidget = m_fWindow->widget();
            if (fwidget->isMaximized() || fwidget->isFullScreen())
                return;

            QPoint pos = fwidget->mapFromGlobal(QCursor::pos());

            int flag = _NET_WM_MOVERESIZE_MOVE;
            if (m_state == StateNothing) {
                if (m_fWindow->isResizeable()) {
                    long result = m_fWindow->d->moveResizeHelpre->calcMousePos(fwidget->rect(), pos);
                    if (result == 1) {
                        flag = _NET_WM_MOVERESIZE_SIZE_LEFT;
                        fwidget->setCursor(Qt::SizeHorCursor);
                    } else if (result == 2) {
                        flag = _NET_WM_MOVERESIZE_SIZE_RIGHT;
                        fwidget->setCursor(Qt::SizeHorCursor);
                    } else if (result == 3) {
                        flag = _NET_WM_MOVERESIZE_SIZE_BOTTOM;
                        fwidget->setCursor(Qt::SizeVerCursor);
                    } else if (result == 4) {
                        flag = _NET_WM_MOVERESIZE_SIZE_TOP;
                        fwidget->setCursor(Qt::SizeVerCursor);
                    } else if (result == 5) {
                        flag = _NET_WM_MOVERESIZE_SIZE_BOTTOMLEFT;
                        fwidget->setCursor(Qt::SizeBDiagCursor);
                    } else if (result == 6) {
                        flag = _NET_WM_MOVERESIZE_SIZE_TOPRIGHT;
                        fwidget->setCursor(Qt::SizeBDiagCursor);
                    } else if (result == 7) {
                        flag = _NET_WM_MOVERESIZE_SIZE_BOTTOMRIGHT;
                        fwidget->setCursor(Qt::SizeFDiagCursor);
                    } else if (result == 8) {
                        flag = _NET_WM_MOVERESIZE_SIZE_TOPLEFT;
                        fwidget->setCursor(Qt::SizeFDiagCursor);
                    } else {
                        fwidget->setCursor(Qt::ArrowCursor);
                    }
                }
                m_flag = flag;
            }

            if (!m_bLeftPress)
                return;

            if (m_state == StateMoveing || m_state == StateResizeing) {
                xSendMove(fwidget, Qt::LeftButton, m_flag);
                return;
            }

            if (m_state == StatePreMove && m_fWindow->isMoveable()) {
                m_state = StateMoveing;
                xSendMove(fwidget, Qt::LeftButton, m_flag);
            } else if (m_state == StatePreResize && m_fWindow->isResizeable()) {
                m_state = StateResizeing;
                xSendMove(fwidget, Qt::LeftButton, m_flag);
            }
        }

        void X11MoveResizePrivate::mousePress(int btn)
        {
            if (toQtMouseBtn(btn) != Qt::LeftButton)
                return;

            m_bLeftPress = true;
            if (m_state == StateNothing) {
                QPoint pos = m_fWindow->widget()->mapFromGlobal(QCursor::pos());
                bool bTitleBar = m_fWindow->d->moveResizeHelpre->isInTitleBar(QCursor::pos());
                long result = m_fWindow->d->moveResizeHelpre->calcMousePos(m_fWindow->widget()->rect(), pos);
                if (result == 0 && bTitleBar) {
                    m_state = StatePreMove;
                } else if (result != 0) {
                    m_state = StatePreResize;
                }
            }
        }

        void X11MoveResizePrivate::mouseRelease(int btn, const QPoint &pos, const QPoint &globalPos)
        {
            if (toQtMouseBtn(btn) != Qt::LeftButton)
                return;

            if (m_state == StateMoveing) {
                xSendButtonRelease(m_fWindow->widget(), pos, globalPos);
                m_fWindow->widget()->setCursor(Qt::ArrowCursor);
            }

            m_state = StateNothing;
            m_flag = -1;
            m_bLeftPress = false;
        }

        bool X11MoveResizePrivate::isMoveing() const
        {
            return m_state == StateMoveing;
        }

        bool X11MoveResizePrivate::nativeEventFilter(
            const QByteArray &eventType, void *message, NATIVATEEVENTFUNC_3PARAM_TYPE *result)
        {
            Q_UNUSED(result)

            auto framelessWidget = m_fWindow->widget();

            Display *display = this->xDisplay();
            if (!message || !display || !framelessWidget)
                return false;

            if (eventType != "xcb_generic_event_t")
                return false;

            xcb_generic_event_t *ev = static_cast<xcb_generic_event_t *>(message);

            // static int ss = 0;
            // qDebug() << "Main type: " << (ev->response_type & ~0x80) << " -- " << ++ss;

            switch (ev->response_type & ~0x80) {
            case XCB_PROPERTY_NOTIFY: {
                break;
            }
            case XCB_MOTION_NOTIFY: { // 鼠标移动事件
                xcb_motion_notify_event_t *mouseev = static_cast<xcb_motion_notify_event_t *>(message);
                this->mouseMove(mouseev->root_x, mouseev->root_y);
                break;
            }
            case XCB_BUTTON_PRESS: { // 鼠标点击事件
                xcb_button_press_event_t *btnev = static_cast<xcb_button_press_event_t *>(message);
                this->mousePress(btnev->detail);
                break;
            }
            case XCB_BUTTON_RELEASE: { // 鼠标释放事件
                xcb_button_release_event_t *btnev = static_cast<xcb_button_release_event_t *>(message);
                this->mouseRelease(
                    btnev->detail, QPoint(btnev->event_x, btnev->event_y), QPoint(btnev->root_x, btnev->root_y));
                break;
            }
            case XCB_GE_GENERIC: {
                xcb_ge_generic_event_t *genev = static_cast<xcb_ge_generic_event_t *>(message);
                if (!this->enableXInput2(genev->extension))
                    break;

                switch (genev->event_type) {
                case XCB_INPUT_MOTION: { //
                    xcb_input_motion_event_t *ximouseev = static_cast<xcb_input_motion_event_t *>(message);
                    this->mouseMove(ximouseev->event_x, ximouseev->event_y);
                    break;
                }
                case XCB_INPUT_BUTTON_PRESS: { //
                    xcb_input_button_press_event_t *xibtnev = static_cast<xcb_input_button_press_event_t *>(message);
                    this->mousePress(xibtnev->detail);
                    break;
                }
                case XCB_INPUT_BUTTON_RELEASE: { //
                    xcb_input_button_release_event_t *xibtnev =
                        static_cast<xcb_input_button_release_event_t *>(message);
                    this->mouseRelease(xibtnev->detail);
                    break;
                }
                default:
                    break;
                }
                break;
            }
            case 85: { // xcb拓展事件，目前未查询具体属于哪个拓展 XCB_RECORD?
                // move, enable recv BUTTON_RELEASE event
                if (this->isMoveing() || m_state == StateResizeing)
                    this->mouseRelease(Button1);
                break;
            }
            default:
                break;
            }

            return false;
        }

        QhFramelessWindowPrivate::QhFramelessWindowPrivate(QhFramelessWindow * q, QWidget * widget) :
            q_ptr(q), widget(widget), moveResizeHelpre(new QhWidgetMoveResize(q))
        {
            m_pX11 = new X11MoveResizePrivate(q);
            qApp->installNativeEventFilter(m_pX11);
        }

        QhFramelessWindowPrivate::~QhFramelessWindowPrivate()
        {
            if (m_pX11) {
                delete m_pX11;
                m_pX11 = nullptr;
            }
        }

        bool QhFramelessWindowPrivate::nativeEventEx(
            const QByteArray &eventType, void *message, NATIVATEEVENTFUNC_3PARAM_TYPE *result)
        {
            return m_pX11->nativeEventFilter(eventType, message, result);
        }
#endif
