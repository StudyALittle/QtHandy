#include "qhprogressbar.h"
#include "qhprogressbar_p.h"
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>
#include <QLinearGradient>
#include <QtMath>

QhProgressBar::QhProgressBar(QWidget *parent) : QProgressBar(parent), d(new QhProgressBarPrivate(this))
{
}

QhProgressBar::~QhProgressBar()
{
}

QhProgressBar::TextAlign QhProgressBar::textAlign() const
{
    return d->textAlign;
}

int QhProgressBar::circleMinWidth() const
{
    return d->circleMinWidth;
}

int QhProgressBar::circleMaxWidth() const
{
    return d->circleMaxWidth;
}

qreal QhProgressBar::circleWidthRatio() const
{
    return d->circleWidthRatio;
}

void QhProgressBar::setType(Type type)
{
    d->type = type;
    this->update();
}

void QhProgressBar::setTextAlign(TextAlign align)
{
    d->textAlign = align;
    this->update();
}

void QhProgressBar::setCircleMinWidth(int w)
{
    d->circleMinWidth = w;
    this->update();
}

void QhProgressBar::setCircleMaxWidth(int w)
{
    d->circleMaxWidth = w;
    this->update();
}

void QhProgressBar::setCircleWidthRatio(qreal ratio)
{
    d->circleWidthRatio = ratio;
    this->update();
}

QhProgressBar::Type QhProgressBar::type() const
{
    return d->type;
}

QColor QhProgressBar::getBackground() const
{
    return d->background;
}

QColor QhProgressBar::getChunkBackground() const
{
    return d->chunkBackground;
}

Qt::Orientation QhProgressBar::gradientOrientation() const
{
    return d->gradientOrientation;
}

QVector<QhProgressBar::GradientItem> QhProgressBar::gradients() const
{
    return d->gradients;
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

void QhProgressBar::setGradients(const QVector<GradientItem> &items)
{
    d->gradients = items;
    this->update();
}

void QhProgressBar::setGradientOrientation(Qt::Orientation orientation)
{
    d->gradientOrientation = orientation;
    this->update();
}

void QhProgressBar::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::HighQualityAntialiasing, true);
    p.setRenderHint(QPainter::SmoothPixmapTransform, true);

    switch (d->type) {
    case Default: {
        QProgressBar::paintEvent(e);
        break;
    }
    case Line: {
        d->drawLine(p);
        d->drawText(p);
        break;
    }
    case Circle: {
        d->drawCircle(p);
        d->drawText(p);
        break;
    }
    case Dashboard: {
        d->drawDashboard(p);
        d->drawText(p);
        break;
    }
    default:
        break;
    }
}

QhProgressBarPrivate::QhProgressBarPrivate(QhProgressBar *p) : pBar(p)
{
}

QhProgressBarPrivate::~QhProgressBarPrivate()
{
}

void QhProgressBarPrivate::drawLine(QPainter &p)
{
    qreal w = pBar->width();
    qreal h = pBar->height();
    qreal radius = h / 2.0f;

    qreal max = pBar->maximum();
    qreal val = pBar->value();
    qreal cw = w * (val / max);

    QColor backgroundColor = background;
    QColor chunkColor = chunkBackground;

    auto drawFirstSemicircle = [=](QPainter &p, const QBrush &fillColor) {
        QPainterPath path;
        QRectF rect(0, 0, h, h);
        path.moveTo(radius, radius);
        path.arcTo(rect, 90, 180);
        path.moveTo(radius, radius);
        p.fillPath(path, fillColor);
    };
    auto drawLastSemicircle = [=](QPainter &p, qreal w, const QBrush &fillColor) {
        QPainterPath path;
        qreal x = w - h;
        QRectF rect(x, 0, h, h);
        path.moveTo(x + radius, radius);
        path.arcTo(rect, -90, 180);
        path.moveTo(x + radius, radius);
        p.fillPath(path, fillColor);
    };
    auto drawCenterRect = [=](QPainter &p, qreal w, const QBrush &fillColor) {
        p.fillRect(QRectF(radius - 1.0f, 0, w - h + 2.0f, h), fillColor);
    };

    /// 绘制背景
    // 1）绘制前面的半圆
    drawFirstSemicircle(p, backgroundColor);
    // 2）绘制后面面的半圆
    drawLastSemicircle(p, w, backgroundColor);
    // 3）绘制中间的矩形
    drawCenterRect(p, w, backgroundColor);

    QBrush brush;
    if (gradients.size() < 2) {
        brush = chunkColor;
    } else {
        QLinearGradient gradient(0, 0, w, 0);
        if (gradientOrientation == Qt::Vertical) {
            gradient.setFinalStop(0, h);
        }
        for (auto &item : gradients) {
            gradient.setColorAt(item.pos, item.color);
        }
        brush = gradient;
    }

    p.save();
    /// 绘制进度
    if (cw >= h) {
        // 1）绘制前面的半圆
        drawFirstSemicircle(p, brush);
        // 2）绘制后面面的半圆
        drawLastSemicircle(p, cw, brush);
        // 3）绘制中间的矩形
        drawCenterRect(p, cw, brush);
    } else if (cw >= radius) {
        // 1）绘制前面的半圆
        drawFirstSemicircle(p, brush);
        // 2）绘制后面面的半圆
        QPainterPath path;
        qreal rew = (cw - radius) * 2;
        qreal x = cw - rew - 1.0f;
        QRectF rect(x, 0, rew, h);
        path.moveTo(x + rew / 2.0f, radius);
        path.arcTo(rect, -90, 180);
        path.moveTo(x + rew / 2.0f, radius);
        p.fillPath(path, brush);
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
        p.fillPath(path, brush);
    }
    p.restore();
}

qreal QhProgressBarPrivate::calculateCircularRingWidth(qreal min)
{
    qreal cw = min / 2.0f * circleWidthRatio;
    if (cw < circleMinWidth)
        cw = circleMinWidth;
    if (cw > circleMaxWidth)
        cw = circleMaxWidth;
    return cw;
}

void QhProgressBarPrivate::setPen(QPainter &p, const QBrush &brush)
{
    auto cw = calculateCircularRingWidth(qMin(pBar->width(), pBar->height()));

    QPen pen;
    pen.setBrush(brush);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setWidthF(cw);
    p.setPen(pen);
    p.setBrush(Qt::NoBrush);
}

void QhProgressBarPrivate::drawCircle(QPainter &p)
{
    // p.drawRect(pBar->rect());

    qreal w = pBar->width();
    qreal h = pBar->height();
    qreal min = qMin(w, h);

    // 计算圆环宽度
    qreal cw = calculateCircularRingWidth(min);

    // 外圆环矩形
    auto externalRect = QRectF((w - min) / 2.0f, (h - min) / 2.0f, min, min);
    // 内圆环矩形
    auto internalCrect = QRectF(externalRect.x() + cw, externalRect.y() + cw, min - cw * 2, min - cw * 2);

    auto drawRing = [=](QPainter &p, const QColor &color) {
        QPainterPath externalPath;
        externalPath.addEllipse(externalRect);

        QPainterPath internalPath;
        internalPath.addEllipse(internalCrect);

        QPainterPath path = externalPath.subtracted(internalPath);
        p.fillPath(path, color);
    };

    // 绘制背景圆环
    drawRing(p, background);

    /// 绘制圆环值
    // 计算要绘制的角度
    qreal max = pBar->maximum();
    qreal val = pBar->value();

    QRectF rect(externalRect.x() + cw / 2.0f, externalRect.y() + cw / 2.0f, externalRect.width() - cw,
        externalRect.height() - cw);
    if (val > 0) {
        qreal angle = 360.0f * (val / max);
#if 1
        p.save();
        // C=2πr 圆周长
        qreal externalC = M_PI * (externalRect.width() - cw);
        qreal halfCircleAngel = (cw / externalC) * 360.0f / 2.0f;
        if (gradients.size() < 2) {
            setPen(p, chunkBackground);
        } else {
            QConicalGradient brush(rect.center(), 90);
            for (auto &item : gradients) {
                brush.setColorAt(1.0f - item.pos, item.color);
            }
            setPen(p, brush);
        }

        p.drawArc(rect, 90 * 16 - halfCircleAngel * 16, -(angle * 16));
        p.restore();
#else
        // C=2πr 圆周长
        qreal externalC = M_PI * externalRect.width();

        auto drawHalfCircleStart = [=](QPainter &p, qreal halfCircleAngel, const QColor &color) {
            QRectF bgRect(-cw / 2.0f, -externalRect.height() / 2.0f, cw, cw);

            QPainterPath path;
            path.moveTo(bgRect.center());
            path.arcTo(bgRect, 90, 180);
            path.moveTo(bgRect.center());

            p.save();
            p.translate(w / 2.0f, h / 2.0f);
            p.rotate(halfCircleAngel);
            p.fillPath(path, color);
            p.restore();
        };

        auto drawHalfCircleEnd = [=](QPainter &p, qreal angle, qreal halfCircleAngel, const QColor &color) {
            QRectF bgRect(-cw / 2.0f, -externalRect.height() / 2.0f, cw, cw);

            QPainterPath path;
            path.moveTo(bgRect.center());
            path.arcTo(bgRect, -90, 180);
            path.moveTo(bgRect.center());

            p.save();
            p.translate(externalRect.center());
            p.rotate(angle - halfCircleAngel);
            p.fillPath(path, color);
            p.restore();
        };

        auto drawRRing = [=](QPainter &p, qreal angle, qreal halfCircleAngel, const QColor &color) {
            QPainterPath path;
            path.moveTo(externalRect.center());
            path.arcTo(externalRect, 90 - halfCircleAngel + 0.5f, -(angle - halfCircleAngel * 2.0f) - 1.0f);
            path.moveTo(externalRect.center());
            QPainterPath internalPath;
            internalPath.addEllipse(internalCrect);

            path = path.subtracted(internalPath);
            p.fillPath(path, color);
        };

        qreal halfCircleAngel = (cw / externalC) * 360.0f / 2.0f;
        if (angle < halfCircleAngel * 2.0f) {
            angle = halfCircleAngel * 2.0f;
        }

        // 绘制起始端半圆环
        drawHalfCircleStart(p, halfCircleAngel, chunkBackground);
        // 绘制结束端半圆环
        drawHalfCircleEnd(p, angle, halfCircleAngel, chunkBackground);

        if (angle > halfCircleAngel * 2.0f) {
            // 绘制直角圆环
            drawRRing(p, angle, halfCircleAngel, chunkBackground);
        }
#endif
    }
}

void QhProgressBarPrivate::drawDashboard(QPainter &p)
{
    auto fillDashboard = [this, &p](QRectF rectF, qreal angle, qreal ratio, const QBrush &brush) {
        p.save();
        setPen(p, brush);
        p.drawArc(rectF, (270 - (360.0f - angle) / 2.0f) * 16, -(angle * ratio * 16));
        p.restore();
    };

    qreal w = pBar->width();
    qreal h = pBar->height();
    qreal min = qMin(w, h);
    // 计算圆环宽度
    qreal cw = calculateCircularRingWidth(min);

    // 仪表盘角度占比
    qreal angle = 360.0f - 30.0f * 2;

    // H: 绘制高度
    // LB: 邻边(下半部分圆的高度)
    // COS: cos夹角
    // XB: 斜边（半径）
    // LB = (H * COS) / （COS + 1）
    // XB = H - LB;
    qreal dh = min - cw;                       // 直径
    qreal iangle = (360.0f - angle) / 2.0f;    // cos夹角
    qreal riangle = qDegreesToRadians(iangle); // 弧度
    qreal ciangle = qCos(riangle);             // qCos

    qreal lb = (dh * ciangle) / (ciangle + 1);
    qreal r = dh - lb;

    qreal val = pBar->value();
    qreal max = pBar->maximum();

    QRectF rect(w / 2.0f - r, h - lb - r - cw / 2.0f, r * 2, r * 2);
    if (max > val)
        fillDashboard(rect, angle, 1.0f, background);

    if (val > 0) {
        if (gradients.size() < 2) {
            fillDashboard(rect, angle, (val / max), chunkBackground);
        } else {
            QConicalGradient brush(rect.center(), 270);
            brush.setColorAt(0.0, gradients.first().color);
            brush.setColorAt(1.0, gradients.last().color);
            for (auto &item : gradients) {
                brush.setColorAt(item.pos * 360.0f / angle, item.color);
            }

            fillDashboard(rect, angle, (val / max), brush);
        }
    }
}

void QhProgressBarPrivate::drawText(QPainter &p)
{
    if (!pBar->isTextVisible())
        return;

    QhProgressBar::TextAlign tAlign = QhProgressBar::AlignCenter;
    switch (type) {
    case QhProgressBar::Line:
        tAlign = textAlign;
        break;
    default:
        break;
    }

    qreal max = pBar->maximum();
    qreal val = pBar->value();
    QString text = QString::number((val / max) * 100) + "%";

    qreal mg = 4;
    qreal pw = pBar->width() * (val / max);
    QFontMetricsF fm(p.font());
    qreal tl = fm.horizontalAdvance(text) + mg * 2;
    if (type == QhProgressBar::Line && pw <= tl)
        tAlign = QhProgressBar::AlignLeft;

    switch (tAlign) {
    case QhProgressBar::AlignFollowText: {
        p.drawText(QRectF(pw - tl, 0, tl, pBar->height()), Qt::AlignVCenter | Qt::AlignLeft, text);
        break;
    }
    case QhProgressBar::AlignCenter: {
        p.drawText(pBar->rect(), Qt::AlignCenter, text);
        break;
    }
    case QhProgressBar::AlignLeft: {
        QRect rect = pBar->rect();
        rect.setLeft(mg);
        p.drawText(rect, Qt::AlignVCenter | Qt::AlignLeft, text);
        break;
    }
    case QhProgressBar::AlignRight: {
        QRect rect = pBar->rect();
        rect.setRight(rect.right() - mg);
        p.drawText(rect, Qt::AlignVCenter | Qt::AlignRight, text);
        break;
    }
    default:
        break;
    }
}
