#include "qhdatepicker.h"
#include "qhdatepicker_p.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QVariant>
#include "qhwidgetutil.h"

QhDatePicker::QhDatePicker(bool bRange, QWidget *parent):
    QhFloating(parent),
    d(new QhDatePickerPrivate(this))
{
    d->init(bRange);
    connect(d.get(), &QhDatePickerPrivate::dated, this, &QhDatePicker::dated);
    connect(d.get(), &QhDatePickerPrivate::dateRanged, this, &QhDatePicker::dateRanged);
}

QhDatePicker::QhDatePicker(bool bBase, bool bRange, QWidget *parent):
    QhFloating(bBase, parent),
    d(new QhDatePickerPrivate(this))
{
    d->init(bRange);
    connect(d.get(), &QhDatePickerPrivate::dated, this, &QhDatePicker::dated);
    connect(d.get(), &QhDatePickerPrivate::dateRanged, this, &QhDatePicker::dateRanged);
}

QhDatePicker::~QhDatePicker()
{

}

QhDatePicker::TNames &QhDatePicker::tnames()
{
    static TNames s_tnames;
    return s_tnames;
}

QDate QhDatePicker::date() const
{
    return d->choosedDateStart;
}

QhDatePicker::DRange QhDatePicker::dateRange() const
{
    return {d->choosedDateStart, d->choosedDateEnd};
}

void QhDatePicker::setDate(const QDate &date)
{
    d->setDate(date);
}

void QhDatePicker::setDate(const DRange &dateRange)
{
    d->setDateRange(dateRange.first, dateRange.second);
}

QhDatePickerPrivate::QhDatePickerPrivate(QWidget *q):
    ptr(q)
{

}

QhDatePickerPrivate::~QhDatePickerPrivate()
{

}

void QhDatePickerPrivate::init(bool bRange)
{
    auto *ly = new QHBoxLayout(ptr);

    leftWidgetDate = new QhDatePickerItemPrivate(this);
    connect(leftWidgetDate, &QhDatePickerItemPrivate::dated,
        this, &QhDatePickerPrivate::onDated);
    leftWidgetDate->init(bRange);
    if (bRange) {
        connect(leftWidgetDate, &QhDatePickerItemPrivate::pageYearMonthChanged,
            this, &QhDatePickerPrivate::onPageYearMonthChanged);
        QhWidgetUtil::hideRetainSize(leftWidgetDate->buttonNextYear);
        QhWidgetUtil::hideRetainSize(leftWidgetDate->buttonNextMonth);
    }
    ly->addWidget(leftWidgetDate);

    if (bRange) {
        rightWidgetDate = new QhDatePickerItemPrivate(this);
        connect(rightWidgetDate, &QhDatePickerItemPrivate::dated,
            this, &QhDatePickerPrivate::onDated);
        rightWidgetDate->init(bRange);

        connect(rightWidgetDate, &QhDatePickerItemPrivate::pageYearMonthChanged,
            this, &QhDatePickerPrivate::onPageYearMonthChanged);
        QhWidgetUtil::hideRetainSize(rightWidgetDate->buttonPreYear);
        QhWidgetUtil::hideRetainSize(rightWidgetDate->buttonPreMonth);

        // default value
        auto date = QDate::currentDate();
        leftWidgetDate->setDate(date);
        auto ym = rightWidgetDate->monthAdd(date.year(), date.month());
        rightWidgetDate->setDate(QDate(ym.first, ym.second, 1));

        ly->addWidget(rightWidgetDate);
    }
    ly->setSpacing(0);
    ly->setContentsMargins(0, 0, 0, 0);
}

void QhDatePickerPrivate::setDate(const QDate &date)
{
    choosedDateStart = date;
    leftWidgetDate->setDate(date);
    leftWidgetDate->updateRangeDaysChoosed();
}

void QhDatePickerPrivate::setDateRange(const QDate &dateStart, const QDate &dateEnd)
{
    choosedDateStart = dateStart;
    choosedDateEnd = dateEnd;

    leftWidgetDate->setDate(dateStart);

    auto ym = rightWidgetDate->monthAdd(dateStart.year(), dateStart.month());
    rightWidgetDate->setDate(QDate(ym.first, ym.second, 1));
}

void QhDatePickerPrivate::onDated(const QDate &date)
{
    if (sender() == leftWidgetDate && !rightWidgetDate) {
        choosedDateStart = date;
        // leftWidgetDate->date = date;
        leftWidgetDate->updateRangeDaysChoosed();
        emit dated(date);
        // ptr->close();
        return;
    }

    int validDateNum = 0;
    if (choosedDateStart.isValid()) ++validDateNum;
    if (choosedDateEnd.isValid()) ++validDateNum;

    if (validDateNum == 2 || validDateNum == 0) {
        choosedDateStart = date;
        choosedDateEnd = QDate();

        leftWidgetDate->updateRangeDaysChoosed();
        rightWidgetDate->updateRangeDaysChoosed();
    } else if (validDateNum == 1) {
        if (date < choosedDateStart) {
            choosedDateEnd = choosedDateStart;
            choosedDateStart = date;
        } else {
            choosedDateEnd = date;
        }
        leftWidgetDate->updateRangeDaysChoosed();
        rightWidgetDate->updateRangeDaysChoosed();
        emit dateRanged({choosedDateStart, choosedDateEnd});
        // ptr->close();
    }
}

void QhDatePickerPrivate::onPageYearMonthChanged(int year, int month)
{
    // The left side is always one month younger than the right side
    if (sender() == leftWidgetDate) {
        auto ym = rightWidgetDate->monthAdd(year, month);
        rightWidgetDate->setDayPage(ym.first, ym.second);
    } else {
        auto ym = leftWidgetDate->monthSub(year, month);
        leftWidgetDate->setDayPage(ym.first, ym.second);
    }
}

QhDatePickerItemPrivate::QhDatePickerItemPrivate(QhDatePickerPrivate *p, QWidget *parent):
    QWidget(parent),
    ptr(p)
{

}

QhDatePickerItemPrivate::~QhDatePickerItemPrivate()
{

}

void QhDatePickerItemPrivate::init(bool bRange)
{
    this->bRange = bRange;
    date = QDate::currentDate();

    /// top: year/month
    widgetTopYearMonth = new QWidget;
    widgetTopYearMonth->setObjectName("WidgetTopYearMonth");
    buttonPreYear = new QPushButton("<<");
    buttonPreMonth = new QPushButton("<");
    buttonNextYear = new QPushButton(">>");
    buttonNextMonth = new QPushButton(">");
    buttonYear = new QPushButton(tr("%1%2").arg(date.year()).arg(QhDatePicker::tnames().year));
    buttonMonth = new QPushButton(tr("%1%2").arg(date.month()).arg(QhDatePicker::tnames().month));

    buttonPreYear->setObjectName("ButtonPreYear");
    buttonPreMonth->setObjectName("ButtonPreMonth");
    buttonNextYear->setObjectName("ButtonNextYear");
    buttonNextMonth->setObjectName("ButtonNextMonth");
    buttonYear->setObjectName("LButtonYear");
    buttonMonth->setObjectName("LButtonMonth");

    /// bottom QStackedWidget
    stackedWidget = new QStackedWidget;

    /// page years
    {
        pageYears = new QWidget;
        stackedWidget->addWidget(pageYears);

        for (int n = 0; n < 10; ++n) {
            buttonYears[n] = new QPushButton(tr("0"));
            buttonYears[n]->setObjectName("ButtonYear");
        }

        auto *ly = new QGridLayout(pageYears);
        int row = 0, col = 0;
        for (int n = 0; n < 10; ++n) {
            ly->addWidget(buttonYears[n], row, col++);
            if (!((n + 1) % 4)) {
                ++row; col = 0;
            }
        }
    }

    /// page month
    {
        pageMonths = new QWidget;
        stackedWidget->addWidget(pageMonths);

        for (int n = 0; n < 12; ++n) {
            buttonMonths[n] = new QPushButton(tr("%1%2").arg(n + 1).arg(QhDatePicker::tnames().month));
            buttonMonths[n]->setObjectName("ButtonMonth");
            buttonMonths[n]->setProperty("month", n + 1);
        }

        auto *ly = new QGridLayout(pageMonths);
        int row = 0, col = 0;
        for (int n = 0; n < 12; ++n) {
            ly->addWidget(buttonMonths[n], row, col++);
            if (!((n + 1) % 4)) {
                ++row; col = 0;
            }
        }
    }

    /// page days
    {
        pageDays = new QWidget;
        stackedWidget->addWidget(pageDays);

        /// week
        auto createWeekButton = [](const QString &name)
        {
            auto *btn = new QPushButton(name);
            btn->setObjectName("ButtonWeek");
            return btn;
        };
        buttonWeeks[0] = createWeekButton(QhDatePicker::tnames().week.monday);
        buttonWeeks[1] = createWeekButton(QhDatePicker::tnames().week.tuesday);
        buttonWeeks[2] = createWeekButton(QhDatePicker::tnames().week.wednesday);
        buttonWeeks[3] = createWeekButton(QhDatePicker::tnames().week.thursday);
        buttonWeeks[4] = createWeekButton(QhDatePicker::tnames().week.friday);
        buttonWeeks[5] = createWeekButton(QhDatePicker::tnames().week.saturday);
        buttonWeeks[6] = createWeekButton(QhDatePicker::tnames().week.sunday);

        /// days
        for (int n = 0; n < 7*6; ++n) {
            buttonDays[n] = new QPushButton(tr("0"));
            buttonDays[n]->setObjectName("ButtonDay");
        }

        auto *lyWeekDays = new QGridLayout(pageDays);
        for (int n = 0; n < 7; ++n) {
            lyWeekDays->addWidget(buttonWeeks[n], 0, n);
        }

        // auto *label = new QLabel;
        // lyWeekDays->addWidget(label, 1, 0, 1, 7);

        int row = 1, col = 0;
        for (int n = 0; n < 7*6; ++n) {
            lyWeekDays->addWidget(buttonDays[n], row, col++);
            if (!((n + 1) % 7)) {
                ++row; col = 0;
            }
        }
    }

    /// main layout
    auto *ly = new QVBoxLayout(this);

    auto *lyTop = new QHBoxLayout(widgetTopYearMonth);
    lyTop->addWidget(buttonPreYear);
    lyTop->addWidget(buttonPreMonth);
    lyTop->addStretch(1);
    lyTop->addWidget(buttonYear);
    lyTop->addWidget(buttonMonth);
    lyTop->addStretch(1);
    lyTop->addWidget(buttonNextMonth);
    lyTop->addWidget(buttonNextYear);

    ly->addWidget(widgetTopYearMonth);
    ly->addWidget(stackedWidget, 1);
    ly->setContentsMargins(0, 0, 0, 0);
    ly->setSpacing(6);

    stackedWidget->setCurrentWidget(pageDays);
    setDate(date.toQDate());

    if (!bRange) {
        connect(buttonYear, &QPushButton::clicked,
                this, [this]() {
            stackedWidget->setCurrentWidget(pageYears);
            buttonMonth->setVisible(false);
            buttonPreMonth->setVisible(false);
            buttonNextMonth->setVisible(false);
            resetPageYears(date.year());
        });
        connect(buttonMonth, &QPushButton::clicked,
            this, [this]() {
            stackedWidget->setCurrentWidget(pageMonths);
            buttonMonth->setVisible(false);
            buttonPreMonth->setVisible(false);
            buttonNextMonth->setVisible(false);
        });
    }

    for (int n = 0; n < 12; ++n) {
        connect(buttonYears[n], &QPushButton::clicked,
            this, &QhDatePickerItemPrivate::onToMonthsPage);
    }
    for (int n = 0; n < 12; ++n) {
        connect(buttonMonths[n], &QPushButton::clicked,
            this, &QhDatePickerItemPrivate::onToDaysPage);
    }
    for (int n = 0; n < 7*6; ++n) {
        connect(buttonDays[n], &QPushButton::clicked,
            this, &QhDatePickerItemPrivate::onToDay);
    }

    connect(buttonPreYear, &QPushButton::clicked,
        this, &QhDatePickerItemPrivate::onYearAddSub);
    connect(buttonNextYear, &QPushButton::clicked,
        this, &QhDatePickerItemPrivate::onYearAddSub);

    connect(buttonPreMonth, &QPushButton::clicked,
        this, &QhDatePickerItemPrivate::onMonthAddSub);
    connect(buttonNextMonth, &QPushButton::clicked,
            this, &QhDatePickerItemPrivate::onMonthAddSub);
}

void QhDatePickerItemPrivate::setDate(const QDate &date)
{
    stackedWidget->setCurrentWidget(pageDays);
    this->date = date;
    setDayPage(date.year(), date.month());
}

void QhDatePickerItemPrivate::setDayPage(int year, int month)
{
    date._year = year;
    date._month = month;
    buttonYear->setText(tr("%1%2").arg(year).arg(QhDatePicker::tnames().year));
    buttonMonth->setText(tr("%1%2").arg(month).arg(QhDatePicker::tnames().month));
    resetPageYears(year);
    resetPageDays(year, month);
}

void QhDatePickerItemPrivate::onToYearsPage()
{
    stackedWidget->setCurrentWidget(pageYears);
}

void QhDatePickerItemPrivate::onToMonthsPage()
{
    stackedWidget->setCurrentWidget(pageMonths);

    auto *btnYear = static_cast<QPushButton*>(sender());
    auto year = btnYear->property("year").toInt();
    setDayPage(year, date.month());
}

void QhDatePickerItemPrivate::onToDaysPage()
{
    stackedWidget->setCurrentWidget(pageDays);
    buttonMonth->setVisible(true);
    buttonPreMonth->setVisible(true);
    buttonNextMonth->setVisible(true);

    auto *btnMonth = static_cast<QPushButton*>(sender());
    auto month = btnMonth->property("month").toInt();
    setDayPage(date.year(), month);
}

void QhDatePickerItemPrivate::onToDay()
{
    auto *btnDay = static_cast<QPushButton*>(sender());
    auto day = btnDay->property("day").toInt();
    date._day = day;
    emit dated(date.toQDate());
}

void QhDatePickerItemPrivate::onYearAddSub()
{
    int step = (stackedWidget->currentWidget() == pageYears) ? 10 : 1;

    int year = date.year();
    if (sender() == buttonPreYear) {
        year -= step;
        if (year <= 0)
            return;
    } else {
        year += step;
    }
    setDayPage(year, date.month());
    emit pageYearMonthChanged(year, date.month());
}

void QhDatePickerItemPrivate::onMonthAddSub()
{
    QPair<int, int> ym;
    if (sender() == buttonPreMonth) {
        ym = monthSub(date.year(), date.month());
    } else {
        ym = monthAdd(date.year(), date.month());
    }

    setDayPage(ym.first, ym.second);
    emit pageYearMonthChanged(ym.first, ym.second);
}

QPair<int, int> QhDatePickerItemPrivate::monthSub(int year, int month)
{
    if (year <= 0 && month <= 1)
        return {year, month};

    month -= 1;
    if (month <= 0) {
        month = 12;
        -- year;
    }
    return {year, month};
}

QPair<int, int> QhDatePickerItemPrivate::monthAdd(int year, int month)
{
    month += 1;
    if (month > 12) {
        month = 1;
        ++ year;
    }
    return {year, month};
}

void QhDatePickerItemPrivate::resetPageYears(int year)
{
    // Display 10 years per page

    int index = year % 10;
    for (int n = index, space = 0; n < 10; ++n, ++space) {
        buttonYears[n]->setText(tr("%1%2").arg(year + space).arg(QhDatePicker::tnames().year));
        buttonYears[n]->setProperty("year", year + space);
    }
    for (int n = index - 1, space = 1; n >= 0; --n, ++space) {
        buttonYears[n]->setText(tr("%1%2").arg(year - space).arg(QhDatePicker::tnames().year));
        buttonYears[n]->setProperty("year", year - space);
    }

    if (stackedWidget->currentWidget() == pageYears) {
        buttonYear->setText(tr("%1%3 - %2%3")
            .arg(buttonYears[0]->property("year").toInt())
            .arg(buttonYears[9]->property("year").toInt())
            .arg(QhDatePicker::tnames().year));
    } else {
        buttonYear->setText(tr("%1%2").arg(year).arg(QhDatePicker::tnames().year));
    }
}

void QhDatePickerItemPrivate::resetPageDays(int year, int month)
{
    if (month <= 0 || month > 12)
        month = 1;

    auto preYM = monthSub(year, month);

    int preMonthDayNum = calcMonthDayNum(preYM.first, preYM.second);
    int dayNum = calcMonthDayNum(year, month);

    int week = calcDayWeek(year, month, 1) - 1;

    // pre month days
    for (int n = 0, day = preMonthDayNum - week + 1; n < week; ++n, ++day) {
        buttonDays[n]->setEnabled(false);
        buttonDays[n]->setText(QString::number(day));
        buttonDays[n]->setProperty("day", day);
    }

    // current month days
    for (int n = week, day = 1; n < (dayNum + week); ++n, ++day) {
        buttonDays[n]->setEnabled(true);
        buttonDays[n]->setText(QString::number(day));
        buttonDays[n]->setProperty("day", day);
    }

    // next month days
    for (int n = dayNum + week, day = 1; n < 7*6; ++n, ++day) {
        buttonDays[n]->setEnabled(false);
        buttonDays[n]->setText(QString::number(day));
        buttonDays[n]->setProperty("day", day);
    }

    updateRangeDaysChoosed();
}

void QhDatePickerItemPrivate::updateRangeDaysChoosed()
{
    if (!bRange) {
        for (int n = 0; n < 7*6; ++n) {
            if (!buttonDays[n]->isEnabled()) {
                buttonDays[n]->setCheckable(false);
                buttonDays[n]->setChecked(false);
                buttonDays[n]->setProperty("qstate", "");
                QhWidgetUtil::updateQssStyle(buttonDays[n]);
                continue;
            }

            int day = buttonDays[n]->property("day").toInt();
            if (ptr->choosedDateStart.isValid()
                    && (day == ptr->choosedDateStart.day()
                        && date.month() == ptr->choosedDateStart.month()
                        && date.year() == ptr->choosedDateStart.year())) {
                buttonDays[n]->setCheckable(true);
                buttonDays[n]->setChecked(true);
                buttonDays[n]->setProperty("qstate", "");
            } else {
                buttonDays[n]->setCheckable(false);
                buttonDays[n]->setChecked(false);
                buttonDays[n]->setProperty("qstate", "");
            }
            QhWidgetUtil::updateQssStyle(buttonDays[n]);
        }
        return;
    }

    int validDateNum = 0;
    if (ptr->choosedDateStart.isValid()) ++validDateNum;
    if (ptr->choosedDateEnd.isValid()) ++validDateNum;

    for (int n = 0; n < 7*6; ++n) {
        if (!buttonDays[n]->isEnabled()) {
            buttonDays[n]->setProperty("qstate", "");
            QhWidgetUtil::updateQssStyle(buttonDays[n]);
            continue;
        }

        int day = buttonDays[n]->property("day").toInt();
        QDate currentDate(date.year(), date.month(), day);
        if (ptr->choosedDateStart.isValid()
                && (day == ptr->choosedDateStart.day()
                    && date.month() == ptr->choosedDateStart.month()
                    && date.year() == ptr->choosedDateStart.year())) {
            buttonDays[n]->setCheckable(true);
            buttonDays[n]->setChecked(true);
            buttonDays[n]->setProperty("qstate", "");
        } else if (ptr->choosedDateEnd.isValid()
               && (day == ptr->choosedDateEnd.day()
                   && date.month() == ptr->choosedDateEnd.month()
                   && date.year() == ptr->choosedDateEnd.year())) {
            buttonDays[n]->setCheckable(true);
            buttonDays[n]->setChecked(true);
            buttonDays[n]->setProperty("qstate", "");
        } else {
            buttonDays[n]->setCheckable(false);
            buttonDays[n]->setChecked(false);
            if (validDateNum == 2
                    && currentDate > ptr->choosedDateStart
                    && currentDate < ptr->choosedDateEnd)
                buttonDays[n]->setProperty("qstate", "daterange");
            else
                buttonDays[n]->setProperty("qstate", "");
        }
        QhWidgetUtil::updateQssStyle(buttonDays[n]);
    }
}

int QhDatePickerItemPrivate::calcDayWeek(int y, int m, int d)
{
    // 基姆拉尔森计算公式
    // 把一月和二月换算成上一年的十三月和是四月
    if(m==1 || m==2) {
        m += 12;
        y--;
    }

    // 取值范围是0~6，0代表星期日，1~6星期一到星期六
    int week = (d+2*m+3*(m+1)/5+y+y/4-y/100+y/400+1)%7;
    return week == 0 ? 7 : week;
}

int QhDatePickerItemPrivate::calcMonthDayNum(int year, int month)
{
    // 一月大，二月平，三月大，四月小，五月大，六月小，七月大，八月大，九月小，十月大，十一月小，十二月大。
    // 大月，一三五七八十腊（即十二月），每个月都有三十一天。小月，四六九冬（即十一月），每个月都是三十天

    //【平年与闰年】
    // 对于平年来说，二月有二十八天；
    // 但如果是闰年，二月则有二十九天。
    // 一般来说，能被4整除的年份通常是闰年，但世纪年需能被400整除才是闰年。例如：
    // 1) 2008年能被4整除，商为502，所以2008年是闰年。
    // 2) 而2009年不能被4整除，商为502.25，因此2009年是平年。
    // 此外，对于世纪年来说：
    // 1) 1900年不能被400整除，商为4.75，所以1900年是平年。
    // 2) 而2000年能被400整除，商为5，因此2000年是闰年。

    if (monthDayNums.isEmpty()) {
        monthDayNums = {
            31/*1*/, 0/*2*/, 31/*3*/, 30/*4*/, 31/*5*/, 30/*6*/,
            31/*7*/, 31/*8*/, 30/*9*/, 31/*10*/, 30/*11*/, 31/*12*/
        };
    }

    if (month == 2) {
        // 是否闰年
        bool bLeapYear;

        if (!(year % 100)) {
            // 世纪年
            bLeapYear = !(year % 400);
        } else {
            bLeapYear = !(year % 4);
        }

        return bLeapYear ? 29 : 28;
    } else {
        return monthDayNums.at(month  - 1);
    }
}

