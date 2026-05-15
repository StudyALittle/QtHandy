#ifndef QHRADARCHART_P_H
#define QHRADARCHART_P_H

#include <QPen>
#include "qhradarchart.h"

class QhRadarChartPrivate : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhRadarChartPrivate)

public:
    QhRadarChartPrivate();
    ~QhRadarChartPrivate();

    struct TextItem {
        using Ptr = QSharedPointer<TextItem>;
        QString text;
        QRectF rtf;
        qreal value;
    };

    int type = QhRadarChart::DataDistribution;

    QList<QhRadarChart::DataItem> datas;
    QList<TextItem::Ptr> textPosList;

    QPen textPen = QPen(QColor(0x00, 0x00, 0x00));       // 文本
    QPen gridPen = QPen(QColor(0x20, 0xA1, 0xCA));       // 网格
    QPen dataPen = QPen(QColor(0xD2, 0x59, 0x39, 0xD4)); // 数据
};

#endif // QHRADARCHART_P_H
