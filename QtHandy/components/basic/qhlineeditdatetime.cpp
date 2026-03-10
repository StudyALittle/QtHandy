#include "qhlineeditdatetime.h"
#include "qhlineeditdatetime_p.h"
#include <QLayout>

QhLineEditDateTime::QhLineEditDateTime(Type type, QWidget *parent):
    QhLineEdit(parent), d(new QhLineEditDateTimePrivate(this))
{
    d->dtType = type;
    d->init();
}

QhLineEditDateTime::~QhLineEditDateTime()
{

}

QDateTime QhLineEditDateTime::dateTime() const
{
    return d->dtRange.first;
}

QhLineEditDateTime::DTRange QhLineEditDateTime::dateTimeRange() const
{
    return d->dtRange;
}

QDate QhLineEditDateTime::date() const
{
    return dateTime().date();
}

QhLineEditDateTime::DRange QhLineEditDateTime::dateRange() const
{
    return { d->dtRange.first.date(), d->dtRange.second.date() };
}

QTime QhLineEditDateTime::time() const
{
    return dateTime().time();
}

QhLineEditDateTime::TRange QhLineEditDateTime::timeRange() const
{
    return { d->dtRange.first.time(), d->dtRange.second.time() };
}

void QhLineEditDateTime::setDateTime(const QDateTime &dateTime)
{
    d->dtRange = {dateTime, dateTime};
    this->setText(dateTime.toString(d->strFormatDate + " " + d->strFormatTime));
}

void QhLineEditDateTime::setDateTime(const DTRange &dtrange)
{
    d->dtRange = dtrange;
    if (d->labelStart)
        d->labelStart->setText(dtrange.first.toString(d->strFormatDate + " " + d->strFormatTime));
    if (d->labelEnd)
        d->labelEnd->setText(dtrange.second.toString(d->strFormatDate + " " + d->strFormatTime));
}

void QhLineEditDateTime::setDate(const DRange &drange)
{
    d->dtRange = {QDateTime(drange.first, QTime::currentTime()),
                 QDateTime(drange.second, QTime::currentTime())};
    if (d->labelStart)
        d->labelStart->setText(drange.first.toString(d->strFormatDate));
    if (d->labelEnd)
        d->labelEnd->setText(drange.second.toString(d->strFormatDate));
}

void QhLineEditDateTime::setDate(const QDate &date)
{
    d->dtRange = {QDateTime(date, QTime::currentTime()), QDateTime()};
    this->setText(date.toString(d->strFormatDate));
}

void QhLineEditDateTime::setTime(const TRange &trange)
{
    d->dtRange = {QDateTime(QDate::currentDate(), trange.first),
                 QDateTime(QDate::currentDate(), trange.second)};
    if (d->labelStart)
        d->labelStart->setText(trange.first.toString(d->strFormatTime));
    if (d->labelEnd)
        d->labelEnd->setText(trange.second.toString(d->strFormatTime));
}

void QhLineEditDateTime::setTime(const QTime &time)
{
    setDateTime(QDateTime(QDate::currentDate(), time));
    this->setText(time.toString(d->strFormatTime));
}

QhLineEditDateTimePrivate::QhLineEditDateTimePrivate(QhLineEditDateTime *q):
    ptr(q)
{

}

QhLineEditDateTimePrivate::~QhLineEditDateTimePrivate()
{

}

void QhLineEditDateTimePrivate::init()
{
    ptr->leftWidget()->setVisible(true);
    ptr->rightWidget()->setVisible(true);

    ptr->leftWidget()->layout()->setContentsMargins(12, 0, 0, 0);
    ptr->leftWidgetC<QhLineEditLeft*>()->label()->setFixedSize(20, 20);

    ptr->rightWidget()->layout()->setContentsMargins(0, 0, 12, 0);
    ptr->rightWidgetC<QhLineEditRight*>()->button()->setFixedSize(20, 20);

    ptr->resetMargin();
    ptr->setReadOnly(true);

    switch (dtType) {
    case QhLineEditDateTime::TimeRange:
    case QhLineEditDateTime::DateRange:
    case QhLineEditDateTime::DateTimeRange: {
        auto *cly = new QHBoxLayout;
        labelStart = new QhLabel;
        labelStart->setMouseTracking(true);
        labelStart->setObjectName("LabelText");
        labelStart->setAlignment(Qt::AlignCenter);

        labelTo = new QhLabel(tr("to"));
        labelTo->setMouseTracking(true);
        labelTo->setObjectName("LabelTo");

        labelEnd = new QhLabel;
        labelEnd->setMouseTracking(true);
        labelEnd->setObjectName("LabelText");
        labelEnd->setAlignment(Qt::AlignCenter);

        cly->addWidget(labelStart, 1);
        cly->addWidget(labelTo);
        cly->addWidget(labelEnd, 1);
        cly->setContentsMargins(0, 0, 0, 0);
        cly->setSpacing(0);

        auto *mly = static_cast<QHBoxLayout*>(ptr->layout());
        mly->removeItem(mly->itemAt(1));
        mly->insertLayout(1, cly, 1);
        break;
    }
    default:
        break;
    }

    switch (dtType) {
    case QhLineEditDateTime::Time: {
        ptr->setPlaceholderText("select time");
        break;
    }
    case QhLineEditDateTime::TimeRange: {
        break;
    }
    case QhLineEditDateTime::Date: {
        ptr->setPlaceholderText("select date");
        break;
    }
    case QhLineEditDateTime::DateRange: {
        labelStart->setPlaceholderText(tr("start date"));
        labelEnd->setPlaceholderText(tr("end date"));
        break;
    }
    case QhLineEditDateTime::DateTime: {
        ptr->setPlaceholderText("select datetime");
        break;
    }
    case QhLineEditDateTime::DateTimeRange: {
        labelStart->setPlaceholderText(tr("start datetime"));
        labelEnd->setPlaceholderText(tr("end datetime"));
        break;
    }
    default:
        break;
    }

    connect(ptr->rightWidgetC<QhLineEditRight*>(), &QhLineEditRight::clicked,
            this, [this]() {
        dtRange = {QDateTime(), QDateTime()};
        if (labelStart)
            labelStart->clear();
        if (labelEnd)
            labelEnd->clear();
        ptr->clear();
    });
    connect(ptr, &QhLineEdit::clicked, this, &QhLineEditDateTimePrivate::onOpenPicker);
}

void QhLineEditDateTimePrivate::onOpenPicker()
{
    switch (dtType) {
    case QhLineEditDateTime::Time: {
        if (timePicker) {
            timePicker->close();
            timePicker->deleteLater();
            timePicker = nullptr;
            break;
        }

        timePicker = new QhTimePicker;
        timePicker->setIgnoreWidgets({ptr});
        connect(timePicker, &QhTimePicker::timed,
                this, [this](const QTime &time) {
            ptr->setTime(time);
            timePicker->deleteLater();
            timePicker = nullptr;
        });
        connect(timePicker, &QhTimePicker::closed,
                this, [this]() {
            timePicker->deleteLater();
            timePicker = nullptr;
        });

        timePicker->setTime(dtRange.first.time());
        timePicker->resize(260, 400);
        timePicker->open(ptr->mapToGlobal(QPoint(0, ptr->height())));
        break;
    }
    case QhLineEditDateTime::TimeRange: {
        break;
    }
    case QhLineEditDateTime::Date: {
        createDatePicker();
        break;
    }
    case QhLineEditDateTime::DateRange: {
        createDatePicker();
        break;
    }
    case QhLineEditDateTime::DateTime: {
        createDateTimePicker();
        break;
    }
    case QhLineEditDateTime::DateTimeRange: {
        createDateTimePicker();
        break;
    }
    default:
        break;
    }
}

void QhLineEditDateTimePrivate::createDatePicker()
{
    if (datePicker) {
        datePicker->close();
        datePicker->deleteLater();
        datePicker = nullptr;
        return;
    }

    bool bRange = (dtType == QhLineEditDateTime::DateRange);

    datePicker = new QhDatePicker(bRange);
    datePicker->setIgnoreWidgets({ptr});
    if (!bRange) {
        if (ptr->date().isValid())
            datePicker->setDate(ptr->date());
        connect(datePicker, &QhDatePicker::dated, this, [this](const QDate &date) {
            ptr->setDate(date);
            datePicker->deleteLater();
            datePicker = nullptr;
        });
    } else {
        if (ptr->dateRange().first.isValid())
            datePicker->setDate(ptr->dateRange());
        connect(datePicker, &QhDatePicker::dateRanged, this, [this](const QPair<QDate, QDate> &dateRange) {
            ptr->setDate(dateRange);
            datePicker->deleteLater();
            datePicker = nullptr;
        });
    }

    connect(datePicker, &QhDatePicker::closed,
            this, [this]() {
        datePicker->deleteLater();
        datePicker = nullptr;
    });

    datePicker->adjustSize();
    datePicker->open(ptr->mapToGlobal(QPoint(0, ptr->height())));
}

void QhLineEditDateTimePrivate::createDateTimePicker()
{
    if (dateTimePicker) {
        dateTimePicker->close();
        dateTimePicker->deleteLater();
        dateTimePicker = nullptr;
        return;
    }

    bool bRange = (dtType == QhLineEditDateTime::DateTimeRange);

    dateTimePicker = new QhDateTimePicker(bRange);
    dateTimePicker->setIgnoreWidgets({ptr});
    if (!bRange) {
        if (ptr->dateTime().isValid())
            dateTimePicker->setDateTime(ptr->dateTime());
        connect(dateTimePicker, &QhDateTimePicker::datetimed,
                this, [this](const QDateTime &dateTime) {
            ptr->setDateTime(dateTime);
            dateTimePicker->deleteLater();
            dateTimePicker = nullptr;
        });
    } else {
        if (ptr->dateTimeRange().first.isValid())
            dateTimePicker->setDateTime(ptr->dateTimeRange());
        connect(dateTimePicker, &QhDateTimePicker::datetimeRanged,
                this, [this](const QPair<QDateTime, QDateTime> &dtrange) {
            ptr->setDateTime(dtrange);
            dateTimePicker->deleteLater();
            dateTimePicker = nullptr;
        });
    }

    connect(dateTimePicker, &QhDateTimePicker::closed,
            this, [this]() {
        dateTimePicker->deleteLater();
        dateTimePicker = nullptr;
    });

    dateTimePicker->adjustSize();
    dateTimePicker->open(ptr->mapToGlobal(QPoint(0, ptr->height())));
}
