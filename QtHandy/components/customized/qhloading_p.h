#ifndef QHLOADING_P_H
#define QHLOADING_P_H

#include <QTimer>
#include <QElapsedTimer>
#include "qhloading.h"

class QhLoadingPrivate: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhLoadingPrivate)

public:
    explicit QhLoadingPrivate(QhLoading *loading);
    ~QhLoadingPrivate();

    enum LState { StateWait, StateShow, StateClose };

    void init();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

public:
    QhLoading *loading;
    QWidget *installEventWidget = nullptr;

    QTimer timer;
    QElapsedTimer etimer;
    LState state;
    qint64 nBeginShowTime;
    int nWaitShowTimeSpace;
    int nMinShowTimeSpace;
};

#endif // QHLOADING_P_H
