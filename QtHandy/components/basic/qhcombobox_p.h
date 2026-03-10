#ifndef QHCOMBOBOX_P_H
#define QHCOMBOBOX_P_H

#include "qhcombobox.h"

class QhComboBoxPrivate: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhComboBoxPrivate)

public:
    QhComboBoxPrivate() {}

    bool bModifyByWheel = false;
};

#endif // QHCOMBOBOX_P_H
