#include "qhradarchart.h"
#include "qhradarchart_p.h"
#include <QToolTip>
#include <QApplication>
#include <QPainter>
#include <QtMath>
#include <QMouseEvent>
#include <QDebug>
#include "qhmathutil.h"

QhRadarChart::QhRadarChart(QWidget *parent) : QWidget(parent), d(new QhRadarChartPrivate)
{
    this->setMouseTracking(true);
}

QhRadarChart::~QhRadarChart()
{
}

void QhRadarChart::setType(int type)
{
    d->type = type;
    this->update();
}

void QhRadarChart::setData(const QList<DataItem> &datas)
{
    d->datas = datas;
    this->update();
}

void QhRadarChart::setTextPen(const QPen &pen)
{
    d->textPen = pen;
    this->update();
}

void QhRadarChart::setGridPen(const QPen &pen)
{
    d->gridPen = pen;
    this->update();
}

void QhRadarChart::setDataPen(const QPen &pen)
{
    d->dataPen = pen;
    this->update();
}

int QhRadarChart::type() const
{
    return d->type;
}

const QList<QhRadarChart::DataItem> &QhRadarChart::data() const
{
    return d->datas;
}

QPen QhRadarChart::textPen() const
{
    return d->textPen;
}

QPen QhRadarChart::gridPen() const
{
    return d->gridPen;
}

QPen QhRadarChart::dataPen() const
{
    return d->dataPen;
}

void QhRadarChart::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
    if (d->type != DataDistribution)
        return;

    d->textPosList.clear();
    if (d->datas.size() < 3)
        return;

    qreal h = this->height();
    qreal w = this->width();
    qreal cx = w / 2.0;
    qreal cy = h / 2.0;

    QFontMetricsF fm(this->font());

    // 平均角度（从顶部中心开始绘制）
    qreal itemAngle = 360.0 / d->datas.size();

    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing);

    // 获取数据最大值
    qreal dataMax = 0.0;
    for (int n = 0; n < d->datas.size(); ++n) {
        if (n == 0)
            dataMax = d->datas.at(0).value;
        else if (dataMax < d->datas.at(n).value)
            dataMax = d->datas.at(n).value;
    }

    int gridLayers = 5;                                          // 网格层数
    qreal th = fm.height();                                      // 文本高度
    qreal gridSize = qMin((h - th * 2) / 2.0, w / 2.0);          // 网格最大半径
    qreal gridSingleSize = gridSize / (qreal)gridLayers;         //
    qreal dataSizeRatio = (gridSize - gridSingleSize) / dataMax; // 数据半径与值的比例
    QVector<QVector<QPointF> > gridLayerPts(gridLayers);         // 网格层的点坐标
    QVector<QPointF> dataPts;                                    // 网格数据
    qreal layerRadius = gridSize;                                // 网格半径

    p.setPen(d->textPen);

    for (int n = 0; n < gridLayers; ++n) {
        for (int m = 0; m < d->datas.size(); ++m) {
            const auto &item = d->datas.at(m);
            qreal angle = itemAngle * m - 180;
            qreal x = cx + QhMathUtil::Triangle::calcOppositeBy_H_O_Angle(layerRadius, angle);
            qreal y = cy + QhMathUtil::Triangle::calcAdjacentBy_H_O_Angle(layerRadius, angle);
            gridLayerPts[n].append(QPointF(x, y));

            if (n == 0) {
                qreal valueRadius = item.value * dataSizeRatio;
                valueRadius += gridSize / (qreal)gridLayers;
                qreal vx = cx + QhMathUtil::Triangle::calcOppositeBy_H_O_Angle(valueRadius, angle);
                qreal vy = cy + QhMathUtil::Triangle::calcAdjacentBy_H_O_Angle(valueRadius, angle);
                dataPts.append(QPointF(vx, vy));

                // p.drawLine(QPointF(vx, vy), QPointF(cx, cy));

                qreal tLen = fm.horizontalAdvance(item.name);
                qreal tHeight = th;
                qreal tx = x;
                qreal ty = y - tHeight / 2.0f;
                if (angle < 0) {
                    tx = x - tLen;
                }
                if ((angle <= -180 && angle > -270) || (angle > 90 && angle <= 180)) {
                    ty = y - tHeight;
                }
                if (angle == -180 || angle == 0) {
                    tx = x - tLen / 2.0f;
                }
                auto textItem = QhRadarChartPrivate::TextItem::Ptr::create();
                textItem->rtf = QRectF(tx, ty, tLen, tHeight);
                textItem->text = item.name;
                textItem->value = item.value;
                p.drawText(textItem->rtf, Qt::AlignCenter, textItem->text);
                d->textPosList.append(textItem);
            }
        }
        layerRadius -= gridSingleSize;
    }

    // 绘制网格线
    for (int n = 0; n < gridLayers; ++n) {
        p.setPen(d->gridPen);
        p.drawPolygon(QPolygonF(gridLayerPts[n]));
    }

    dataPts.append(dataPts.first());
    // 填充多边形
    static QVector<QColor> s_color = {QColor(0xFF, 0x3B, 0x3C, 0xEF), QColor(0xF7, 0xA4, 0x32, 0xEF),
        QColor(0xFF, 0xE7, 0x37, 0xEF), QColor(0x5B, 0xFF, 0x37, 0xEF), QColor(0x37, 0xE1, 0xFF, 0xEF),
        QColor(0x37, 0x61, 0xFF, 0xEF), QColor(0x6A, 0x37, 0xFF, 0xEF), QColor(0xFF, 0x3B, 0x3C, 0xEF),
        QColor(0xF7, 0xA4, 0x32, 0xEF), QColor(0xFF, 0xE7, 0x37, 0xEF)};
    qreal nm = 1.0f;
    qreal space = 1.0f / (d->datas.size() * nm);
    QConicalGradient radiaColor;
    radiaColor.setCenter(cx, cy);
    radiaColor.setAngle(itemAngle / nm);
    // radiaColor.setAngle(-180);
    for (int n = 0, cn = 0; n < d->datas.size() * nm; ++n, ++cn) {
        qreal pos = space * n;
        if (cn >= s_color.size())
            cn = 0;
        radiaColor.setColorAt(pos, s_color.at(cn));
    }
    QPainterPath path;
    path.addPolygon(QPolygonF(dataPts));
    p.fillPath(path, QBrush(radiaColor));

    // 绘制数值多边形（最里面一层值为0）
    // p.setPen(d->dataPen);
    // p.drawPolygon(QPolygonF(dataPts));
}

void QhRadarChart::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);

    for (auto &item : d->textPosList) {
        if (item->rtf.contains(event->pos())) {
            // QToolTip::hideText();
            QToolTip::showText(this->mapToGlobal(event->pos()), QString("%1: %2").arg(item->text).arg(item->value));
            break;
        }
    }
}

QhRadarChartPrivate::QhRadarChartPrivate()
{
}

QhRadarChartPrivate::~QhRadarChartPrivate()
{
}
