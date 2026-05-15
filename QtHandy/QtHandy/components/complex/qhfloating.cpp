#include "qhfloating.h"
#include "qhfloating_p.h"
#include <QEvent>
#include <QResizeEvent>
#include <QGuiApplication>
#include <QGraphicsDropShadowEffect>
#include "qhwidgetutil.h"

QhFloating::QhFloating(QWidget *parent):
    QhFramelessWidget(parent),
    d(new QhFloatingPrivate)
{
    if (!parent) {
        this->setWindowFlags(this->windowFlags()
            | Qt::WindowStaysOnTopHint | Qt::ToolTip);
    }
    this->setAttribute(Qt::WA_StyledBackground);
    // this->setAttribute(Qt::WA_DeleteOnClose);
    this->installEventFilter(this);
    qApp->installEventFilter(this);
}

QhFloating::QhFloating(bool bBase, QWidget *parent):
    QhFramelessWidget(parent),
    d(new QhFloatingPrivate)
{
    this->setAttribute(Qt::WA_StyledBackground);
}

QhFloating::~QhFloating()
{

}

bool QhFloating::isCloseAtFocusOut() const
{
    return d->bCloseAtFocusOut;
}

QVector<QWidget *> QhFloating::ignoreWidgets() const
{
    return d->ignoreWidgets;
}

void QhFloating::setCloseAtFocusOut(bool b)
{
    d->bCloseAtFocusOut = b;
}

void QhFloating::setIgnoreWidgets(const QVector<QWidget *> &ws)
{
    d->ignoreWidgets = ws;
    for (auto *w: ws) {
        w->installEventFilter(this);
    }
}

void QhFloating::open(const QPoint &pos)
{
    d->pos = pos;

    if (this->parentWidget()) {
        auto *shadowEffect = new QGraphicsDropShadowEffect;
        shadowEffect->setOffset(0, 0);
        shadowEffect->setColor(QColor(0x00, 0x00, 0x00, 0x88));
        shadowEffect->setBlurRadius(18);
        this->setGraphicsEffect(shadowEffect);
    } else {
        this->initFramelessWindow();
    }
    this->setFocus();
    this->activateWindow();
    // this->adjustSize();
    this->show();
}

void QhFloating::openShadowEffect()
{
    auto *shadowEffect = new QGraphicsDropShadowEffect;
    shadowEffect->setOffset(0, 0);
    shadowEffect->setColor(QColor(0x00, 0x00, 0x00, 0x88));
    shadowEffect->setBlurRadius(18);
    this->setGraphicsEffect(shadowEffect);
}

bool QhFloating::eventFilter(QObject *o, QEvent *e)
{
    switch (e->type()) {
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseButtonDblClick: {
        if (!d->bCloseAtFocusOut)
            break;

        if (!o->inherits("QWidget"))
            break;

        if (QhWidgetUtil::isParentWidget(this, static_cast<QWidget*>(o)))
            break;

        if (d->ignoreWidgets.contains(static_cast<QWidget*>(o)))
            break;

        bool bk = false;
        for (auto *iw: d->ignoreWidgets) {
            if (QhWidgetUtil::isParentWidget(iw, static_cast<QWidget*>(o))) {
                bk = true;
                break;
            }
        }
        if (bk)
            break;

        close();
        emit closed();
        break;
    }
    case QEvent::WindowDeactivate: {
        break;
    }
    case QEvent::ApplicationDeactivate:
    case QEvent::NonClientAreaMouseButtonPress: {
        if (!d->bCloseAtFocusOut)
            break;
        close();
        emit closed();
        break;
    }
    case QEvent::Resize:
    case QEvent::Show: {
        if (!d->pos.isNull())
            this->move(d->pos);
        break;
    }
    default:
        break;
    }
    return false;
}

QhFloatingPrivate::QhFloatingPrivate()
{

}

QhFloatingPrivate::~QhFloatingPrivate()
{

}
