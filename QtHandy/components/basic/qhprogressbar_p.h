#ifndef QHPROGRESSBAR_P_H
#define QHPROGRESSBAR_P_H

#include "qhprogressbar.h"

class QhProgressBarPrivate : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhProgressBarPrivate)

public:
    QhProgressBarPrivate(QhProgressBar *p);
    ~QhProgressBarPrivate();

    bool bRoundedCorner = false;
    QColor background = QColor(0x12, 0x57, 0x60);
    QColor chunkBackground = QColor(0x32, 0xE7, 0xFF);

private:
    QhProgressBar *p = nullptr;
};

#endif // QHPROGRESSBAR_P_H
