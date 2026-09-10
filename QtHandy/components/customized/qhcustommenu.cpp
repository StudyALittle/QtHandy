#include "qhcustommenu.h"
#include "qhcustommenu_p.h"
#include <QPushButton>
#include <qhwidgetutil.h>

QhCustomMenu::QhCustomMenu(QWidget *parent):
    QhFloating(parent), d(new QhCustomMenuPrivate(this))
{
    d->init();
}

QhCustomMenu::~QhCustomMenu()
{

}

QAbstractButton *QhCustomMenu::button(int id)
{
    for (auto &button: d->buttons) {
        if (button.second == id)
            return button.first;
    }
    return nullptr;
}

void QhCustomMenu::addButton(QAbstractButton *button, int id)
{
    connect(button, &QAbstractButton::clicked, this, [this, button, id]() {
        emit clicked(button, id);
    });
    d->layout->addWidget(button);
    d->buttons.append({button, id});
}

QAbstractButton *QhCustomMenu::addButton(const QString &text, int id)
{
    auto *button = new QPushButton(text);
    addButton(button, id);
    return button;
}

void QhCustomMenu::exec(const QPoint &pos)
{
    this->open(pos);
}

void QhCustomMenu::exec(QWidget *alignWidget)
{
    this->adjustSize();

    QPoint pos;
    auto *pw = this->parentWidget();
    if (pw) {
        pos = QPoint(0, alignWidget->height());
        pos = alignWidget->mapTo(pw, pos);
        if (pos.y() + this->height() > pw->height())
            pos.setY(pos.y() - alignWidget->height() - this->height());
    } else {
        pos = QPoint(0, alignWidget->height());
        pos = alignWidget->mapToGlobal(pos);

        auto *screen = QhWidgetUtil::screenUnderPoint(pos);
        if (screen && (pos.y() + this->height() > screen->availableSize().height())) {
            pos.setY(pos.y() - alignWidget->height() - this->height());
        }
    }
    this->open(pos);
}

QhCustomMenuPrivate::QhCustomMenuPrivate(QhCustomMenu *pCustomMenu):
    customMenu(pCustomMenu)
{

}

QhCustomMenuPrivate::~QhCustomMenuPrivate()
{

}

void QhCustomMenuPrivate::init()
{
    layout = new QVBoxLayout(customMenu);
}
