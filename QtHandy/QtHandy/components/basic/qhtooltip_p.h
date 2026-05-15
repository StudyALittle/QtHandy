#ifndef QHTOOLTIP_P_H
#define QHTOOLTIP_P_H

#include <QBasicTimer>
#include "qhtooltip.h"

class QhToolTipPrivate : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhToolTipPrivate)

public:
    QhToolTipPrivate(QhToolTip *toolTip);
    ~QhToolTipPrivate();

    struct ShowInfo {
        QWidget *w = nullptr;
        QPoint pos = QPoint();
        QRect rect;
        QhToolTip::Placement placement;
        QString text;
        int msecDisplayTime = 0;

        void clear();
    };

    static QhToolTip *s_toolTip;
    QhToolTip *toolTip = nullptr;
    ShowInfo showInfo;
    QBasicTimer hideTimer, expireTimer;

    void init();
    static void showText(QWidget *w, const QPoint &pos, QhToolTip::Placement placement, const QRect &rect,
        const QString &text, int msecDisplayTime);

    void hideTip();
    void hideTipImmediately();
    void restartExpireTimer(int msecDisplayTime);

    void timerEvent(QTimerEvent *e) override;
    bool eventFilter(QObject *o, QEvent *e) override;
};

#endif // QHTOOLTIP_P_H
