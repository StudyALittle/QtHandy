#include "qhlabel.h"
#include "qhlabel_p.h"
#include <QPainter>

QhLabel::QhLabel(QWidget *parent, Qt::WindowFlags f):
    QLabel(parent, f),
    d(new QhLabelPrivate)
{

}

QhLabel::QhLabel(const QString &text, QWidget *parent, Qt::WindowFlags f):
    QLabel(QString(), parent, f),
    d(new QhLabelPrivate)
{
    setText(text);
}

QhLabel::~QhLabel()
{

}

QString QhLabel::text() const
{
    return d->text;
}

QString QhLabel::placeholderText() const
{
    return d->placeholderText;
}

int QhLabel::maxLine() const
{
    return d->maxLine;
}

bool QhLabel::isEllipsis() const
{
    return d->bEllipsis;
}

QhLabel::RequiredMode QhLabel::requiredMode() const
{
    return d->requiredMode;
}

QString QhLabel::requiredPlaceholderText() const
{
    return d->requiredPlaceholderText;
}

QString QhLabel::requiredMarkText() const
{
    return d->requiredMarkText;
}

void QhLabel::setText(const QString &text)
{
    d->text = text;
    d->resetText(this);
}

void QhLabel::setMaxLine(int n)
{
    d->maxLine = n;
    d->resetText(this);
}

void QhLabel::setEllipsis(bool b)
{
    d->bEllipsis = b;
    d->resetText(this);
}

void QhLabel::setRequiredMode(RequiredMode md)
{
    d->requiredMode = md;
    d->resetText(this);
}

void QhLabel::setRequiredPlaceholderText(const QString &text)
{
    d->requiredPlaceholderText = text;
    d->resetText(this);
}

void QhLabel::setRequiredMarkText(const QString &text)
{
    d->requiredMarkText = text;
    d->resetText(this);
}

void QhLabel::setPlaceholderText(const QString &text)
{
    d->placeholderText = text;
    this->update();
}

void QhLabel::clear()
{
    QLabel::clear();
    d->text.clear();
    this->update();
}

void QhLabel::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);
    d->resetText(this);
}

void QhLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    d->drawRequired(this);

    if (this->text().isEmpty() && !d->placeholderText.isEmpty()) {
        QPainter p(this);
        p.setPen(QColor(0x8A, 0x8A, 0x8A));
        p.drawText(this->rect(), Qt::AlignCenter, d->placeholderText);
    }
}

void QhLabelPrivate::resetText(QhLabel *label)
{
    QString writeText;
    auto *baseLabel = static_cast<QLabel*>(label);
    if (maxLine <= 1) {
        if (requiredMode != QhLabel::NoRequired) {
            writeText.append(requiredPlaceholderText);
        }
        writeText.append(text);

        if (bEllipsis) {
            QFontMetrics fontWidth(label->font());
            auto elidedText = fontWidth.elidedText(writeText, Qt::ElideRight, label->width());
            baseLabel->setText(elidedText);
            if (elidedText != writeText) {
                baseLabel->setToolTip(text);
            }
        } else if (writeText != static_cast<QLabel*>(label)->text()) {
            baseLabel->setText(writeText);
        }
    } else {
        /// multi-line display
        int width = label->width();

        QString newText = text;
        newText.remove("\n");

        bool bToolTip = text.isEmpty() ? false : true;

        QFontMetrics fm(label->font());
        for (int n = 0; n < maxLine && !newText.isEmpty(); ++n) {
            if (n > 0)
                writeText.append("\n");

            if (requiredMode != QhLabel::NoRequired)
                newText.insert(0, requiredPlaceholderText);

            auto lineText = fm.elidedText(newText, Qt::ElideRight, width);
            if (lineText == newText) {
                // end
                writeText.append(lineText);
                bToolTip = false;
                break;
            }

            // remove "..."
            lineText.remove(lineText.size() - 3, 3);
            newText.remove(0, lineText.size());
            writeText.append(lineText);

            if (bEllipsis && n + 1 == maxLine) {
                // Keep "..."
                writeText.append("...");
                break;
            }

            // fill in the missing "..."
            for (int n = 0; !newText.isEmpty() && n < 2; ++n) {
                lineText.append(newText.at(0));
                int tw = fm.width(lineText);
                if (tw > width)
                    break;

                writeText.append(newText.at(0));
                newText.remove(0, 1);
            }
        }

        if (bToolTip)
            label->setToolTip(text);

        baseLabel->setText(writeText);
    }
}

void QhLabelPrivate::drawRequired(QhLabel *label)
{
    if (requiredMode != QhLabel::Required)
        return;

    QPainter p(label);

    QFontMetrics fm(label->font());

    qreal wheight = label->height();
    qreal wwidth = label->width();
    qreal theight = fm.height();
    qreal twidth = fm.width(requiredPlaceholderText + text);
    qreal x = 0, y = 0;

    auto align = label->alignment();

    if (align & Qt::AlignRight) {
        x = wwidth - twidth;
    } else if (align & Qt::AlignHCenter) {
        x = wwidth / 2.0 - twidth / 2.0;
    }

    if (align & Qt::AlignBottom) {
        y = wheight - theight;
    } else if (align & Qt::AlignVCenter) {
        y = wheight / 2.0 - theight / 2.0;
    }

    p.setPen(QColor(Qt::red));
    p.drawText(QRectF(x + 2, y, 50, 50),
        Qt::AlignTop | Qt::AlignLeft, requiredMarkText);
}














