#include "qhspin.h"
#include "qhspin_p.h"
#include <QPainter>
#include <QtMath>

QhSpin::QhSpin(QWidget *parent) : QLabel(parent), d(new QhSpinPrivate(this))
{
    d->init();
    d->initSizeColor();
}

QhSpin::QhSpin(Style style, QWidget *parent) : QLabel(parent), d(new QhSpinPrivate(this))
{
    d->init();
    setStyle(style);
}

QhSpin::~QhSpin()
{
}

void QhSpin::setStyle(Style style)
{
    d->style = style;
    d->initSizeColor();
    this->update();
}

void QhSpin::setColor(const QColor &displayColor, const QColor &undersideColor)
{
    d->displayColor = displayColor;
    d->undersideColor = undersideColor;
    d->initSizeColor();
    this->update();
}

void QhSpin::setDotNum(int dotNum)
{
    d->dotNum = dotNum;
    d->initSizeColor();
    this->update();
}

void QhSpin::setWidthRatio(qreal wr)
{
    d->widthRatio = wr;
    d->initSizeColor();
    this->update();
}

void QhSpin::setMaxWidth(int maxw)
{
    d->maxWidth = maxw;
    d->initSizeColor();
    this->update();
}

void QhSpin::setMinWidth(int minw)
{
    d->minWidth = minw;
    d->initSizeColor();
    this->update();
}

void QhSpin::start(int ms)
{
    d->timer.start(ms);
    this->update();
}

void QhSpin::stop()
{
    d->timer.stop();
    this->update();
}

void QhSpin::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);

    if (d->style == StyleLabel)
        return;

    QPainter p(this);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    p.setRenderHint(QPainter::Antialiasing);

    qreal w = this->width();
    qreal h = this->height();

    qreal nmin = d->minWH();

    qreal dotMax = 0;
    foreach (auto circle, d->dotCircle) {
        if (circle.size.height() > dotMax)
            dotMax = circle.size.height();
    }

    // 以中心为原点
    p.translate(w / 2.0, h / 2.0);

    // 以中心为远点旋转
    qreal centerX = nmin / 2.0f - dotMax / 2.0f;
    qreal centerY = 0.0f;

    // 绘制圆
    foreach (auto circle, d->dotCircle) {
        p.save();
        p.rotate(circle.angle);
        QPainterPath path;
        path.addEllipse(QPointF(centerX, centerY), circle.size.width() / 2.0, circle.size.height() / 2.0);
        p.fillPath(path, circle.color);
        p.restore();
    }
}

void QhSpin::resizeEvent(QResizeEvent *e)
{
    QLabel::resizeEvent(e);
    d->updateSizes();
}

QhSpinPrivate::QhSpinPrivate(QhSpin *p) : p(p)
{
}

QhSpinPrivate::~QhSpinPrivate()
{
}

void QhSpinPrivate::init()
{
    connect(&timer, &QTimer::timeout, this, &QhSpinPrivate::updateAngles);
}

void QhSpinPrivate::initSizeColor()
{
    if (style == QhSpin::StyleDotSS || style == QhSpin::StyleDotDS) {
        dotCircle.clear();
        dotCircle.resize(dotNum);

        qreal widgetR = minWH() / 2.0f;
        qreal dotD = widthRatio * widgetR;
        if (dotD > maxWidth)
            dotD = maxWidth;
        if (dotD < minWidth)
            dotD = minWidth;

        QSizeF dotSize(dotD, dotD);
        qreal angleSpace = 360.0f / (qreal)dotNum;
        qreal colorASpace = 255.0f / (qreal)dotNum;
        qreal sizeDSpace = dotD / (qreal)dotNum;
        qreal angle = 0, colorA = 255.f, sizeD = dotD;
        for (int n = 0; n < dotNum; ++n) {
            switch (style) {
            case QhSpin::StyleDotSS: {
                // 每个圆点大小一样
                DotCircle circ;
                circ.size = dotSize;

                circ.angle = angle;
                angle += angleSpace;

                auto color = displayColor;
                color.setAlpha(colorA);
                circ.color = color;
                colorA -= colorASpace;
                dotCircle[n] = circ;
                break;
            }
            case QhSpin::StyleDotDS: {
                // 每个圆点大小不一样
                DotCircle circ;

                circ.size = QSizeF(sizeD, sizeD);
                sizeD -= sizeDSpace;

                circ.angle = angle;
                angle += angleSpace;

                circ.color = displayColor;
                dotCircle[n] = circ;
                break;
            }
            default:
                break;
            }
        }
    }
}

qreal QhSpinPrivate::minWH()
{
    return qMin(p->width(), p->height());
}

void QhSpinPrivate::updateAngles()
{
    if (style == QhSpin::StyleDotSS || style == QhSpin::StyleDotDS) {
        qreal angleSpace = 360.0f / (qreal)dotNum;
        for (int n = 0; n < dotNum; ++n) {
            auto &circ = dotCircle[n];
            // 每个圆点大小一样
            circ.angle += angleSpace;
            if (circ.angle >= 360)
                circ.angle = 0;
        }
    }
    p->update();
}

void QhSpinPrivate::updateSizes()
{
    initSizeColor();
    p->update();
}
