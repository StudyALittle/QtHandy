#ifndef QHWIDGETMOVERESIZE_H
#define QHWIDGETMOVERESIZE_H

#include <QObject>
#include <QEvent>
#include <QWidget>
#include "QH_global.h"

class QhWidgetMoveResizePrivate;
class QhFramelessWindow;

class QTHANDY_EXPORT QhWidgetMoveResize
{
public:
    QhWidgetMoveResize(QhFramelessWindow *fwidget);
    ~QhWidgetMoveResize();

    bool proccessEvent(QEvent *event);
    void windowsNativeEventMove(void *message);
    void moveResize(const QPoint &pos);
    bool isInTitleBar(QPoint pos, bool *bInTitleWidget = nullptr);

    long calcMousePos(const QRect &rect, const QPoint &pos);

private:
    QhWidgetMoveResizePrivate *d;
    Q_DISABLE_COPY(QhWidgetMoveResize)
    friend class QhWidgetMoveResizePrivate;
};

#endif // QHWIDGETMOVERESIZE_H
