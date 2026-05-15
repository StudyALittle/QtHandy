#ifndef QHWIDGETMOVERESIZE_P_H
#define QHWIDGETMOVERESIZE_P_H

#include <QObject>
#include <QEvent>
#include <QWidget>
#include <QWindowStateChangeEvent>
#include "qhframelesswindow.h"
#include "qhwidgetmoveresize.h"

class QhWidgetMoveResizePrivate
{
    Q_DISABLE_COPY(QhWidgetMoveResizePrivate)
    Q_DECLARE_PUBLIC(QhWidgetMoveResize)

public:
    QhWidgetMoveResizePrivate(
        QhWidgetMoveResize *q, QhFramelessWindow *fwidget):
        q_ptr(q), framelessWidget(fwidget) {}

    bool proccessEvent(QEvent *event);

    void moveResize(const QPoint &pos);
    void windowsNativeEventMove(void *message);

    bool isInTitleBar(QPoint pos, bool *bInTitleWidget = nullptr);

    long calcMousePos(const QRect &rect, const QPoint &pos);

protected:
    void updateWindowState();

    void proccessWindowStateChange(QWindowStateChangeEvent *e);
    void proccessMouseButtonPress(QMouseEvent *e);
    void proccessMouseButtonRelease(QMouseEvent *e);
    void proccessMouseButtonRelease(QHoverEvent *e);
    void proccessMouseDoubleClicked();
    void proccessWindowDeactivate();

    void verifyResize(const QPoint &pos);
    void verifyResize(long pos);

    bool isEnableResize();
    void resizePressPrepare(const QPoint &pos);
    void startResize(const QPoint &pos);
    void stopResize();

private:
    enum MouseState { ENothing, EMove, EResize };

    QhWidgetMoveResize *const q_ptr;
    QhFramelessWindow *framelessWidget = nullptr;

    // 鼠标左键是否按下
    bool m_bLeftPress = false;
    // 鼠标左键按下位置
    QPoint m_leftPressMousePos;
    QRect m_leftPressRect;
    // 鼠标在边框位置
    long m_mouseBorderPos = 0;

    bool m_bResizeHPause = false;
    bool m_bResizeVPause = false;
    int m_pressVerBorderTopSpace = 0;
    int m_pressVerBorderBottomSpace = 0;
    int m_pressHorBorderLeftSpace = 0;
    int m_pressHorBorderRightSpace = 0;

    MouseState m_optState = ENothing;
};

#endif // QHWIDGETMOVERESIZE_P_H
