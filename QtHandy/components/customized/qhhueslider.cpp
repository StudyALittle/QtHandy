#include "qhhueslider.h"
#include "qhhueslider_p.h"
#include <QPainter>
#include <QMouseEvent>

QhHueSlider::QhHueSlider(Qt::Orientation orientation, QWidget *parent):
    QWidget(parent), d(new QhHueSliderPrivate(this))
{
    d->orientation = orientation;
}

QhHueSlider::~QhHueSlider()
{

}

qreal QhHueSlider::hue() const
{
    return d->hue;
}

QColor QhHueSlider::color() const
{
    return QColor::fromHsvF(d->hue, 1.0, 1.0);
}

void QhHueSlider::setHue(qreal hue)
{
//    {
//        h = qBound(0.0, h, 1.0);
//        if (!qFuzzyCompare(h, m_hue)) {
//            m_hue = h;
//            update();
//        }
//    }
    if (d->hue == hue)
        return;

    d->hue = hue;
    this->update();
    emit hueChanged(hue);
}

void QhHueSlider::setColor(const QColor &color)
{
    setHue(color.hueF());
}

void QhHueSlider::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    switch (d->orientation) {
    case Qt::Horizontal: {
        // 1. 渐变条区域（留出圆头的空间）
        qreal radius = height() / 2.0;
        QRectF barRect(radius, 0, width() - 2 * radius, height());

        // 2. 构造色相渐变
        QLinearGradient grad(barRect.topLeft(), barRect.topRight());
        for (int i = 0; i <= 360; i += 30) {
            // 每 30° 一个色标
            grad.setColorAt(i / 360.0, QColor::fromHsvF(qMin(i / 360.0, 1.0), 1.0, 1.0));
        }

        // 3. 画渐变条（圆角矩形）
        QPainterPath barPath;
        barPath.addRoundedRect(barRect, radius, radius);
        p.fillPath(barPath, grad);

        // 4. 画圆形指示器
        qreal x = radius + d->hue * barRect.width();
        QPointF center(x, height() / 2.0);
        qreal circleR = radius * 0.9;

        // 外圈白色 + 阴影感
        p.setPen(QPen(QColor(220, 220, 220), 2));
        p.setBrush(Qt::white);
        p.drawEllipse(center, circleR + 2, circleR + 2);

        // 内圈当前色相颜色
        p.setPen(Qt::NoPen);
        p.setBrush(QColor::fromHsvF(d->hue, 1.0, 1.0));
        p.drawEllipse(center, circleR, circleR);
        break;
    }
    case Qt::Vertical: {
        qreal radius = width() / 2.0;
        // 垂直方向：上下各留 radius，中间是渐变条
        QRectF barRect(0, radius, width(), height() - 2 * radius);

        // 1. 构造垂直渐变
        // Qt 的 y 轴向下，所以顶部是 0，底部是 1
        QLinearGradient grad(barRect.topLeft(), barRect.bottomLeft());
        for (int i = 0; i <= 360; i += 30) {
            grad.setColorAt(i / 360.0, QColor::fromHsvF(qMin(i / 360.0, 1.0), 1.0, 1.0));
        }

        // 2. 画渐变条（圆角矩形）
        QPainterPath barPath;
        barPath.addRoundedRect(barRect, radius, radius);
        p.fillPath(barPath, grad);

        // 3. 画圆形指示器
        // y 坐标：hue=0 在顶部，hue=1 在底部
        qreal y = radius + d->hue * barRect.height();
        QPointF center(width() / 2.0, y);
        qreal circleR = radius * 0.9;

        p.setPen(QPen(QColor(220, 220, 220), 2));
        p.setBrush(Qt::white);
        p.drawEllipse(center, circleR + 2, circleR + 2);

        p.setPen(Qt::NoPen);
        p.setBrush(QColor::fromHsvF(d->hue, 1.0, 1.0));
        p.drawEllipse(center, circleR, circleR);
        break;
    }
    default:
        break;
    }
}

void QhHueSlider::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
    d->updateFromPos(e->pos());
}

void QhHueSlider::mouseMoveEvent(QMouseEvent *e)
{
    QWidget::mouseMoveEvent(e);
    d->updateFromPos(e->pos());
}

QhHueSliderPrivate::QhHueSliderPrivate(QhHueSlider *hueSlider):
    hueSlider(hueSlider)
{

}

QhHueSliderPrivate::~QhHueSliderPrivate()
{

}

void QhHueSliderPrivate::updateFromPos(const QPoint &pos)
{
    switch (orientation) {
    case Qt::Horizontal: {
        qreal radius = hueSlider->height() / 2.0;
        qreal w = hueSlider->width() - 2 * radius;
        if (w <= 0) return;

        qreal t = (pos.x() - radius) / w;
        t = qBound(0.0, t, 1.0);

        if (!qFuzzyCompare(t, hue)) {
            hueSlider->setHue(t);
        }
        break;
    }
    case Qt::Vertical: {
        qreal radius = hueSlider->width() / 2.0;
        qreal h = hueSlider->height() - 2 * radius;
        if (h <= 0) return;

        qreal t = (pos.y() - radius) / h;
        t = qBound(0.0, t, 1.0);

        if (!qFuzzyCompare(t, hue)) {
            hueSlider->setHue(t);
        }
        break;
    }
    default:
        break;
    }
}
