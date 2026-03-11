#ifndef QHMESSAGEBOX_P_H
#define QHMESSAGEBOX_P_H

#include <QLabel>
#include "qhmessagebox.h"

class QhMessageBoxPrivate: public QObject
{
    Q_OBJECT

    Q_DISABLE_COPY(QhMessageBoxPrivate)
    Q_DECLARE_PUBLIC(QhMessageBox)

public:
    QhMessageBoxPrivate(QhMessageBox *q):
        q_ptr(q) {}

    void init();

    QhMessageBox::Icon icon;
    QWidget *widgetContent = nullptr;
    QLabel *labelContent = nullptr;

    static int s_nBorderRadius;
    static int s_nShadowWidth;

private:
    QhMessageBox *const q_ptr;
};

#endif // QHMESSAGEBOX_P_H
