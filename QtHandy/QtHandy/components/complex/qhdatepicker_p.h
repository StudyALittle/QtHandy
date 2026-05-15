#ifndef QHDATEPICKER_P_H
#define QHDATEPICKER_P_H

#include <QStackedWidget>
#include <QPushButton>
#include <QLabel>
#include <QDate>
#include "qhdatepicker.h"

class QhDatePickerItemPrivate: public QWidget
{
    Q_OBJECT

public:
    QhDatePickerItemPrivate(QhDatePickerPrivate *p, QWidget *parent = nullptr);
    ~QhDatePickerItemPrivate();

    void init(bool bRange);
    void setDate(const QDate &date);
    void setDayPage(int year, int month);

    QhDatePickerPrivate const *ptr;

    /// @brief Date: Make no effective judgment
    struct Date
    {
        int year() const { return _year; }
        int month() const { return _month; }
        int day() const { return _day; }

        Date &operator = (const QDate &date)
        {
            _year = date.year();
            _month = date.month();
            _day = date.day();
            return *this;
        }

        QDate toQDate() const { return QDate(_year, _month, _day); }

        int _year;
        int _month;
        int _day;
    };
    Date date;
    bool bRange = false;

    /// top: year/month
    QWidget *widgetTopYearMonth = nullptr;
    QPushButton *buttonPreYear = nullptr;
    QPushButton *buttonPreMonth = nullptr;
    QPushButton *buttonNextYear = nullptr;
    QPushButton *buttonNextMonth = nullptr;
    QPushButton *buttonYear = nullptr;
    QPushButton *buttonMonth = nullptr;

    /// bottom QStackedWidget
    QStackedWidget *stackedWidget = nullptr;

    /// page years
    QWidget *pageYears = nullptr;
    QPushButton *buttonYears[10];

    /// page month
    QWidget *pageMonths = nullptr;
    QPushButton *buttonMonths[12];

    /// page days
    QWidget *pageDays = nullptr;
    /// week
    QPushButton *buttonWeeks[7];
    /// days
    QPushButton *buttonDays[7*6];

signals:
    void dated(const QDate &date);
    void pageYearMonthChanged(int year, int month);

public slots:
    void onToYearsPage();
    void onToMonthsPage();
    void onToDaysPage();
    void onToDay();

    void onYearAddSub();
    void onMonthAddSub();

    void resetPageYears(int year);
    void resetPageDays(int year, int month);
    void updateRangeDaysChoosed();

public:
    static QPair<int, int> monthSub(int year, int month);
    static QPair<int, int> monthAdd(int year, int month);

    /// @brief Calculate the day of the week for a given date
    int calcDayWeek(int y, int m, int d);
    /// @brief Calculate the number of days in the corresponding year and month
    int calcMonthDayNum(int year, int month);

    QVector<int> monthDayNums;
};

class QhDatePickerPrivate: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhDatePickerPrivate)

public:
    QhDatePickerPrivate(QWidget *q);
    ~QhDatePickerPrivate();

    void init(bool bRange = false);
    void setDate(const QDate &date);
    void setDateRange(const QDate &dateStart, const QDate &dateEnd);

    QhDatePickerItemPrivate *leftWidgetDate = nullptr;
    QhDatePickerItemPrivate *rightWidgetDate = nullptr;

    QDate choosedDateStart;
    QDate choosedDateEnd;

signals:
    void dated(const QDate &date);
    void dateRanged(const QPair<QDate, QDate> &dateRange);

protected slots:
    void onDated(const QDate &date);
    void onPageYearMonthChanged(int year, int month);

private:
    QWidget *const ptr;
};

#endif // QHDATEPICKER_P_H
