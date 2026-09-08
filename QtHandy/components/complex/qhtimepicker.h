#ifndef QHTIMEPICKER_H
#define QHTIMEPICKER_H

#include <QWidget>
#include <qhfloating.h>
#include "QH_global.h"

class QhTimePickerPrivate;

class QTHANDY_EXPORT QhTimePicker: public QhFloating
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhTimePicker)

public:
    QhTimePicker(QWidget *parent = nullptr);
    ~QhTimePicker();

    QTime time();

    void setTime(const QTime &time);

signals:
    void timed(const QTime &time);
};

#endif // QHTIMEPICKER_H
