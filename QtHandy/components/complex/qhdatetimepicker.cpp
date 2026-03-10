#include "qhdatetimepicker.h"
#include "qhdatetimepicker_p.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

QhDateTimePicker::QhDateTimePicker(bool bRange, QWidget *parent):
    QhFloating(parent),
    d(new QhDateTimePickerPrivate(this))
{
    d->init(bRange);
}

QhDateTimePicker::~QhDateTimePicker()
{

}

QDateTime QhDateTimePicker::dateTime() const
{
    return d->dateTime();
}

QPair<QDateTime, QDateTime> QhDateTimePicker::dateTimeRange() const
{
    return d->dateTimeRange();
}

void QhDateTimePicker::setDateTime(const QDateTime &dateTime)
{
    d->setDateTime(dateTime);
}

void QhDateTimePicker::setDateTime(const QhDateTimePicker::DTRange &dtrange)
{
    d->setDateTimeRange(dtrange.first, dtrange.second);
}

QString QhDateTimePicker::dateTimesToString(const DTRange &dtms, const QString &content, const QString &format)
{
    return content.arg(dtms.first.toString(format), dtms.second.toString(format));
}

QhDateTimePickerPrivate::QhDateTimePickerPrivate(QhDateTimePicker *q):
    ptr(q)
{

}

QhDateTimePickerPrivate::~QhDateTimePickerPrivate()
{

}

void QhDateTimePickerPrivate::init(bool bRange)
{
    widgetTop = new QWidget;
    widgetTop->setObjectName("WidgetTime");
    auto *topLy = new QHBoxLayout(widgetTop);

    editDateStart = new QhLineEdit;
    editDateStart->leftWidget()->setVisible(false);
    editDateStart->rightWidget()->setVisible(false);
    editDateStart->setReadOnly(true);
    editDateStart->setPlaceholderText("select date");

    editTimeStart = new QhLineEdit;
    editTimeStart->leftWidget()->setVisible(false);
    editTimeStart->rightWidget()->setVisible(false);
    editTimeStart->setReadOnly(true);
    editTimeStart->setPlaceholderText("select time");

    topLy->addWidget(editDateStart);
    topLy->addWidget(editTimeStart);

    if (bRange) {
        editDateEnd = new QhLineEdit;
        editDateEnd->leftWidget()->setVisible(false);
        editDateEnd->rightWidget()->setVisible(false);
        editDateEnd->setReadOnly(true);
        editDateEnd->setPlaceholderText("select date");

        editTimeEnd = new QhLineEdit;
        editTimeEnd->leftWidget()->setVisible(false);
        editTimeEnd->rightWidget()->setVisible(false);
        editTimeEnd->setReadOnly(true);
        editTimeEnd->setPlaceholderText("select time");

        topLy->addWidget(editDateEnd);
        topLy->addWidget(editTimeEnd);
    }

    datePicker = new QhDatePicker(false, bRange);

    if (!bRange) {
        connect(datePicker, &QhDatePicker::dated, this, [this](const QDate &date) {
            editDateStart->setText(date.toString(strFormatDate));
        });

        connect(editTimeStart, &QhLineEdit::clicked, this, [this]() {
            createTimePicker(&timePickerStart, editTimeStart, true,
               ptr->width() - (ptr->width() / 3));
        });
    } else {
        connect(datePicker, &QhDatePicker::dateRanged, this, [this](const QPair<QDate, QDate> &dateRange) {
            editDateStart->setText(dateRange.first.toString(strFormatDate));
            editDateEnd->setText(dateRange.second.toString(strFormatDate));
        });

        connect(editTimeStart, &QhLineEdit::clicked, this, [this]() {
            createTimePicker(&timePickerStart, editTimeStart, false,
                ptr->width() / 2 - (ptr->width() / 6));
        });

        connect(editTimeEnd, &QhLineEdit::clicked, this, [this]() {
            createTimePicker(&timePickerEnd, editTimeEnd, true,
                ptr->width() / 2 - (ptr->width() / 6));
        });
    }

    widgetBottom = new QWidget;
    widgetBottom->setObjectName("WidgetBottom");

    auto *bottomLy = new QHBoxLayout(widgetBottom);
    buttonOk = new QPushButton(tr("ok"));
    buttonCancel = new QPushButton(tr("cancel"));
    bottomLy->addStretch(1);
    bottomLy->addWidget(buttonCancel);
    bottomLy->addWidget(buttonOk);

    connect(buttonCancel, &QPushButton::clicked, this, [this]() {
        ptr->close();
    });

    if (!bRange) {
        connect(buttonOk, &QPushButton::clicked, this, [this]() {
            emit ptr->datetimed(dateTime());
            ptr->close();
        });
    } else {
        connect(buttonOk, &QPushButton::clicked, this, [this]() {
            auto dtms = dateTimeRange();
            emit ptr->datetimeRanged({dtms.first, dtms.second});
            ptr->close();
        });
    }

    auto *ly = new QVBoxLayout(ptr);
    ly->addWidget(widgetTop);
    ly->addWidget(datePicker, 1);
    ly->addWidget(widgetBottom);
    ly->setSpacing(0);
    ly->setContentsMargins(0, 0, 0, 0);
}

void QhDateTimePickerPrivate::createTimePicker(QhTimePicker **timePicker,
    QhLineEdit *timeEidt, bool bEnd, int width)
{
    if (*timePicker)
        return;

    *timePicker = new QhTimePicker(ptr);

    connect(*timePicker, &QhTimePicker::timed, this, [this, timeEidt](const QTime &time) {
        timeEidt->setText(time.toString(strFormatTime));
    });
    connect(*timePicker, &QhTimePicker::closed, this, [timePicker]() {
        (*timePicker)->deleteLater();
        (*timePicker) = nullptr;
    });

    if (width <= 0)
        width = ptr->width() / 2;

    (*timePicker)->setIgnoreWidgets({timeEidt});
    (*timePicker)->setTime(dateTime().time());
    (*timePicker)->move(ptr->mapFromGlobal(
        timeEidt->mapToGlobal(QPoint(
            bEnd ? (timeEidt->width() - width) : 0, timeEidt->height()))));
    (*timePicker)->resize(width, ptr->height() - widgetTop->height());
    (*timePicker)->open(QPoint());
}

QDateTime QhDateTimePickerPrivate::dateTime() const
{
    return QDateTime(
        QDate::fromString(editDateStart->text(), strFormatDate),
        QTime::fromString(editTimeStart->text(), strFormatTime));
}

QPair<QDateTime, QDateTime> QhDateTimePickerPrivate::dateTimeRange() const
{
    return {
        dateTime(),
        QDateTime(
            QDate::fromString(editDateEnd->text(), strFormatDate),
            QTime::fromString(editTimeEnd->text(), strFormatTime))
    };
}

void QhDateTimePickerPrivate::setDateTime(const QDateTime &dateTime)
{
    datePicker->setDate(dateTime.date());
    editDateStart->setText(dateTime.date().toString(strFormatDate));
    editTimeStart->setText(dateTime.time().toString(strFormatTime));
}

void QhDateTimePickerPrivate::setDateTimeRange(const QDateTime &dateTimeStart, const QDateTime &dateTimeEnd)
{
    datePicker->setDate({dateTimeStart.date(), dateTimeEnd.date()});

    editDateStart->setText(dateTimeStart.date().toString(strFormatDate));
    editTimeStart->setText(dateTimeStart.time().toString(strFormatTime));

    editDateEnd->setText(dateTimeEnd.date().toString(strFormatDate));
    editTimeEnd->setText(dateTimeEnd.time().toString(strFormatTime));
}
