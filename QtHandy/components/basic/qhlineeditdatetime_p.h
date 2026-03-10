#ifndef QHLINEEDITDATETIME_P_H
#define QHLINEEDITDATETIME_P_H

#include "qhtimepicker.h"
#include "qhdatepicker.h"
#include "qhdatetimepicker.h"
#include "qhlineeditdatetime.h"
#include "qhlabel.h"

class QhLineEditDateTimePrivate: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhLineEditDateTimePrivate)

public:
    QhLineEditDateTimePrivate(QhLineEditDateTime *q);
    ~QhLineEditDateTimePrivate();

    void init();

    QhLineEditDateTime *ptr = nullptr;
    QhLineEditDateTime::Type dtType;
    QhLineEditDateTime::DTRange dtRange;

    QhLabel *labelStart = nullptr;
    QhLabel *labelTo = nullptr;
    QhLabel *labelEnd = nullptr;

    QhTimePicker *timePicker = nullptr;
    QhDatePicker *datePicker = nullptr;
    QhDateTimePicker *dateTimePicker = nullptr;

    QString strFormatDate = "yyyy-MM-dd";
    QString strFormatTime = "HH:mm:ss";

public slots:
    void onOpenPicker();

public:
    void createDatePicker();
    void createDateTimePicker();
};

#endif // QHLINEEDITDATETIME_P_H
