#include "qhwidgetzoom.h"
#include "qhwidgetzoom_p.h"
#include <QLayout>
#include <QFormLayout>
#include <QScreen>
#include "qhwidgetutil.h"

QhWidgetZoom &QhWidgetZoom::instance()
{
    static QhWidgetZoom instance;
    return instance;
}

QhWidgetZoom::QhWidgetZoom():
    d(new QhWidgetZoomPrivate(this))
{

}

QhWidgetZoom::~QhWidgetZoom()
{

}

qreal QhWidgetZoom::defaultScreenZoom()
{
    return screenZoomUnderWidget(nullptr);
}

qreal QhWidgetZoom::screenZoomUnderWidget(QWidget *w)
{
    QScreen *screen = QhWidgetUtil::screenUnderWidget(w);
    return screen->logicalDotsPerInch() / WIN_UNIX_SAMECODE(96.0, 72.0);
}

qreal QhWidgetZoom::ptToPx(QWidget *w, qreal pt)
{
    QScreen *screen = QhWidgetUtil::screenUnderWidget(w);

    // pt = px * dpi / 72
    // px = pt / (dpi / 72)

    qreal px = 0;
    qreal dpi = screen->logicalDotsPerInch();
    if (dpi == 0)
        dpi = 10;
    //px = dpi * pt;
    px = pt / (dpi / 72.0);
    return px;
}

qreal QhWidgetZoom::pxToPt(QWidget *w, qreal px)
{
    QScreen *screen = QhWidgetUtil::screenUnderWidget(w);

    // pt = px * dpi / 72
    // px = pt / (dpi/72)

    qreal pt = 0;
    qreal dpi = screen->logicalDotsPerInch();
    pt = px * (dpi / 72.0);
    return pt;
}

bool QhWidgetZoom::enableZoom() const
{
    return d->enableZoom;
}

qreal QhWidgetZoom::validZoom() const
{
    if (!d->enableZoom)
        return 1.0;

    return qMin(d->zoom, d->maxZoom);
}

qreal QhWidgetZoom::zoom() const
{
    return d->zoom;
}

qreal QhWidgetZoom::maxZoom() const
{
    return d->maxZoom;
}

void QhWidgetZoom::setEnableZoom(bool enableZoom)
{
    d->enableZoom = enableZoom;
}

void QhWidgetZoom::setMaxZoom(qreal maxZoom)
{
    d->maxZoom = maxZoom;
}

void QhWidgetZoom::setZoom(qreal zoom)
{
    d->zoom = zoom;
}

qreal QhWidgetZoom::calcZoomSize(qreal s) const
{
    return calcZoomSize(s, validZoom());
}

QSize QhWidgetZoom::calcZoomSize(const QSize &size) const
{
    return calcZoomSize(size, validZoom());
}

QRect QhWidgetZoom::calcZoomSize(const QRect &rt) const
{
    return calcZoomSize(rt, validZoom());
}

/// @brief Ensure that the size cannot be 0
qreal sizeCorrect(qreal sOld, qreal sNew)
{
    if (sOld >= 1.0 && sNew < 1.0)
        return 1.0;
    return sNew;
}

qreal QhWidgetZoom::calcZoomSize(qreal s, qreal scale) const
{
    if (!d->enableZoom)
        return s;
    return sizeCorrect(s, s * scale);
}

QSize QhWidgetZoom::calcZoomSize(const QSize &size, qreal scale) const
{
    if (!d->enableZoom)
        return size;

    qreal ww = size.width();
    qreal wh = size.height();

    auto nsize = QSize(sizeCorrect(ww, ww * scale), sizeCorrect(wh, wh * scale));
    if (nsize.width() > 16777215)
        nsize.setWidth(16777215);
    if (nsize.height() > 16777215)
        nsize.setHeight(16777215);
    return nsize;
}

QRect QhWidgetZoom::calcZoomSize(const QRect &rt, qreal scale) const
{
    if (!d->enableZoom)
        return rt;

    qreal x = rt.x();
    qreal y = rt.y();
    qreal ww = rt.width();
    qreal wh = rt.height();
    return QRect(
        sizeCorrect(x, x * scale), sizeCorrect(y, y * scale),
        sizeCorrect(ww, ww * scale), sizeCorrect(wh, wh * scale));
}

void QhWidgetZoom::zoomWidget(QWidget *widget)
{
    if (!d->enableZoom || !widget)
        return;

    auto factor = validZoom();
    if (qAbs(factor - 1) <= 0.000001) // same as 1
        return;

    d->zoomSizeChild(widget, factor);
}

QString QhWidgetZoom::zoomQssPx(const QString &qss, const QVector<QString> &replaceAttributes)
{
    if (!d->enableZoom)
        return qss;

    auto zoom = validZoom();
    if (qAbs(zoom - 1) <= 0.000001)
        return qss;

    QString newQss = qss;
    for (auto attr: replaceAttributes)
        replaceQssSize(attr, newQss, -1, zoom);
    return newQss;
}

void QhWidgetZoom::replaceQssSize(const QString &replaceName, QString &qss, int fromEd, qreal factor)
{
    // "aa:xx;"
    // "xxxxx; font-size: 12px;"
    int lidx = qss.lastIndexOf(replaceName + ":", fromEd);
    if (lidx < 0)
        return;

    int lidxBg = qss.indexOf(":", lidx);
    int lidxEd = qss.indexOf(";", lidx);
    if (lidxEd >= 0 && lidxBg >= 0) {
        QString value = qss.mid(lidxBg + 1, lidxEd - lidxBg - 1).trimmed();
        QStringList strs = value.split(" ", QString::SkipEmptyParts);
        QString rpText;
        foreach (auto str, strs) {
            qreal fpx = 0;
            bool bPx = false;
            if (str.endsWith("px")) {
                str.remove("px");
                bPx = true;
            }

            fpx = str.toInt();
            int newPx = fpx * factor;

            if (!rpText.isEmpty())
                rpText.append(" ");
            rpText.append(QString::number(newPx));
            if (bPx)
                rpText.append("px");
        }
        qss = qss.replace(lidxBg + 1, lidxEd - lidxBg - 1, rpText);
    }
    replaceQssSize(replaceName, qss, lidx - 1, factor);
}

QhWidgetZoomPrivate::QhWidgetZoomPrivate(QhWidgetZoom *q):
    ptr(q)
{

}

QhWidgetZoomPrivate::~QhWidgetZoomPrivate()
{

}

void QhWidgetZoomPrivate::zoomSizeChild(QWidget *w, qreal scale)
{
    if (!enableZoom)
        return;

    auto dpiResize = [this](QWidget *w, qreal scale)
    {
        if (zoomedWidgets.contains(w))
            return;

        connect(w, &QWidget::destroyed, this, [this, w](QObject *obj) {
            if (w == obj && zoomedWidgets.contains(w)) {
                zoomedWidgets.removeOne(w);
            }
        });
        zoomedWidgets.append(w);

        w->setMinimumSize(ptr->calcZoomSize(w->minimumSize(), scale));
        w->setMaximumSize(ptr->calcZoomSize(w->maximumSize(), scale));
        w->resize(ptr->calcZoomSize(w->size(), scale));
    };

    // widget size
    dpiResize(w, scale);

    // widget layout
    zoomSizeChild(w->layout(), scale);

    // all sub widget
    auto objs = w->children();
    for (auto *obj: objs) {
        if (!obj->isWidgetType()) {
            continue;
        }

        QWidget *widget = static_cast<QWidget*>(obj);
        zoomSizeChild(widget, scale);
    }
}

void QhWidgetZoomPrivate::zoomSizeChild(QLayout *ly, qreal scale)
{
    if (!enableZoom || !ly || zoomedLayouts.contains(ly))
        return;

    connect(ly, &QLayout::destroyed, this, [this, ly](QObject *obj) {
        if (ly == obj && zoomedLayouts.contains(ly)) {
            zoomedLayouts.removeOne(ly);
        }
    });
    zoomedLayouts.append(ly);

    auto mgs = ly->contentsMargins();
    mgs.setBottom((qreal)mgs.bottom() * scale);
    mgs.setTop((qreal)mgs.top() * scale);
    mgs.setLeft((qreal)mgs.left() * scale);
    mgs.setRight((qreal)mgs.right() * scale);
    ly->setContentsMargins(mgs);

    if (ly->inherits("QGridLayout")) {
        QGridLayout *glayout = qobject_cast<QGridLayout *>(ly);
        glayout->setHorizontalSpacing((qreal)glayout->horizontalSpacing() * scale);
        glayout->setVerticalSpacing((qreal)glayout->verticalSpacing() * scale);
    } else if (ly->inherits("QFormLayout")) {
        QFormLayout *flayout = qobject_cast<QFormLayout *>(ly);
        flayout->setHorizontalSpacing((qreal)flayout->horizontalSpacing() * scale);
        flayout->setVerticalSpacing((qreal)flayout->verticalSpacing() * scale);
    } else {
        ly->setSpacing((qreal)ly->spacing() * scale);
    }

    int cnt = ly->count();
    for (int n = 0; n < cnt; ++n) {
        QLayoutItem *item = ly->itemAt(n);
        if (item->layout())
            zoomSizeChild(item->layout(), scale);
    }
}
