#ifndef QHLINEEDITDATETIME_H
#define QHLINEEDITDATETIME_H

#include <QDateTime>
#include "qhlineedit.h"
#include "QH_global.h"

class QhLineEditDateTimePrivate;

class QTHANDY_EXPORT QhLineEditDateTime: public QhLineEdit
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhLineEditDateTime)

public:
    typedef QPair<QDateTime, QDateTime> DTRange;
    typedef QPair<QDate, QDate> DRange;
    typedef QPair<QTime, QTime> TRange;

    enum Type {
        Time,
        TimeRange, // TODO: Not yet implemented
        Date,
        DateRange,
        DateTime,
        DateTimeRange
    };

    QhLineEditDateTime(Type type, QWidget *parent = nullptr);
    ~QhLineEditDateTime();

    QDateTime dateTime() const;
    DTRange dateTimeRange() const;

    QDate date() const;
    DRange dateRange() const;

    QTime time() const;
    TRange timeRange() const;

    void setDateTime(const QDateTime &dateTime);
    void setDateTime(const DTRange &dtrange);

    void setDate(const DRange &drange);
    void setDate(const QDate &date);

    void setTime(const TRange &trange);
    void setTime(const QTime &time);
};

#endif // QHLINEEDITDATETIME_H
