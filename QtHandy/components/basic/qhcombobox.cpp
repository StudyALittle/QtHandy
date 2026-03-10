#include "qhcombobox.h"
#include "qhcombobox_p.h"
#include <QListView>

QhComboBox::QhComboBox(QWidget *parent):
    QComboBox(parent),
    d(new QhComboBoxPrivate)
{
    this->setView(new QListView());
}

QhComboBox::QhComboBox(bool bModifyByWheel, QWidget *parent):
    QComboBox(parent),
    d(new QhComboBoxPrivate)
{
    setModifyByWheel(bModifyByWheel);
}

QhComboBox::~QhComboBox()
{

}

bool QhComboBox::isModifyByWheel() const
{
    return d->bModifyByWheel;
}

void QhComboBox::setModifyByWheel(bool b)
{
    d->bModifyByWheel = b;
}

void QhComboBox::wheelEvent(QWheelEvent *e)
{
    if (d->bModifyByWheel)
        QComboBox::wheelEvent(e);
}
