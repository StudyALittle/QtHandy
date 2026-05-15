#include "qhcustomplotex.h"
#include "qhcustomplotex_p.h"

QhCustomPlotEx::QhCustomPlotEx(
        XTickerType type, QScrollBar *hScrollBar, QWidget *parent):
    QCustomPlot(parent),
    d(new QhCustomPlotExPrivate(this))
{
    d->xTickerType = type;
    d->hScrollBar = hScrollBar;
    d->init();
}

QhCustomPlotEx::~QhCustomPlotEx()
{

}

QCPBars *QhCustomPlotEx::getBar(qint64 id) const
{
    for (auto *bar: d->bars) {
        if (bar->property("exchar_id").toInt() == id)
            return bar;
    }
    return nullptr;
}

QCPGraph *QhCustomPlotEx::getGraph(qint64 id) const
{
    for (auto *graph: d->graphs) {
        if (graph->property("exchar_id").toInt() == id)
            return graph;
    }
    return nullptr;
}

QScrollBar *QhCustomPlotEx::hScrollBar() const
{
    return d->hScrollBar;
}

QCPBarsGroup *QhCustomPlotEx::barsGroup() const
{
    return d->barsGroup;
}

QhCustomPlotEx::TickerDateTime QhCustomPlotEx::xTickerDateTime() const
{
    return d->xTickerDateTime;
}

QhCustomPlotEx::TickerText QhCustomPlotEx::xTickerText() const
{
    return d->xTickerText;
}

void QhCustomPlotEx::setXYAxisStyle()
{
    QColor backgroundColor = QColor(Qt::transparent);
    QColor textColor = QColor(0xBA, 0xD7, 0xFF);        // 文本颜色
    QColor tickColor = QColor(0x00, 0x72, 0xE8);        // 刻度颜色
    QColor tickLineColor = QColor(0x36, 0x50, 0x80);    // 刻度线条颜色
    QPen tickPen = QPen(tickColor, 1, Qt::SolidLine);
    QPen tickLinePen = QPen(tickLineColor, 1, Qt::DotLine);

    setXYAxisStyle(
        backgroundColor, textColor, tickColor,
        tickLineColor, tickPen, tickLinePen);
}

void QhCustomPlotEx::setXYAxisStyle(const QColor &backgroundColor, const QColor &textColor, const QColor &tickColor, const QColor &tickLineColor, const QPen &tickPen, const QPen &tickLinePen)
{
    this->legend->setVisible(false);

    this->setBackground(backgroundColor);
    // 设置x轴
    this->xAxis2->setVisible(false);
    this->xAxis2->setBasePen(Qt::NoPen);
    this->xAxis2->grid()->setVisible(false);
    this->xAxis2->grid()->setPen(QPen(Qt::NoPen));
    this->xAxis->setSubTicks(false);
    this->xAxis->setTickLabelColor(textColor);
    this->xAxis->setLabelColor(textColor);
    this->xAxis->setTickLabelFont(QFont(qApp->font().family(), 8));
    this->xAxis->setBasePen(tickLinePen);
    this->xAxis->grid()->setVisible(true);
    this->xAxis->grid()->setPen(QPen(Qt::NoPen));

    // 设置y轴
    this->yAxis2->setVisible(false);
    this->yAxis2->setTickPen(Qt::NoPen);
    this->yAxis2->grid()->setVisible(false);
    this->yAxis2->grid()->setPen(QPen(Qt::NoPen));
    this->yAxis->setTickLabelColor(textColor);
    this->yAxis->setLabelColor(textColor);
    this->yAxis->setTickLabelFont(QFont(qApp->font().family(), 8));
    this->yAxis->setBasePen(QPen(Qt::NoPen));
    this->yAxis->setTickPen(tickPen);
    this->yAxis->setSubTickPen(QPen(Qt::NoPen));
    this->yAxis->grid()->setVisible(true);
    this->yAxis->grid()->setPen(tickLinePen);
    this->yAxis->grid()->setSubGridVisible(false);
    this->yAxis->grid()->setSubGridPen(Qt::NoPen);
}

void QhCustomPlotEx::setPageMaxCount(int cnt)
{
    d->rangeParam.pageMaxCount = cnt;
}

QCPBars *QhCustomPlotEx::createBar(qint64 id, const QString &name, const QColor &color, const QPen &pen, int pxSize)
{
    auto *bar = new QCPBars(this->xAxis, this->yAxis);
    bar->setAntialiased(false);
    bar->setStackingGap(0);
    bar->setName(name);
    bar->setPen(pen);
    bar->setBrush(color);
    bar->setWidthType(QCPBars::wtAbsolute);
    bar->setWidth(pxSize);
    bar->setProperty("exchar_id", id);
    d->bars.append(bar);
    return bar;
}

QCPGraph *QhCustomPlotEx::createGraph(qint64 id, const QString &name, const QPen &pen)
{
    auto *graph = this->addGraph();
    graph->setName(name);
    graph->setLineStyle(QCPGraph::lsLine);
    graph->setPen(pen);
    graph->setProperty("exchar_id", id);
    d->graphs.append(graph);
    return graph;
}

void QhCustomPlotEx::initBarMouseMove(bool bShowName)
{
//    initLabel();

    connect(this, &QCustomPlot::mouseMove, this, [=](QMouseEvent *event) {
        double x = event->pos().x();
        double y = event->pos().y();
        double mx = this->xAxis->pixelToCoord(event->pos().x());
        double my = this->yAxis->pixelToCoord(event->pos().y());

        // 遍历多个柱状图
        for (auto itBars = d->bars.begin(); itBars != d->bars.end(); ++itBars) {
            auto *bars = *itBars;
            QCPAxisRect *rect = this->xAxis->axisRect();
            double barsWidth = bars->width();
            double halfWidth = barsWidth / 2.0;

            QCPBars *barBelow = bars->barBelow(); // 下方
            QCPBars *barAbove = bars->barAbove(); // 上方

            // qDebug() << "y: " << rect->bottom() << " -- h: " << this->height();

            auto dataContainer = bars->data();
            int n = 0;
            for (auto itData = dataContainer->constBegin(); itData != dataContainer->constEnd(); ++itData, ++n) {
                // 获取柱状图的位置
                auto pos = bars->dataPixelPosition(n);
                auto barMx = this->xAxis->pixelToCoord(pos.x());
                auto barMy = this->yAxis->pixelToCoord(pos.y());

                if (bars->widthType() != QCPBars::wtAbsolute) {
                    if (barBelow) {
                        // y要大于下方柱子的高度
                        auto posBelow = barBelow->dataPixelPosition(n);
                        auto barBelowMy = this->yAxis->pixelToCoord(posBelow.y());
                        if (my <= barBelowMy)
                            continue;
                    } else if (barAbove) {
                        // y要小于上方柱子
                        auto posAbove = barAbove->dataPixelPosition(n);
                        auto barAboveMy = this->yAxis->pixelToCoord(posAbove.y());
                        if (my >= barAboveMy)
                            continue;
                    }

                    if (mx >= barMx - halfWidth && mx <= barMx + halfWidth
                            && my >= 0 && my <= barMy) {
                        QString text;
                        if (bShowName)
                            text = QString("%1: ").arg(bars->name());
                        text += QString::number(itData->value);
                        QToolTip::showText(mapToGlobal(QPoint(event->pos().x(), event->pos().y())), text, this);
                        return;
                    }
                } else {
                    mx = x; my = y; barMx = pos.x(); barMy = pos.y();

                    if (barBelow) {
                        // y要小于下方柱子的高度
                        auto posBelow = barBelow->dataPixelPosition(n);
                        if (my > posBelow.y())
                            continue;
                    } else if (barAbove) {
                        // y要大于上方柱子
                        auto posAbove = barAbove->dataPixelPosition(n);
                        if (my < posAbove.y())
                            continue;
                    }

                    if (mx >= barMx - halfWidth && mx <= barMx + halfWidth
                            && my <= rect->bottom() && my >= barMy) {
                        QString text;
                        if (bShowName)
                            text = QString("%1: ").arg(bars->name());
                        text += QString::number(itData->value);
                        QToolTip::showText(mapToGlobal(QPoint(event->pos().x(), event->pos().y())), text, this);
                        return;
                    }
                }
            }
        }
    });
}

void QhCustomPlotEx::initGraphMouseMove()
{
//    m_tracer = new QCPItemTracer(this);
//    m_tracer->setStyle(QCPItemTracer::tsCircle);
//    m_tracer->setSize(6);

//    initLabel();

    connect(this, &QCustomPlot::mouseMove, this, [=](QMouseEvent *event) {
        double xVal = this->xAxis->pixelToCoord(event->pos().x());
        // double yVal = this->yAxis->pixelToCoord(event->pos().y());

        QString name;
        QCPGraph *closestGraph = nullptr;
        double minDist = 1e12;
        double key = 0, value = 0;

        for (int i = 0; i < this->graphCount(); i++) {
            QCPGraph *g = this->graph(i);
            if (g->data()->isEmpty())
                continue;

            auto it = g->data()->findBegin(xVal);
            if (it == g->data()->end())
                continue;

            double y = it->value;
            double py = this->yAxis->coordToPixel(y);
            double my = event->pos().y();
            double dist = qAbs(py - my);

            if (dist < minDist) {
                minDist = dist;
                closestGraph = g;
                key = it->key;
                value = y;
                name = g->name();
            }
        }

        if (!closestGraph)
            return;

//        m_tracer->setVisible(true);

//        m_tracer->setGraph(closestGraph);
//        m_tracer->setGraphKey(key);
//        m_tracer->setInterpolating(true);
//        m_tracer->updatePosition();

//        m_label->position->setCoords(key, value);
//        m_label->setText(QString("%1").arg(value, 0, 'f', 2));

        QToolTip::showText(mapToGlobal(QPoint(event->pos().x(), event->pos().y())),
            QString("%1: %2").arg(name).arg(value, 0, 'f', 2), this);

//        m_tracer->setPen(QPen(Qt::red));
//        m_tracer->setBrush(Qt::red);

        this->replot(QCustomPlot::rpQueuedReplot);
    });
}

QhCustomPlotExPrivate::QhCustomPlotExPrivate(QhCustomPlotEx *q):
    ptr(q)
{

}

QhCustomPlotExPrivate::~QhCustomPlotExPrivate()
{

}

void QhCustomPlotExPrivate::init()
{

}

QhCustomPlotScrollBarEx::QhCustomPlotScrollBarEx(QhCustomPlotEx::XTickerType type, QWidget *parent)
{
    auto *scrollBar = new QScrollBar(Qt::Horizontal);
    customPlotEx = new QhCustomPlotEx(type, scrollBar);

    auto *ly = new QVBoxLayout(this);
    ly->addWidget(customPlotEx, 1);
    ly->addWidget(scrollBar);
    ly->setContentsMargins(0, 0, 0, 0);
    ly->setSpacing(0);
}

QhCustomPlotScrollBarEx::~QhCustomPlotScrollBarEx()
{

}

QhCustomPlotEx *QhCustomPlotScrollBarEx::chart() const
{
    return customPlotEx;
}
