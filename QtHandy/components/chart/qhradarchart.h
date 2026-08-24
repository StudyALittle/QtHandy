#ifndef QHRADARCHART_H
#define QHRADARCHART_H

#include <QWidget>
#include "QH_global.h"

class QhRadarChartPrivate;

class QTHANDY_EXPORT QhRadarChart : public QWidget
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhRadarChart)

public:
    /// @brief 类型（不同雷达图绘制风格可能不一样）
    enum Type {
        DataDistribution, // 数据分布（默认）
        // 实现其他类型的
    };

    struct DataItem {
        QString name;
        qreal value;
    };

    QhRadarChart(QWidget *parent = nullptr);
    ~QhRadarChart();

    void setType(int type);
    void setData(const QList<DataItem> &datas);

    void setTextPen(const QPen &pen);
    void setGridPen(const QPen &pen);
    void setDataPen(const QPen &pen);

    int type() const;
    const QList<DataItem> &data() const;
    QPen textPen() const;
    QPen gridPen() const;
    QPen dataPen() const;

protected:
    void paintEvent(QPaintEvent *e) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // QHRADARCHART_H
