#ifndef QHWIDGETZOOM_P_H
#define QHWIDGETZOOM_P_H

#include "qhwidgetzoom.h"

class QhWidgetZoomPrivate: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhWidgetZoomPrivate)

public:
    QhWidgetZoomPrivate(QhWidgetZoom *q);
    ~QhWidgetZoomPrivate();

    void zoomSizeChild(QWidget *w, qreal scale);
    void zoomSizeChild(QLayout *ly, qreal scale);

    QhWidgetZoom *ptr = nullptr;
    qreal maxZoom = 10;
    qreal zoom = 1.0;
    bool enableZoom = false;

    QList<QWidget*> zoomedWidgets;
    QList<QLayout*> zoomedLayouts;
};

#endif // QHWIDGETZOOM_P_H
