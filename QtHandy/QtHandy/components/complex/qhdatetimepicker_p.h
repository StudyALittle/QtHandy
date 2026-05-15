#ifndef QHDATETIMEPICKER_P_H
#define QHDATETIMEPICKER_P_H

#include <QWidget>
#include <QPushButton>
#include "qhlineedit.h"
#include "qhdatepicker.h"
#include "qhdatetimepicker.h"
#include "qhtimepicker.h"
#include "qhdatepicker_p.h"

class QhDateTimePickerPrivate: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhDateTimePickerPrivate)

public:
    QhDateTimePickerPrivate(QhDateTimePicker *q);
    ~QhDateTimePickerPrivate();

    void init(bool bRange);
    void createTimePicker(QhTimePicker **timePicker, QhLineEdit *timeEidt,
        bool bEnd = false, int width = 0);

    QDateTime dateTime() const;
    QPair<QDateTime, QDateTime> dateTimeRange() const;

    void setDateTime(const QDateTime &dateTime);
    void setDateTimeRange(const QDateTime &dateTimeStart, const QDateTime &dateTimeEnd);

private:
    QhDateTimePicker *const ptr;

    QWidget *widgetTop = nullptr;
    QhLineEdit *editDateStart = nullptr;
    QhLineEdit *editTimeStart = nullptr;
    QhLineEdit *editDateEnd = nullptr;
    QhLineEdit *editTimeEnd = nullptr;

    QhDatePicker *datePicker = nullptr;

    QWidget *widgetBottom = nullptr;
    QPushButton *buttonOk = nullptr;
    QPushButton *buttonCancel = nullptr;

    QhTimePicker *timePickerStart = nullptr;
    QhTimePicker *timePickerEnd = nullptr;

    QString strFormatDate = "yyyy-MM-dd";
    QString strFormatTime = "HH:mm:ss";
};

#endif // QHDATETIMEPICKER_P_H
