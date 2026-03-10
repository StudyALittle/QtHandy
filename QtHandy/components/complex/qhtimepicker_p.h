#ifndef QHTIMEPICKER_P_H
#define QHTIMEPICKER_P_H

#include <QPushButton>
#include <QTime>
#include <QLabel>
#include "qhtimepicker.h"

class QhTimePickerPrivate: public QObject
{
    Q_OBJECT

    Q_DISABLE_COPY(QhTimePickerPrivate)
    Q_DECLARE_PUBLIC(QhTimePicker)

public:
    QhTimePickerPrivate(QhTimePicker *q):
        q_ptr(q) { }

    void init();
    void createButtons();
    QPushButton *createTimeButton(int number, QWidget *parent);

    void setTime(const QTime &time);

    QTime time;

protected:
    QTime timeAtWidget();
    QPushButton *centerButton(QWidget *widget, const QSize &buttonSize);
    void updateWidgetPosition();
    void moveTimeButtonPosition();
    void moveTimeButtonPosition(int pos, QWidget *widget, QPushButton *buttons[], int size);
    void wheelMoveTimeButtonPosition(QWidget *widget, QPushButton *buttons[], int size, bool bUp);

    bool eventFilter(QObject *obj, QEvent *event);

private:
    QhTimePicker *const q_ptr;

    QWidget *timeWidget;
    QWidget *hourWidget;
    QWidget *minuteWidget;
    QWidget *secondWidget;

    QLabel *centerTopLine;
    QLabel *centerBottomLine;

    // hour buttons
    QPushButton *hourButtons[24];
    // minute buttons
    QPushButton *minuteButtons[60];
    // second buttons
    QPushButton *secondButtons[60];

    // current time button
    QPushButton *currentTimeButton;
    // ok button
    QPushButton *okButton;
    // cancel button
    QPushButton *cancelButton;
};

#endif // QHTIMEPICKER_P_H
