#ifndef QHSVPANEL_P_H
#define QHSVPANEL_P_H

#include "qhsvpanel.h"

class QhSVPanelPrivate: public QObject
{
    Q_OBJECT

public:
    QhSVPanelPrivate(QhSVPanel *svPanel);
    ~QhSVPanelPrivate();

    void updateFromPos(const QPoint &pos);

    QhSVPanel *svPanel;

    // 指示器（白色圆环）半径
    qreal ringRadius = 14;

    qreal hue = 0.0;   // 0.0 ~ 1.0
    qreal sat = 1.0;   // 0.0 ~ 1.0
    qreal val = 1.0;   // 0.0 ~ 1.0

    QRectF panelRect;
    QPointF selectedPos;
};

#endif // QHSVPANEL_P_H
