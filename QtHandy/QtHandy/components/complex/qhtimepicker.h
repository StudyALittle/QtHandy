#ifndef QHTIMEPICKER_H
#define QHTIMEPICKER_H

#include <QWidget>
#include <qhfloating.h>
#include "QH_global.h"

class QhTimePickerPrivate;

class QTHANDY_EXPORT QhTimePicker: public QhFloating
{
    Q_OBJECT

public:
    QhTimePicker(QWidget *parent = nullptr);
    ~QhTimePicker();

    QTime time();

    void setTime(const QTime &time);

signals:
    void timed(const QTime &time);

private:
    QhTimePickerPrivate *d;
    Q_DISABLE_COPY(QhTimePicker)
    friend class QhTimePickerPrivate;
};

#endif // QHTIMEPICKER_H
