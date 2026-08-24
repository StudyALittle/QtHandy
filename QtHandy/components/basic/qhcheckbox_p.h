#ifndef QHCHECKBOX_P_H
#define QHCHECKBOX_P_H

#include "qhcheckbox.h"

class QhCheckBoxPrivate: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhCheckBoxPrivate)

public:
    explicit QhCheckBoxPrivate() {}

    bool bLockState = false;
    bool bSelectOutsideText = false; // 在文本外是否能选中
};

#endif // QHCHECKBOX_P_H
