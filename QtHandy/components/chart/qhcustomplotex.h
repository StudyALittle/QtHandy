#ifndef QHCUSTOMPLOTEX_H
#define QHCUSTOMPLOTEX_H

#include <QScrollBar>
#include <qcustomplot.h>
#include "QH_global.h"

class QhCustomPlotExPrivate;

class QhCustomPlotEx: public QCustomPlot
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhCustomPlotEx)

public:
    typedef QSharedPointer<QCPAxisTickerDateTime> TickerDateTime;
    typedef QSharedPointer<QCPAxisTickerText> TickerText;

    /// @brief x ticker type
    enum XTickerType { XText, XDateTime };

    /// @brief 柱状图数据
    struct BarData
    {
        double value;
        QString tick;
    };

    QhCustomPlotEx(XTickerType type,
        QScrollBar *hScrollBar = nullptr, QWidget *parent = nullptr);
    ~QhCustomPlotEx();

    /// @brief
    QCPBars *getBar(qint64 id) const;

    /// @brief
    QCPGraph *getGraph(qint64 id) const;

    QScrollBar *hScrollBar() const;
    QCPBarsGroup *barsGroup() const;

    TickerDateTime xTickerDateTime() const;
    TickerText xTickerText() const;

    void setXYAxisStyle();
    void setXYAxisStyle(
            const QColor &backgroundColor, const QColor &textColor,
            const QColor &tickColor, const QColor &tickLineColor,
            const QPen &tickPen, const QPen &tickLinePen);

    void setPageMaxCount(int cnt);

    QCPBars *createBar(qint64 id, const QString &name, const QColor &color,
        const QPen &pen = QPen(Qt::NoPen), int pxSize = 22);
    QCPGraph *createGraph(qint64 id, const QString &name, const QPen &pen);

    void initBarMouseMove(bool bShowName = true);
    void initGraphMouseMove();
};

class QhCustomPlotScrollBarEx: public QWidget
{
    Q_OBJECT

public:
    QhCustomPlotScrollBarEx(QhCustomPlotEx::XTickerType type, QWidget *parent = nullptr);
    ~QhCustomPlotScrollBarEx();

    QhCustomPlotEx *chart() const;

private:
    QhCustomPlotEx *customPlotEx = nullptr;
};

#endif // QHCUSTOMPLOTEX_H
