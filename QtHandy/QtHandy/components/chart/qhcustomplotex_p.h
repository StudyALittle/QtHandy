#ifndef QHCUSTOMPLOTEX_P_H
#define QHCUSTOMPLOTEX_P_H

#include "qhcustomplotex.h"

class QhCustomPlotExPrivate: public QObject
{
    Q_OBJECT

public:
    QhCustomPlotExPrivate(QhCustomPlotEx *q);
    ~QhCustomPlotExPrivate();

    void init();

    struct RangeParam
    {
        int pageMaxCount = 4;
        qreal xRangeMin = 0.0;
        qreal xRangeMax = 0.0;
        qreal yRangeMax = 0.0;
        qreal xScrollRatio = 0.0;
        qreal xPageRange = 0.0;
    };

    QhCustomPlotEx *ptr = nullptr;

    QhCustomPlotEx::XTickerType xTickerType;

    RangeParam rangeParam;
    QScrollBar *hScrollBar = nullptr;
    QCPBarsGroup *barsGroup = nullptr;

    // 折线图集合
    QList<QCPGraph*> graphs;
    // 柱状图集合
    QList<QCPBars*> bars;

    // X轴时间刻度
    QhCustomPlotEx::TickerDateTime xTickerDateTime = nullptr;
    // X轴文本刻度
    QhCustomPlotEx::TickerText xTickerText = nullptr;
};

#endif // QHCUSTOMPLOTEX_P_H
