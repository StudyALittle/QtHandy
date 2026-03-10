#ifndef QHPROGRESSBAR_H
#define QHPROGRESSBAR_H

#include <QProgressBar>
#include "QH_global.h"

class QTHANDY_EXPORT QhProgressBar: public QProgressBar
{
    Q_OBJECT

public:
    QhProgressBar(QWidget *parent = nullptr);
};

#endif // QHPROGRESSBAR_H
