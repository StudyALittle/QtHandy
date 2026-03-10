#include "demodatetime.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTime>
#include <QVariant>
#include <qhlabel.h>

#pragma execution_character_set("utf-8")

DemoDateTime::DemoDateTime(QWidget *parent):
    QWidget(parent)
{
    auto *ly = new QVBoxLayout(this);
    {
        auto *label = new QhLabel("Time Picker");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");

        auto *button = new QPushButton("time");
        connect(button, &QPushButton::clicked, this, [button, this]() {
            auto *timePicker = new QhTimePicker;
            timePicker->setTime(QTime::fromString(button->text(), "HH:mm:ss"));
            timePicker->setAttribute(Qt::WA_DeleteOnClose);
            timePicker->adjustSize();
            connect(timePicker, &QhTimePicker::timed, this, [button](const QTime &time) {
                button->setText(time.toString("HH:mm:ss"));
            });
            timePicker->resize(260, 400);
            timePicker->open(QCursor::pos());
        });

        ly->addWidget(label);
        ly->addWidget(button);
    }

    // Facilitate international translation
    QhDatePicker::tnames() = {
        "年", "月", "日", { "一", "二", "三", "四", "五", "六", "日" }
    };

    {
        auto *label = new QhLabel("Date Picker");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");

        auto *button = new QPushButton(QDate::currentDate().toString("yyyy-MM-dd"));
        connect(button, &QPushButton::clicked, this, [button, this]() {
            auto *datePicker = new QhDatePicker;
            datePicker->setDate(QDate::fromString(button->text(), "yyyy-MM-dd"));
            datePicker->setAttribute(Qt::WA_DeleteOnClose);
            datePicker->adjustSize();
            connect(datePicker, &QhDatePicker::dated, this, [datePicker, button](const QDate &date) {
                button->setText(date.toString("yyyy-MM-dd"));
                datePicker->close();
            });
            datePicker->setAttribute(Qt::WA_DeleteOnClose);
            datePicker->open(QCursor::pos());
        });

        ly->addWidget(label);
        ly->addWidget(button);
    }

    {
        auto *label = new QhLabel("Date Range Picker");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");

        auto *button = new QPushButton(QDate::currentDate().toString("yyyy-MM-dd"));
        static QhDatePicker::DRange s_drange = { QDate::currentDate(), QDate::currentDate() };
        connect(button, &QPushButton::clicked, this, [button, this]() {
            auto *datePicker = new QhDatePicker(true);
            datePicker->setDate(s_drange);

            datePicker->setAttribute(Qt::WA_DeleteOnClose);
            datePicker->adjustSize();
            connect(datePicker, &QhDatePicker::dateRanged, this,
                    [datePicker, button](const QPair<QDate, QDate> &dateRange) {
                button->setText(
                    dateRange.first.toString("yyyy-MM-dd") + " to " +
                    dateRange.second.toString("yyyy-MM-dd"));
                s_drange = dateRange;
                datePicker->close();
            });
            datePicker->setAttribute(Qt::WA_DeleteOnClose);
            datePicker->open(QCursor::pos());
        });

        ly->addWidget(label);
        ly->addWidget(button);
    }

    {
        auto *label = new QhLabel("Date Time Picker");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");

        auto *button = new QPushButton(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
        connect(button, &QPushButton::clicked, this, [button, this]() {
            auto *datePicker = new QhDateTimePicker;
            connect(datePicker, &QhDateTimePicker::datetimed, this,
                    [button](const QDateTime &dateTime) {
                button->setText(dateTime.toString("yyyy-MM-dd HH:mm:ss"));
            });
            datePicker->setDateTime(QDateTime::fromString(button->text(), "yyyy-MM-dd HH:mm:ss"));
            datePicker->adjustSize();
            datePicker->setAttribute(Qt::WA_DeleteOnClose);
            datePicker->open(QCursor::pos());
        });

        ly->addWidget(label);
        ly->addWidget(button);
    }

    {
        auto *label = new QhLabel("Date Time Range Picker");
        label->setStyleSheet("font-size: 16px; font-weight: 600;");

        static QhDateTimePicker::DTRange s_drange = {
            QDateTime::currentDateTime(),
            QDateTime::currentDateTime()
        };
        auto *button = new QPushButton(QhDateTimePicker::dateTimesToString(s_drange));
        connect(button, &QPushButton::clicked, this, [button, this]() {
            auto *datePicker = new QhDateTimePicker(true);
            connect(datePicker, &QhDateTimePicker::datetimeRanged, this,
                    [button](const QPair<QDateTime, QDateTime> &dtrange) {
                s_drange = dtrange;
                button->setText(QhDateTimePicker::dateTimesToString(s_drange));
            });
            datePicker->setDateTime(s_drange);
            datePicker->adjustSize();
            datePicker->setAttribute(Qt::WA_DeleteOnClose);
            datePicker->open(QCursor::pos());
        });

        ly->addWidget(label);
        ly->addWidget(button);
    }

    ly->addStretch(1);
}
