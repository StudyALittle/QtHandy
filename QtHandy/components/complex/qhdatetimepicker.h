#ifndef QHDATETIMEPICKER_H
#define QHDATETIMEPICKER_H

/**
 * @file       Qhdatetimepicker.h
 * @brief      datetime picker
 *
 * @author     wmz
 * @date       2026/02/26
 * @history
 */

#include <QDateTime>
#include <qhfloating.h>
#include "QH_global.h"

class QhDateTimePickerPrivate;

class QTHANDY_EXPORT QhDateTimePicker: public QhFloating
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhDateTimePicker)

public:
    typedef QPair<QDateTime, QDateTime> DTRange;

    QhDateTimePicker(bool bRange = false, QWidget *parent = nullptr);
    ~QhDateTimePicker();

    QDateTime dateTime() const;
    DTRange dateTimeRange() const;

    void setDateTime(const QDateTime &dateTime);
    void setDateTime(const DTRange &dtrange);

    static QString dateTimesToString(
        const DTRange &dtms,
        const QString &content = "%1 to %2",
        const QString &format = "yyyy-MM-dd HH:mm:ss");

signals:
    void datetimed(const QDateTime &dateTime);
    void datetimeRanged(const QPair<QDateTime, QDateTime> &dtrange);
};

#endif // QHDATETIMEPICKER_H
