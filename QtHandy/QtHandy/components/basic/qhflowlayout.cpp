#include "qhflowlayout.h"
#include "qhflowlayout_p.h"
#include <QStyle>
#include <QWidget>

QhFlowLayout::QhFlowLayout(QWidget *parent) : QLayout(parent), d(new QhFlowLayoutPrivate)
{
}

QhFlowLayout::~QhFlowLayout()
{
    while (d->items.size() > 0) {
        delete d->items.takeAt(0);
    }
}

void QhFlowLayout::setHorizontalSpacing(int space)
{
    d->hSpace = space;
}

void QhFlowLayout::setVerticalSpacing(int space)
{
    d->vSpace = space;
}

void QhFlowLayout::addItem(QLayoutItem *item)
{
    d->items.append(item);
}

QLayoutItem *QhFlowLayout::itemAt(int index) const
{
    return d->items.value(index);
}

QLayoutItem *QhFlowLayout::takeAt(int index)
{
    return (index < 0 || index >= d->items.size()) ? nullptr : d->items.takeAt(index);
}

Qt::Orientations QhFlowLayout::expandingDirections() const
{
    return {};
}

int QhFlowLayout::count() const
{
    return d->items.size();
}

int QhFlowLayout::horizontalSpacing() const
{
    if (d->hSpace >= 0) {
        return d->hSpace;
    } else {
        return smartSpacing(QStyle::PM_LayoutHorizontalSpacing);
    }
}

int QhFlowLayout::verticalSpacing() const
{
    if (d->vSpace >= 0) {
        return d->vSpace;
    } else {
        return smartSpacing(QStyle::PM_LayoutVerticalSpacing);
    }
}

bool QhFlowLayout::hasHeightForWidth() const
{
    return true;
}

int QhFlowLayout::heightForWidth(int width) const
{
    int height = doLayout(QRect(0, 0, width, 0), true);
    return height;
}

QSize QhFlowLayout::minimumSize() const
{
    QSize size;
    for (auto &item : d->items) {
        size = size.expandedTo(item->minimumSize());
    }

    const QMargins margins = contentsMargins();
    size += QSize(margins.left() + margins.right(), margins.top() + margins.bottom());
    return size;
}

QSize QhFlowLayout::sizeHint() const
{
    return minimumSize();
}

void QhFlowLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);
    doLayout(rect, false);
}

int QhFlowLayout::doLayout(const QRect &rect, bool testOnly) const
{
    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
    int x = effectiveRect.x();
    int y = effectiveRect.y();
    int lineHeight = 0;

    for (auto &item : d->items) {
        const QWidget *wid = item->widget();
        int spaceX = horizontalSpacing();
        if (spaceX == -1)
            spaceX = wid->style()->layoutSpacing(QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Horizontal);
        int spaceY = verticalSpacing();
        if (spaceY == -1)
            spaceY = wid->style()->layoutSpacing(QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Vertical);
        int nextX = x + item->sizeHint().width() + spaceX;
        if (nextX - spaceX > effectiveRect.right() && lineHeight > 0) {
            x = effectiveRect.x();
            y = y + lineHeight + spaceY;
            nextX = x + item->sizeHint().width() + spaceX;
            lineHeight = 0;
        }

        if (!testOnly)
            item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));

        x = nextX;
        lineHeight = qMax(lineHeight, item->sizeHint().height());
    }
    return y + lineHeight - rect.y() + bottom;
}

int QhFlowLayout::smartSpacing(QStyle::PixelMetric pm) const
{
    QObject *parent = this->parent();
    if (!parent) {
        return -1;
    } else if (parent->isWidgetType()) {
        QWidget *pw = static_cast<QWidget *>(parent);
        return pw->style()->pixelMetric(pm, nullptr, pw);
    } else {
        return static_cast<QLayout *>(parent)->spacing();
    }
}

QhFlowLayoutPrivate::QhFlowLayoutPrivate()
{
}

QhFlowLayoutPrivate::~QhFlowLayoutPrivate()
{
}
