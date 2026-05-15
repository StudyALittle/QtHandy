#include "qhtextedit.h"
#include "qhtextedit_p.h"
#include <QResizeEvent>
#include "qhqss.h"

QhTextEdit::QhTextEdit(QWidget *parent):
    QTextEdit(parent),
    d(new QhTextEditPrivate(this))
{
    d->init();
}

QhTextEdit::QhTextEdit(const QString &text, QWidget *parent):
    QTextEdit(text, parent),
    d(new QhTextEditPrivate(this))
{
    d->init();
}

QhTextEdit::~QhTextEdit()
{

}

int QhTextEdit::textMaxLenght()
{
    return d->textMaxLenght;
}

void QhTextEdit::setTextMaxLenght(int len)
{
    d->textMaxLenght = len;
    d->onTextChanged();
}

QString QhTextEdit::getLabelMargins() const
{
    return QhQss::marginsToString(d->labelMargins);
}

void QhTextEdit::setLabelMargins(const QString &str)
{
    d->labelMargins = QhQss::stringToMargins(str);
    d->resetLabelPos(QSize());
}

void QhTextEdit::resizeEvent(QResizeEvent *e)
{
    QTextEdit::resizeEvent(e);

    auto size = e->size();
    d->resetLabelPos(size);
}

QhTextEditPrivate::QhTextEditPrivate(QhTextEdit *p):
    ptr(p)
{

}

QhTextEditPrivate::~QhTextEditPrivate()
{

}

void QhTextEditPrivate::init()
{
    label = new QLabel(ptr);
    label->clear();

    connect(ptr, &QhTextEdit::textChanged,
            this, &QhTextEditPrivate::onTextChanged);
}

void QhTextEditPrivate::resetLabelPos(const QSize &size)
{
    auto newSize = size.isValid() ? size : ptr->size();
    label->move(newSize.width() - label->width() - labelMargins.right(),
                newSize.height() - label->height() - labelMargins.bottom());
}

void QhTextEditPrivate::resetLabelText()
{
    if (textMaxLenght <= 0) {
        label->clear();
        return;
    }

    label->setText(QString("%1/%2").arg(ptr->toPlainText().size()).arg(textMaxLenght));
    label->adjustSize();
    label->update();

    resetLabelPos(QSize());
}

void QhTextEditPrivate::onTextChanged()
{
    resetLabelText();

    if (textMaxLenght <= 0)
        return;

    QString text = ptr->toPlainText();
    if (text.size() <= textMaxLenght)
        return;

    QTextCursor cursor = ptr->textCursor();
    ptr->setText(text.mid(0, textMaxLenght));
    if (cursor.position() > textMaxLenght) {
        cursor.setPosition(textMaxLenght);
    }
    ptr->setTextCursor(cursor);
}
