#include "qhalphaslider.h"
#include "qhalphaslider_p.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtMath>
#include "qhstyle.h"

QhAlphaSliderPrivate::QhAlphaSliderPrivate(QhAlphaSlider *alphaSlider):
    alphaSlider(alphaSlider)
{

}

QhAlphaSliderPrivate::~QhAlphaSliderPrivate()
{

}

void QhAlphaSliderPrivate::updateFromPos(const QPoint &pos)
{
    qreal radius = alphaSlider->height() / 2.0;
    qreal w = alphaSlider->width() - 2 * radius;
    if (w <= 0)
        return;

    qreal t = (pos.x() - radius) / w;
    alphaSlider->setAlpha(t);
}

void QhAlphaSliderPrivate::drawCheckerboard(QPainter *p, const QRectF &rect, int rows)
{
    // 先铺浅色底
    p->fillRect(rect, QColor(255, 255, 255));

    // 再画深色格子
    p->setPen(Qt::NoPen);
    p->setBrush(QColor(200, 200, 200));

    qreal cellSize = rect.height() / rows;
    qreal cols = qCeil(rect.width() / cellSize);
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if ((row + col) % 2 == 0)
                continue;
            QRectF cell(
                rect.left() + col * cellSize,
                rect.top() + row * cellSize,
                cellSize, cellSize);
            p->drawRect(cell);
        }
    }
}

QhAlphaSlider::QhAlphaSlider(QWidget *parent):
    QWidget(parent), d(new QhAlphaSliderPrivate(this))
{

}

QhAlphaSlider::~QhAlphaSlider()
{

}

qreal QhAlphaSlider::alpha() const
{
    return d->alpha;
}

void QhAlphaSlider::setColor(const QColor &color)
{
    d->color = color;
    d->color.setAlphaF(d->alpha);
    this->update();
}

void QhAlphaSlider::setAlpha(qreal alpha)
{
    alpha = qBound(0.0, alpha, 1.0);
    if (qFuzzyCompare(alpha, d->alpha))
        return;

    d->alpha = alpha;
    d->color.setAlphaF(d->alpha);
    this->update();
    emit alphaChanged(d->alpha);
}

void QhAlphaSlider::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    qreal circleRadius = (qreal)height() / 2.0f;
    qreal bgRadius = (height() - d->margin.top() - d->margin.bottom()) / 2.0f;
    QRectF barRect(circleRadius, d->margin.top(),
        width() - 2 * circleRadius, height() - d->margin.top() - d->margin.bottom());

    // 底色（棋盘样式）
    QPainterPath barPath;
    barPath.addRoundedRect(barRect, bgRadius, bgRadius);
    p.save();
    p.setClipPath(barPath);
    d->drawCheckerboard(&p, barRect, 3);
    p.restore();

    // 颜色渐变：透明 → 纯色
    QLinearGradient grad(barRect.topLeft(), barRect.topRight());
    QColor c0 = d->color;
    c0.setAlphaF(0.0);
    QColor c1 = d->color;
    c1.setAlphaF(1.0);
    grad.setColorAt(0.0, c0);
    grad.setColorAt(1.0, c1);
    p.fillPath(barPath, grad);

    // 当前透明度
    qreal x = circleRadius + d->alpha * barRect.width();
    QPointF center(x, height() / 2.0);

    QColor cur = d->color;
    cur.setAlphaF(d->alpha);
    QhStyle::drawIndicatorRing(&p, center, cur, circleRadius);
}

void QhAlphaSlider::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
    d->updateFromPos(e->pos());
}

void QhAlphaSlider::mouseMoveEvent(QMouseEvent *e)
{
    QWidget::mouseMoveEvent(e);
    if (e->buttons() & Qt::LeftButton)
        d->updateFromPos(e->pos());
}
