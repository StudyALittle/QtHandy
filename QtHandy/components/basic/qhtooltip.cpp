#include "qhtooltip.h"
#include "qhtooltip_p.h"
#include <QApplication>
#include <QMouseEvent>

QhToolTip *QhToolTipPrivate::s_toolTip = nullptr;

QhToolTip::QhToolTip(QWidget *parent) : QWidget(parent), d(new QhToolTipPrivate(this))
{
    if (QhToolTipPrivate::s_toolTip)
        delete QhToolTipPrivate::s_toolTip;
    QhToolTipPrivate::s_toolTip = this;

    setMouseTracking(true);
    d->init();
}

QhToolTip::~QhToolTip()
{
    QhToolTipPrivate::s_toolTip = nullptr;
}

void QhToolTip::showText(QWidget *w, Placement placement, const QString &text, const QRect &rect, int msecDisplayTime)
{
    QhToolTipPrivate::showText(w, QPoint(), placement, rect, text, msecDisplayTime);
}

void QhToolTip::showText(const QPoint &pos, const QString &text, const QRect &rect, int msecDisplayTime)
{
    QhToolTipPrivate::showText(nullptr, pos, Bottom, rect, text, msecDisplayTime);
}

void QhToolTip::hideText()
{
}

QString QhToolTip::text()
{
    if (QhToolTipPrivate::s_toolTip)
        return QhToolTipPrivate::s_toolTip->d->showInfo.text;
    return QString();
}

void QhToolTip::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
}

void QhToolTip::mouseMoveEvent(QMouseEvent *e)
{
    if (!d->showInfo.rect.isNull()) {
        QPoint pos = e->globalPos();
        if (d->showInfo.w)
            pos = d->showInfo.w->mapFromGlobal(pos);
        if (!d->showInfo.rect.contains(pos))
            d->hideTip();
    }
    QWidget::mouseMoveEvent(e);
}

void QhToolTip::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
}

QhToolTipPrivate::QhToolTipPrivate(QhToolTip *toolTip) : toolTip(toolTip)
{
}

QhToolTipPrivate::~QhToolTipPrivate()
{
}

void QhToolTipPrivate::init()
{
    qApp->installEventFilter(this);
}

void QhToolTipPrivate::showText(QWidget *w, const QPoint &pos, QhToolTip::Placement placement, const QRect &rect,
    const QString &text, int msecDisplayTime)
{
}

void QhToolTipPrivate::hideTip()
{
    if (!hideTimer.isActive())
        hideTimer.start(300, this);
}

void QhToolTipPrivate::hideTipImmediately()
{
    toolTip->close(); // to trigger QEvent::Close which stops the animation
    toolTip->deleteLater();
}

void QhToolTipPrivate::restartExpireTimer(int msecDisplayTime)
{
    int time = 10000 + 40 * qMax(0, showInfo.text.length() - 100);
    if (msecDisplayTime > 0)
        time = msecDisplayTime;
    expireTimer.start(time, this);
    hideTimer.stop();
}

void QhToolTipPrivate::timerEvent(QTimerEvent *e)
{
    if (e->timerId() == hideTimer.timerId() || e->timerId() == expireTimer.timerId()) {
        hideTimer.stop();
        expireTimer.stop();
#if 0 /* Used to be included in Qt4 for Q_WS_MAC */ && QT_CONFIG(effects)
        if (QApplication::isEffectEnabled(Qt::UI_FadeTooltip)){
            // Fade out tip on mac (makes it invisible).
            // The tip will not be deleted until a new tip is shown.

                        // DRSWAT - Cocoa
                        macWindowFade(qt_mac_window_for(this));
            QTipLabel::instance->fadingOut = true; // will never be false again.
        }
        else
            hideTipImmediately();
#else
        hideTipImmediately();
#endif
    }
}

bool QhToolTipPrivate::eventFilter(QObject *o, QEvent *e)
{
    switch (e->type()) {
#ifdef Q_OS_MACOS
    case QEvent::KeyPress:
    case QEvent::KeyRelease: {
        const int key = static_cast<QKeyEvent *>(e)->key();
        // Anything except key modifiers or caps-lock, etc.
        if (key < Qt::Key_Shift || key > Qt::Key_ScrollLock)
            hideTipImmediately();
        break;
    }
#endif
    case QEvent::Leave:
        hideTip();
        break;

#if defined(Q_OS_QNX) // On QNX the window activate and focus events are delayed and will appear \
    // after the window is shown.
    case QEvent::WindowActivate:
    case QEvent::FocusIn:
        return false;
    case QEvent::WindowDeactivate:
        if (o != this)
            return false;
        hideTipImmediately();
        break;
    case QEvent::FocusOut:
        if (reinterpret_cast<QWindow *>(o) != windowHandle())
            return false;
        hideTipImmediately();
        break;
#else
    case QEvent::WindowActivate:
    case QEvent::WindowDeactivate:
    case QEvent::FocusIn:
    case QEvent::FocusOut:
#endif
    case QEvent::Close: // For QTBUG-55523 (QQC) specifically: Hide tooltip when windows are closed
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseButtonDblClick:
    case QEvent::Wheel:
        hideTipImmediately();
        break;

    case QEvent::MouseMove:
        if (o == showInfo.w && !showInfo.rect.isNull() && !showInfo.rect.contains(static_cast<QMouseEvent *>(e)->pos()))
            hideTip();
    default:
        break;
    }
    return false;
}

void QhToolTipPrivate::ShowInfo::clear()
{
    w = nullptr;
    pos = QPoint();
    rect = QRect();
    placement = QhToolTip::Bottom;
    text.clear();
    msecDisplayTime = 0;
}
