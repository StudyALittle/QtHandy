#include "qhgradientslider.h"
#include "qhgradientslider_p.h"
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QLineEdit>
#include <QTextEdit>
#include <QApplication>
#include "qhstyle.h"

QhGradientSliderPrivate::QhGradientSliderPrivate(QhGradientSlider *gradientSlider):
    gradientSlider(gradientSlider),
    linearGradient(0.5, 0, 0.5, 1.0)
{
    linearGradient.setColorAt(0.0f, Qt::black);
    linearGradient.setColorAt(1.0f, Qt::red);

    qApp->installEventFilter(this);
}

QhGradientSliderPrivate::~QhGradientSliderPrivate()
{

}

bool QhGradientSliderPrivate::containsCircle(
    const QPointF &center, qreal radius, const QPointF &pos) const
{
    QPointF d = pos - center;
    return QPointF::dotProduct(d, d) <= radius * radius;
}

QColor QhGradientSliderPrivate::colorAt(qreal t) const
{
    auto stops = linearGradient.stops();
    if (stops.isEmpty())
        return Qt::white;
    if (t <= stops.first().first)
        return stops.first().second;
    if (t >= stops.last().first)
        return stops.last().second;

    for (int i = 0; i < stops.size() - 1; ++i) {
        qreal p0 = stops[i].first;
        qreal p1 = stops[i+1].first;
        if (t >= p0 && t <= p1) {
            qreal k = (t - p0) / (p1 - p0);
            QColor c0 = stops[i].second;
            QColor c1 = stops[i+1].second;
            return QColor(
                c0.red()   + k * (c1.red()   - c0.red()),
                c0.green() + k * (c1.green() - c0.green()),
                c0.blue()  + k * (c1.blue()  - c0.blue()),
                c0.alpha() + k * (c1.alpha() - c0.alpha()));
        }
    }
    return stops.last().second;
}

qreal QhGradientSliderPrivate::posToAt(const QPoint &pos) const
{
    qreal w = gradientSlider->width() - 2 * circleRadius;
    if (w <= 0)
        return -1;

    qreal t = (pos.x() - circleRadius) / w;
    return qBound(0.0, t, 1.0);
}

void QhGradientSliderPrivate::processPressPos(const QPoint &pos)
{
    qreal t = posToAt(pos);
    if (t < 0)
        return;

    int willIndex = -1;
    auto stops = linearGradient.stops();
    for (int i = 0; i < stops.size(); ++i) {
        auto stop = stops.at(i);

        if (i == 0 && t < stop.first) {
            willIndex = 0;
        } else if (t > stop.first && (i == stops.size() - 1 || t < stops.at(i + 1).first)) {
            willIndex = i + 1;
        }

        // 选中点
        qreal x = circleRadius + stop.first * barRect.width();
        QPointF center(x, (qreal)gradientSlider->height() / 2.0f);
        if (containsCircle(center, circleRadius - 3, pos)) {
            gradientSlider->setSelectIndex(i);
            gradientSlider->setSelectColor(stop.second);
            gradientSlider->update();
            return;
        }
    }

    if (!barRect.contains(pos))
        return;

    if (checkedIndex < 0 || willIndex >= 0) {
        linearGradient.setColorAt(t, colorAt(t));
        gradientSlider->setSelectIndex(willIndex);
        gradientSlider->setSelectColor(colorAt(t));
    }
    gradientSlider->update();
}

void QhGradientSliderPrivate::updateFromPos(const QPoint &pos)
{
    if (checkedIndex < 0)
        return;

    qreal t = posToAt(pos);
    if (t < 0)
        return;

    int idx = -1;
    auto stops = linearGradient.stops();
    for (int i = 0; i < stops.size(); ++i) {
        auto stop = stops.at(i);
        if (qFuzzyCompare(stop.first, t)) {
            // QT目前不支持pos一样
            return;
        }
    }

    // remove old
    if (checkedIndex < stops.size())
        stops.removeAt(checkedIndex);

    // add move pos
    for (int i = 0; i < stops.size(); ++i) {
        auto stop = stops.at(i);
        if (t < stop.first) {
            stops.insert(0, {t, checkedColor});
            idx = 0;
            break;
        } else if (t > stop.first
                && (i == stops.size() - 1 || t < stops.at(i + 1).first)) {
            stops.insert(i + 1, {t, checkedColor});
            idx = i + 1;
            break;
        }
    }

    linearGradient.setStops(stops);
    gradientSlider->setSelectIndex(idx);
    gradientSlider->update();
}

void QhGradientSliderPrivate::removeCheckedPos()
{
    auto stops = linearGradient.stops();
    if (stops.size() <= 2)
        return;

    if (checkedIndex < stops.size())
        stops.removeAt(checkedIndex);
    checkedIndex = stops.size() - 1;
    linearGradient.setStops(stops);
    gradientSlider->setSelectIndex(checkedIndex);
    gradientSlider->setSelectColor(stops.at(checkedIndex).second);
    gradientSlider->update();
}

bool QhGradientSliderPrivate::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        auto *ke = static_cast<QKeyEvent *>(event);

        if (ke->key() == Qt::Key_Delete) {
            // 避免在输入框里误删
            if (qobject_cast<QLineEdit*>(QApplication::focusWidget()) ||
                qobject_cast<QTextEdit*>(QApplication::focusWidget())) {
                return QObject::eventFilter(obj, event);
            }
            removeCheckedPos();
            return true;
        }
    }
    return QObject::eventFilter(obj, event);
}

QhGradientSlider::QhGradientSlider(QWidget *parent):
    QWidget(parent), d(new QhGradientSliderPrivate(this))
{

}

QhGradientSlider::~QhGradientSlider()
{

}

QColor QhGradientSlider::selectedColor() const
{
    return d->checkedColor;
}

int QhGradientSlider::selectedIndex() const
{
    return d->checkedIndex;
}

void QhGradientSlider::setSelectColor(const QColor &color)
{
    if (d->checkedColor == color)
        return;

    d->checkedColor = color;
    auto stops = d->linearGradient.stops();
    stops[d->checkedIndex].second = color;
    d->linearGradient.setStops(stops);
    this->update();
    emit selectedColorChanged(color);
}

void QhGradientSlider::setSelectIndex(int index)
{
    if (d->checkedIndex == index || index < 0
        || index >= d->linearGradient.stops().size())
        return;

    d->checkedIndex = index;
    this->update();
    emit selectedIndexChanged(index);
}

void QhGradientSlider::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    d->circleRadius = (qreal)height() / 2.0f;
    d->barRadius = (height() - d->margin.top() - d->margin.bottom()) / 2.0f;
    d->barRect = QRectF(d->circleRadius, d->margin.top(),
        width() - 2 * d->circleRadius, height() - d->margin.top() - d->margin.bottom());

    // 画渐变条
    QLinearGradient grad = d->linearGradient;
    grad.setStart(d->barRect.topLeft());
    grad.setFinalStop(d->barRect.topRight());
    QPainterPath barPath;
    barPath.addRoundedRect(d->barRect, d->barRadius, d->barRadius);
    p.fillPath(barPath, grad);

    auto stops = d->linearGradient.stops();
    for (int i = 0; i < stops.size(); ++i) {
        auto stop = stops.at(i);
        qreal x = d->circleRadius + stop.first * d->barRect.width();
        QPointF center(x, (qreal)height() / 2.0f);
        if (i == d->checkedIndex) {
            continue;
        }
        QhStyle::drawIndicatorRing(&p, center, stop.second, d->circleRadius - 3);
    }
    // 后绘制选中的，在顶层显示
    if (d->checkedIndex >= 0 && d->checkedIndex < stops.size()) {
        auto stop = stops.at(d->checkedIndex);
        qreal x = d->circleRadius + stop.first * d->barRect.width();
        QPointF center(x, (qreal)height() / 2.0f);
        // 外圈选中阴影
        p.setBrush(Qt::NoBrush);
        for (int n = 0; n < 6; ++n) {
            p.setPen(QPen(QColor(0x00, 0x45, 0xFF, 20 + n * 26), 1.0f));
            p.drawEllipse(center, d->circleRadius - n, d->circleRadius - n);
        }
        QhStyle::drawIndicatorRing(&p, center, stop.second, d->circleRadius - 3);
    }
}

void QhGradientSlider::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
    d->processPressPos(e->pos());
}

void QhGradientSlider::mouseMoveEvent(QMouseEvent *e)
{
    QWidget::mouseMoveEvent(e);
    if (e->buttons() & Qt::LeftButton)
        d->updateFromPos(e->pos());
}
