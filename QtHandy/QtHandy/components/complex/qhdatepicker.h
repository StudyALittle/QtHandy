#ifndef QHDATEPICKER_H
#define QHDATEPICKER_H

/**
 * @file       Qhdatepicker.h
 * @brief      date picker
 *
 * @author     wmz
 * @date       2026/02/26
 * @history
 */

#include <QDate>
#include <qhfloating.h>
#include "QH_global.h"

class QhDatePickerPrivate;

class QTHANDY_EXPORT QhDatePicker: public QhFloating
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhDatePicker)

public:
    struct TNames
    {
        QString year = tr("year");
        QString month = tr("month");
        QString day = tr("day");

        struct Week
        {
            QString monday = tr("mon");
            QString tuesday = tr("tues");
            QString wednesday = tr("wednes");
            QString thursday = tr("thurs");
            QString friday = tr("fri");
            QString saturday = tr("satur");
            QString sunday = tr("sun");
        };
        Week week;
    };

    typedef QPair<QDate, QDate> DRange;

    QhDatePicker(bool bRange = false, QWidget *parent = nullptr);
    ~QhDatePicker();

    static TNames &tnames();

    QDate date() const;
    DRange dateRange() const;

    void setDate(const QDate &date);
    void setDate(const DRange &dateRange);

signals:
    void dated(const QDate &date);
    void dateRanged(const QPair<QDate, QDate> &dateRange);

protected:
    friend class QhDateTimePickerPrivate;
    QhDatePicker(bool bBase, bool bRange, QWidget *parent = nullptr);
};

#endif // QHDATEPICKER_H
