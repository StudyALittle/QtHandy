#include "qhtimepicker.h"
#include "qhtimepicker_p.h"
#include <QHBoxLayout>
#include <QEvent>
#include <QWheelEvent>

QhTimePicker::QhTimePicker(QWidget *parent):
    QhFloating(parent),
    d(new QhTimePickerPrivate(this))
{
    d->init();
}

QhTimePicker::~QhTimePicker()
{
    delete d;
}

QTime QhTimePicker::time()
{
    return d->time;
}

void QhTimePicker::setTime(const QTime &time)
{
    d->setTime(time);
}

void QhTimePickerPrivate::init()
{
    auto *ly = new QVBoxLayout(q_ptr);
    auto *bottomLy = new QHBoxLayout;

    timeWidget = new QWidget;
    timeWidget->setObjectName("WidgetTime");
    hourWidget = new QWidget;
    minuteWidget = new QWidget;
    secondWidget = new QWidget;
    timeWidget->setMouseTracking(true);
    hourWidget->setMouseTracking(true);
    minuteWidget->setMouseTracking(true);
    secondWidget->setMouseTracking(true);

    auto *buttonsLy = new QHBoxLayout(timeWidget);
    buttonsLy->addWidget(hourWidget, 1);
    buttonsLy->addWidget(minuteWidget, 1);
    buttonsLy->addWidget(secondWidget, 1);

    centerTopLine = new QLabel(timeWidget);
    centerTopLine->setObjectName("LabelCenterLine");
    centerBottomLine = new QLabel(timeWidget);
    centerBottomLine->setObjectName("LabelCenterLine");
    centerTopLine->show();
    centerBottomLine->show();

    createButtons();

    currentTimeButton = new QPushButton(tr("current time"));
    currentTimeButton->setObjectName("ButtonCurrentTime");
    okButton = new QPushButton(tr("ok"));
    okButton->setObjectName("ButtonOk");
    cancelButton = new QPushButton(tr("cancel"));
    cancelButton->setObjectName("ButtonCancel");
    bottomLy->addWidget(currentTimeButton);
    bottomLy->addStretch(1);
    bottomLy->addWidget(cancelButton);
    bottomLy->addWidget(okButton);
    bottomLy->setSpacing(8);
    bottomLy->setContentsMargins(12, 6, 12, 6);

    connect(currentTimeButton, &QPushButton::clicked, this, [this]() {
        time = QTime::currentTime();
        emit q_ptr->timed(time);
        q_ptr->close();
    });

    connect(okButton, &QPushButton::clicked, this, [this]() {
        emit q_ptr->timed(time);
        q_ptr->close();
    });

    connect(cancelButton, &QPushButton::clicked, this, [this]() {
        q_ptr->close();
    });

    ly->addWidget(timeWidget, 1);
    ly->addLayout(bottomLy);
    ly->setSpacing(0);
    ly->setContentsMargins(0, 0, 0, 0);

    setTime(QTime::currentTime());

    hourWidget->installEventFilter(this);
    minuteWidget->installEventFilter(this);
    secondWidget->installEventFilter(this);
    q_ptr->installEventFilter(this);
}

void QhTimePickerPrivate::createButtons()
{
    for (int n = 0; n < 24; ++n) {
        hourButtons[n] = createTimeButton(n, hourWidget);
        connect(hourButtons[n], &QPushButton::clicked, this, [this]() {
            auto *btn = static_cast<QPushButton*>(sender());
            setTime(QTime(btn->text().toInt(), time.minute(), time.second()));
        });
    }

    for (int n = 0; n < 60; ++n) {
        minuteButtons[n] = createTimeButton(n, minuteWidget);
        connect(minuteButtons[n], &QPushButton::clicked, this, [this]() {
            auto *btn = static_cast<QPushButton*>(sender());
            setTime(QTime(time.hour(), btn->text().toInt(), time.second()));
        });
    }

    for (int n = 0; n < 60; ++n) {
        secondButtons[n] = createTimeButton(n, secondWidget);
        connect(secondButtons[n], &QPushButton::clicked, this, [this]() {
            auto *btn = static_cast<QPushButton*>(sender());
            setTime(QTime(time.hour(), time.minute(), btn->text().toInt()));
        });
    }
}

QPushButton *QhTimePickerPrivate::createTimeButton(int number, QWidget *parent)
{
    auto *btn = new QPushButton(QString::number(number), parent);
    btn->setObjectName("ButtonTime");
    btn->setCheckable(true);
    btn->setChecked(false);
    btn->show();
    return btn;
}

void QhTimePickerPrivate::setTime(const QTime &time)
{
    this->time = time;
    moveTimeButtonPosition();
}

QTime QhTimePickerPrivate::timeAtWidget()
{
    auto *btnHour = centerButton(hourWidget, hourButtons[0]->size());
    auto *btnMinute = centerButton(minuteWidget, minuteButtons[0]->size());
    auto *btnSecond = centerButton(secondWidget, secondButtons[0]->size());

    if (!btnHour || !btnMinute || !btnSecond)
        return QTime();

    return QTime(btnHour->text().toInt(),
                 btnMinute->text().toInt(),
                 btnSecond->text().toInt());
}

QPushButton *QhTimePickerPrivate::centerButton(QWidget *widget, const QSize &buttonSize)
{
    int centerx = widget->width() / 2;
    int centery = widget->height() / 2;
    auto *w = widget->childAt(centerx, centery);
    if (!w) {
        auto *wTop = widget->childAt(centerx, centery - buttonSize.height() / 2);
        auto *wBottom = widget->childAt(centerx, centery + buttonSize.height() / 2);

        if (wTop && wBottom) {
            w = (qAbs(centery - (wTop->y() + buttonSize.height()))
                    < qAbs(centery - wBottom->y())) ?
                    wTop : wBottom;
        } else {
            w = wTop ? wTop : wBottom;
        }
    }
    return static_cast<QPushButton*>(w);
}

void QhTimePickerPrivate::updateWidgetPosition()
{
    // central location
    int halfh = hourButtons[0]->height() / 2;
    int centery = timeWidget->height() / 2;

    // move line
    int linew = timeWidget->width();
    centerTopLine->resize(linew, 1);
    centerTopLine->move(0, centery - halfh);
    centerBottomLine->resize(linew, 1);
    centerBottomLine->move(0, centery + halfh);

    // move buttons
    moveTimeButtonPosition();
}

void QhTimePickerPrivate::moveTimeButtonPosition()
{
    QTime tm;
    tm = time.isValid() ? time : QTime::currentTime();

    moveTimeButtonPosition(tm.hour(), hourWidget, hourButtons, 24);
    moveTimeButtonPosition(tm.minute(), minuteWidget, minuteButtons, 60);
    moveTimeButtonPosition(tm.second(), secondWidget, secondButtons, 60);
}

void QhTimePickerPrivate::moveTimeButtonPosition(
    int pos, QWidget *widget, QPushButton *buttons[], int size)
{
    // Center button position
    int buttonh = buttons[0]->height();
    int centery = widget->height() / 2 - buttonh / 2;
    int x = (widget->width() - buttons[0]->width()) / 2;

    int y = centery - pos * buttonh;
    for (int n = 0; n < size; ++n) {
        buttons[n]->move(x, y);
        y += buttonh;
        buttons[n]->setChecked(pos == n);
    }
}

void QhTimePickerPrivate::wheelMoveTimeButtonPosition(
    QWidget *widget, QPushButton *buttons[], int size, bool bUp)
{
    static int speed = 36;

    // int buttonh = timeWidget->height();
    // int posCenterY = timeWidget->height() / 2 - buttonh / 2;
    int posCenterY = widget->height() / 2 - buttons[0]->height() / 2;
    int moveSpace = bUp ? speed : -speed;
    if (bUp) {
        auto *btn = buttons[0];
        if (btn->y() >= posCenterY)
            return;

        int newY = btn->y() + speed;
        if (newY > posCenterY)
            moveSpace = posCenterY - btn->y();
    } else {
        auto *btn = buttons[size - 1];
        if (btn->y() <= posCenterY)
            return;

        int newY = btn->y() -  speed;
        if (newY < posCenterY)
            moveSpace = posCenterY - btn->y();
    }

    for (int n = 0; n < size; ++n) {
        auto *btn = buttons[n];
        int newY = btn->y() + moveSpace;
        btn->move(btn->x(), newY);
        btn->setChecked(false);
    }

    QPushButton *btn = centerButton(widget, buttons[0]->size());
    if (btn)
        btn->setChecked(true);
}

bool QhTimePickerPrivate::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type()) {
    case QEvent::MouseMove:
    case QEvent::HoverMove:
    case QEvent::HoverLeave:
    case QEvent::FocusOut: {
        auto time = timeAtWidget();
        if (time.isValid())
            setTime(time);
        break;
    }
    case QEvent::Resize: {
        updateWidgetPosition();
        break;
    }
    case QEvent::Wheel: {
        auto we = static_cast<QWheelEvent*>(event);
        QPoint numPixels = we->pixelDelta();
        QPoint numDegrees = we->angleDelta() / 8;

        int size = 24;
        QWidget *widget = nullptr;
        QPushButton **buttons = nullptr;
        if (hourWidget->underMouse()) {
            widget = hourWidget;
            buttons = hourButtons;
        } else if (minuteWidget->underMouse()) {
            widget = minuteWidget;
            buttons = minuteButtons;
            size = 60;
        } else if (secondWidget->underMouse()) {
            widget = secondWidget;
            buttons = secondButtons;
            size = 60;
        } else {
            break;
        }

        if (!numPixels.isNull()) {
            wheelMoveTimeButtonPosition(widget, buttons, size, numPixels.y() > 0);
        } else if (!numDegrees.isNull()) {
            QPoint numSteps = numDegrees / 15;
            wheelMoveTimeButtonPosition(widget, buttons, size, numSteps.y() > 0);
        }

        auto time = timeAtWidget();
        if (time.isValid())
            setTime(time);
    }
    default: break;
    }
    return QObject::eventFilter(obj, event);
}
