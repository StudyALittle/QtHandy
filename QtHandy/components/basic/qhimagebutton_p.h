#ifndef QHIMAGEBUTTON_P_H
#define QHIMAGEBUTTON_P_H

#include <QLabel>
#include "qhqss.h"
#include "qhimagebutton.h"

class QhImageButtonPrivate: public QObject
{
    Q_OBJECT

public:
    QhImageButtonPrivate(QhImageButton *q);
    ~QhImageButtonPrivate();

    void init();
    void qssReloaded();
    QhQss::PseudoState currentState(QStyleOptionButton &option);

    QhImageButton *ptr;

    QSize leftIconSize = QSize(16, 16);
    QString leftIconPath;
    QSize rightIconSize = QSize(16, 16);
    QString rightIconPath;

    QLabel *iconLeft = nullptr;
    QLabel *iconRight = nullptr;

    int textOffset = 6;
    QString text;
    // QLabel *labelText = nullptr;

    /// Qss style parse
    QhQss *handyQss = nullptr;
};

#endif // QHIMAGEBUTTON_P_H
