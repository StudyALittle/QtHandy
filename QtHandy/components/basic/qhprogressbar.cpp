#include "qhprogressbar.h"
#include "qhprogressbar_p.h"
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>

QhProgressBar::QhProgressBar(QWidget *parent) : QProgressBar(parent), d(new QhProgressBarPrivate(this))
{
}

QhProgressBar::~QhProgressBar()
{
}

bool QhProgressBar::isRoundedCorner() const
{
    return d->bRoundedCorner;
}

void QhProgressBar::setRoundedCorner(bool b)
{
    d->bRoundedCorner = b;
    this->update();
}

QColor QhProgressBar::getBackground() const
{
    return d->background;
}

QColor QhProgressBar::getChunkBackground() const
{
    return d->chunkBackground;
}


void QhProgressBar::setBackground(const QColor &color)
{
    d->background = color;
    this->update();
}

void QhProgressBar::setChunkBackground(const QColor &color)
{
    d->chunkBackground = color;
    this->update();
}

void QhProgressBar::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    if (!d->bRoundedCorner) {
        QProgressBar::paintEvent(e);
        return;
    }

    qreal w = this->width();
    qreal h = this->height();
    qreal radius = h / 2.0f;

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::SmoothPixmapTransform, true);

    // p.drawRect(this->rect());

    QColor backgroundColor = d->background;
    QColor chunkColor = d->chunkBackground;

    auto drawFirstSemicircle = [=](QPainter &p, const QColor &fillColor) {
        QPainterPath path;
        QRectF rect(0, 0, h, h);
        path.moveTo(radius, radius);
        path.arcTo(rect, 90, 180);
        path.moveTo(radius, radius);
        p.fillPath(path, fillColor);
    };
    auto drawLastSemicircle = [=](QPainter &p, qreal w, const QColor &fillColor) {
        QPainterPath path;
        qreal x = w - h;
        QRectF rect(x, 0, h, h);
        path.moveTo(x + radius, radius);
        path.arcTo(rect, -90, 180);
        path.moveTo(x + radius, radius);
        p.fillPath(path, fillColor);
    };
    auto drawCenterRect = [=](QPainter &p, qreal w, const QColor &fillColor) {
        p.fillRect(QRectF(radius - 1.0f, 0, w - h + 2.0f, h), fillColor);
    };

    /// 绘制背景
    // 1）绘制前面的半圆
    drawFirstSemicircle(p, backgroundColor);
    // 2）绘制后面面的半圆
    drawLastSemicircle(p, w, backgroundColor);
    // 3）绘制中间的矩形
    drawCenterRect(p, w, backgroundColor);

    // 绘制进度
    {
        qreal max = this->maximum();
        qreal val = this->value();
        qreal cw = w * (val / max);

        // if (cw < h)
        //     cw = h;

        if (cw >= h) {
            // 1）绘制前面的半圆
            drawFirstSemicircle(p, chunkColor);
            // 2）绘制后面面的半圆
            drawLastSemicircle(p, cw, chunkColor);
            // 3）绘制中间的矩形
            drawCenterRect(p, cw, chunkColor);
        } else if (cw >= radius) {
            // 1）绘制前面的半圆
            drawFirstSemicircle(p, chunkColor);
            // 2）绘制后面面的半圆
            QPainterPath path;
            qreal rew = (cw - radius) * 2;
            qreal x = cw - rew - 1.0f;
            QRectF rect(x, 0, rew, h);
            path.moveTo(x + rew / 2.0f, radius);
            path.arcTo(rect, -90, 180);
            path.moveTo(x + rew / 2.0f, radius);
            p.fillPath(path, chunkColor);
        } else {
            // 需要绘制前面的半圆(部分)
            QPainterPath path;
            QRectF rect(0, 0, h, h);
            path.moveTo(radius, radius);
            path.arcTo(rect, 90, 180);
            path.moveTo(radius, radius);

            QPainterPath pathSub;
            pathSub.addRect(cw, 0, radius - cw, h);

            path = path.subtracted(pathSub);
            p.fillPath(path, chunkColor);
        }
    }

    // 绘制边框
    {
    }
}

QhProgressBarPrivate::QhProgressBarPrivate(QhProgressBar *p) : p(p)
{
}

QhProgressBarPrivate::~QhProgressBarPrivate()
{
}
