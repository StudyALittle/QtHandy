#include "qhsvpanel.h"
#include "qhsvpanel_p.h"
#include <QPainter>
#include <QMouseEvent>
#include "qhstyle.h"

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

QColor QhSVPanel::selectedColor() const
{
    return QColor::fromHsvF(d->hue, d->sat, d->val);
}

QPointF QhSVPanel::selectedPos() const
{
    return d->selectedPos;
}

void QhSVPanel::setSelectPos(const QPointF &pos)
{
    d->updateFromPos(QPoint(pos.x(), pos.y()));
}

QPointF QhSVPanel::posFromColor(const QColor &color) const
{
    qreal s = color.saturationF();   // 0.0 ~ 1.0
    qreal v = color.valueF();        // 0.0 ~ 1.0

    qreal x = d->panelRect.left() + s * d->panelRect.width();
    qreal y = d->panelRect.top()  + (1.0 - v) * d->panelRect.height();

    return QPointF(x, y);
}

void QhSVPanel::setHue(qreal h)
{
    h = qBound(0.0, h, 1.0);
    if (qFuzzyCompare(h, d->hue))
        return;

    d->hue = h;
    update();
    emit selectedColorChanged(selectedColor());
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

    if (qFuzzyCompare(h, d->hue) &&
        qFuzzyCompare(s, d->sat) &&
        qFuzzyCompare(v, d->val))
        return;

    d->hue = h;
    d->sat = s;
    d->val = v;

    update();
    emit selectedColorChanged(selectedColor());
}

void QhSVPanel::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QRectF r = rect().adjusted(
        d->ringRadius, d->ringRadius, - d->ringRadius, - d->ringRadius);
    d->panelRect = r;

    // 水平渐变：白 → 纯色相色
    QLinearGradient satGrad(r.topLeft(), r.topRight());
    satGrad.setColorAt(0.0, Qt::white);
    satGrad.setColorAt(1.0, QColor::fromHsvF(d->hue, 1.0, 1.0));

    // 垂直渐变：透明 → 黑
    QLinearGradient valGrad(r.topLeft(), r.bottomLeft());
    valGrad.setColorAt(0.0, QColor(0, 0, 0, 0));
    valGrad.setColorAt(1.0, Qt::black);

    // 画圆角矩形，先铺水平渐变，再叠垂直渐变
    QPainterPath path;
    path.addRoundedRect(r, 6, 6);
    p.fillPath(path, satGrad);
    p.fillPath(path, valGrad);

    // 画指示器（白色圆环）
    qreal x = d->sat * r.width();
    qreal y = (1.0 - d->val) * r.height(); // 注意 y 轴向下，亮度越高越靠上
    d->selectedPos = QPointF(r.left() + x, r.top() + y);

    QhStyle::drawIndicatorRing(&p, d->selectedPos, selectedColor(), d->ringRadius, 5.0f);
}

void QhSVPanel::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
    d->updateFromPos(e->pos());
}

void QhSVPanel::mouseMoveEvent(QMouseEvent *e)
{
    QWidget::mouseMoveEvent(e);
    if (e->buttons() & Qt::LeftButton)
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
    QRectF r = panelRect;
    if (r.width() <= 0 || r.height() <= 0)
        return;

    qreal s = qBound(0.0, (pos.x() - r.left()) / r.width(), 1.0);
    qreal v = 1.0 - qBound(0.0, (pos.y() - r.top()) / r.height(), 1.0);

    if (!qFuzzyCompare(s, sat) || !qFuzzyCompare(v, val)) {
        sat = s;
        val = v;
        svPanel->update();
        emit svPanel->selectedColorChanged(svPanel->selectedColor());
    }
}
