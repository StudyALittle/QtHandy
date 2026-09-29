#include "qhsvpanel.h"
#include "qhsvpanel_p.h"
#include <QPainter>
#include <QMouseEvent>

QhSVPanel::QhSVPanel(QWidget *parent):
    QWidget(parent), d(new QhSVPanelPrivate(this))
{

}

QhSVPanel::~QhSVPanel()
{

}

qreal QhSVPanel::hue() const
{
    return d->hue;
}

qreal QhSVPanel::saturation() const
{
    return d->sat;
}

qreal QhSVPanel::value() const
{
    return d->val;
}

QColor QhSVPanel::currentColor() const
{
    return QColor::fromHsvF(d->hue, d->sat, d->val);
}

void QhSVPanel::setHue(qreal h)
{
    h = qBound(0.0, h, 1.0);
    if (!qFuzzyCompare(h, d->hue)) {
        d->hue = h;
        update();
        emit colorChanged(currentColor());
    }
}

void QhSVPanel::setColor(const QColor &color)
{
    if (!color.isValid())
        return;

    qreal h = color.hueF();
    qreal s = color.saturationF();
    qreal v = color.valueF();

    // 灰色/黑/白没有色相，hueF() 返回 -1
    // 此时保留当前色相，只更新 S/V
    if (h < 0.0)
        h = d->hue;

    // 避免无意义的重绘和信号
    if (qFuzzyCompare(h, d->hue) &&
        qFuzzyCompare(s, d->sat) &&
        qFuzzyCompare(v, d->val))
        return;

    d->hue = h;
    d->sat = s;
    d->val = v;

    update();
    emit colorChanged(currentColor());
}

void QhSVPanel::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QRectF r = rect().adjusted(d->ringRadius, d->ringRadius, - d->ringRadius, - d->ringRadius); // 留 1 像素给圆角

    // 1. 水平渐变：白 → 纯色相色
    QLinearGradient satGrad(r.topLeft(), r.topRight());
    satGrad.setColorAt(0.0, Qt::white);
    satGrad.setColorAt(1.0, QColor::fromHsvF(d->hue, 1.0, 1.0));

    // 2. 垂直渐变：透明 → 黑
    QLinearGradient valGrad(r.topLeft(), r.bottomLeft());
    valGrad.setColorAt(0.0, QColor(0, 0, 0, 0));
    valGrad.setColorAt(1.0, Qt::black);

    // 3. 画圆角矩形，先铺水平渐变，再叠垂直渐变
    QPainterPath path;
    path.addRoundedRect(r, 6, 6);

    p.fillPath(path, satGrad);
    p.fillPath(path, valGrad);

    // 4. 画指示器（白色圆环）
    qreal x = d->sat * r.width();
    qreal y = (1.0 - d->val) * r.height(); // 注意 y 轴向下，亮度越高越靠上
    QPointF center(r.left() + x, r.top() + y);

#if 0
    p.setPen(QPen(Qt::white, 3));
    p.setBrush(Qt::NoBrush);

    QPainterPath pathOut;
    pathOut.addEllipse(center, d->ringRadius, d->ringRadius);
    // p.fillPath(pathOut, Qt::white);
    // p.drawEllipse(center, d->ringRadius, d->ringRadius);

    // 内圈加一层深色，保证在白/黑背景上都看得清
    QPainterPath pathIn;
    pathOut.addEllipse(center, d->ringRadius - 3, d->ringRadius - 3);
    p.fillPath(pathIn, currentColor());

    p.setPen(QPen(QColor(0, 0, 0, 80), 1));
    // p.drawEllipse(center, d->ringRadius, d->ringRadius);
#else
    // 外阴影
    p.setPen(QPen(QColor(0, 0, 0, 20), 3));
    p.setBrush(Qt::NoBrush);
    p.drawEllipse(center, d->ringRadius, d->ringRadius);

    // 外白环
    QPainterPath pathOut;
    pathOut.addEllipse(center, d->ringRadius, d->ringRadius);
    p.fillPath(pathOut, Qt::white);

    // 中心小圆点显示当前色
    QPainterPath pathIn;
    pathIn.addEllipse(center, d->ringRadius - 3, d->ringRadius - 3);
    p.fillPath(pathIn, currentColor());
#endif
}

void QhSVPanel::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
    d->updateFromPos(e->pos());
}

void QhSVPanel::mouseMoveEvent(QMouseEvent *e)
{
    QWidget::mouseMoveEvent(e);
    d->updateFromPos(e->pos());
}

QhSVPanelPrivate::QhSVPanelPrivate(QhSVPanel *svPanel):
    svPanel(svPanel)
{

}

QhSVPanelPrivate::~QhSVPanelPrivate()
{

}

void QhSVPanelPrivate::updateFromPos(const QPoint &pos)
{
    QRectF r = svPanel->rect().adjusted(ringRadius, ringRadius, -ringRadius, -ringRadius);
    if (r.width() <= 0 || r.height() <= 0) return;

    qreal s = qBound(0.0, (pos.x() - r.left()) / r.width(), 1.0);
    qreal v = 1.0 - qBound(0.0, (pos.y() - r.top()) / r.height(), 1.0);

    if (!qFuzzyCompare(s, sat) || !qFuzzyCompare(v, val)) {
        sat = s;
        val = v;
        svPanel->update();
        emit svPanel->colorChanged(svPanel->currentColor());
    }
}
