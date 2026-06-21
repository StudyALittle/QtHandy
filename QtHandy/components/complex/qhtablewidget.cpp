#include "qhtablewidget.h"
#include "qhtablewidget_p.h"
#include <QResizeEvent>
#include <QHeaderView>
#include <QScrollBar>
#include "qhheaderview.h"
#include "qhheaderviewitem.h"

#define FROZEN_FRONT_BEHIND(DoFront, DoBehind)              \
    if (d->frozenTableFront) {                              \
        int colCnt = d->frozenTableFront->columnCount();    \
        if (column < colCnt) {                              \
            DoFront;                                        \
        }                                                   \
    }                                                       \
    if (d->frozenTableBehind) {                             \
        int behindColumn = d->columnToFrozenBehind(column); \
        if (behindColumn >= 0) {                            \
            DoBehind;                                       \
        }                                                   \
    }

QhTableWidget::QhTableWidget(QWidget *parent) : QTableWidget(parent), d(new QhTableWidgetPrivate(this))
{
    d->init();
}

QhTableWidget::QhTableWidget(int rows, int columns, QWidget *parent) :
    QTableWidget(rows, columns, parent), d(new QhTableWidgetPrivate(this))
{
    d->init();
}

QhTableWidget::~QhTableWidget()
{
    this->clearContents();
    for (auto &item : d->hItems) delete item;
    d->hItems.clear();
}

void QhTableWidget::openFrozenTableFront(int columnCount)
{
    d->initFrozenTable(&(d->frozenTableFront), &(d->hHeaderViewFront), columnCount);
    d->initFrozenTable();
}

void QhTableWidget::openFrozenTableBehind(int columnCount)
{
    d->initFrozenTable(&(d->frozenTableBehind), &(d->hHeaderViewBehind), columnCount);
    d->initFrozenTable();
}

QhHeaderViewItem *QhTableWidget::horizontalHeaderItemAt(int column)
{
    FROZEN_FRONT_BEHIND(                                  //
        return d->hHeaderViewFront->itemAt(column),       //
        return d->hHeaderViewBehind->itemAt(behindColumn) //
    )
    return d->hHeaderView->itemAt(column);
}

void QhTableWidget::setHorizontalHeaderItems(const QList<QhTableWidgetItem *> &items)
{
    d->hItems = items;

    this->setColumnCount(items.size());
    QStringList labels;
    for (int column = 0; column < items.size(); ++column) {
        auto &item = items[column];
        labels.append(item->name());
    }

    if (d->frozenTableFront) {
        QStringList frontLabels;
        for (int n = 0; n < labels.size(); ++n) {
            frontLabels.append(labels.at(n));
        }
        d->frozenTableFront->setHorizontalHeaderLabels(frontLabels);
    }
    if (d->frozenTableBehind) {
        QStringList behindLabels;
        for (int n = labels.size() - 1, cnt = 0; n >= 0 && cnt < d->frozenTableBehind->columnCount(); --n, ++cnt) {
            behindLabels.insert(0, labels.at(n));
        }
        d->frozenTableBehind->setHorizontalHeaderLabels(behindLabels);
    }

    this->setHorizontalHeaderLabels(labels);

    for (int column = 0; column < items.size(); ++column) {
        auto &item = items[column];
        if (item->item()) {
            this->setHorizontalHeaderItem(column, item->item());
        }

        if (item->hitem()) {
            item->hitem()->setName(item->name());

            if (d->hHeaderViewFront) {
                int colCnt = d->frozenTableFront->columnCount();
                if (column < colCnt) {
                    d->hHeaderViewFront->setItem(column, item->hitem());
                    continue;
                }
            }

            if (d->hHeaderViewBehind) {
                int behindCol = d->columnToFrozenBehind(column);
                if (behindCol >= 0) {
                    d->hHeaderViewBehind->setItem(behindCol, item->hitem());
                    continue;
                }
            }

            d->hHeaderView->setItem(column, item->hitem());
        }
    }

    d->updateItemSize();
    d->updateFrozenTableGeometry();
}

void QhTableWidget::setRowCount(int count)
{
    if (d->frozenTableFront)
        d->frozenTableFront->setRowCount(count);
    if (d->frozenTableBehind)
        d->frozenTableBehind->setRowCount(count);
    QTableWidget::setRowCount(count);
}

void QhTableWidget::setItem(int row, int column, QTableWidgetItem *item)
{
    FROZEN_FRONT_BEHIND(                                              //
        return d->frozenTableFront->setItem(row, column, item),       //
        return d->frozenTableBehind->setItem(row, behindColumn, item) //
    )
    QTableWidget::setItem(row, column, item);
}

QTableWidgetItem *QhTableWidget::setCellText(int row, int column, const QString &text, int alignment)
{
    auto *item = new QTableWidgetItem(text);
    item->setTextAlignment(alignment);
    setItem(row, column, item);
    return item;
}

void QhTableWidget::setCellWidget(int row, int column, QWidget *widget)
{
    FROZEN_FRONT_BEHIND(                                                      //
        return d->frozenTableFront->setCellWidget(row, column, widget),       //
        return d->frozenTableBehind->setCellWidget(row, behindColumn, widget) //
    )
    QTableWidget::setCellWidget(row, column, widget);
}

void QhTableWidget::setColumnWidth(int column, int width)
{
    FROZEN_FRONT_BEHIND(                                                 //
        d->frozenTableFront->setColumnWidth(column, width),       //
        d->frozenTableBehind->setColumnWidth(behindColumn, width) //
    )
    QTableWidget::setColumnWidth(column, width);
}

QTableWidgetItem *QhTableWidget::item(int row, int column) const
{
    FROZEN_FRONT_BEHIND(                                     //
        return d->frozenTableFront->item(row, column),       //
        return d->frozenTableBehind->item(row, behindColumn) //
    )
    return QTableWidget::item(row, column);
}

QWidget *QhTableWidget::cellWidget(int row, int column) const
{
    FROZEN_FRONT_BEHIND(                                           //
        return d->frozenTableFront->cellWidget(row, column),       //
        return d->frozenTableBehind->cellWidget(row, behindColumn) //
    )
    return QTableWidget::cellWidget(row, column);
}

void QhTableWidget::clearContents()
{
    if (d->frozenTableFront)
        d->frozenTableFront->clearContents();
    if (d->frozenTableBehind)
        d->frozenTableBehind->clearContents();
    QTableWidget::clearContents();
}

void QhTableWidget::clear()
{
    if (d->frozenTableFront)
        d->frozenTableFront->clear();
    if (d->frozenTableBehind)
        d->frozenTableBehind->clear();
    QTableWidget::clear();
}

void QhTableWidget::horizontalHeaderAssociatedCheckBoxStatus(int column)
{
    auto *hHeaderItem = this->horizontalHeaderItemAt(column);
    // 表头第一行复选框为选中状态跟表格数据复选框状态同步
    connect(hHeaderItem, &QhHeaderViewItem::checkStateChanged, this, [this, column](int /*index*/, int state) {
        auto *hHeaderItem = this->horizontalHeaderItemAt(column);
        if (state == Qt::PartiallyChecked)
            return;

        hHeaderItem->checkBox()->setTristate(false);
        int rowCount = this->rowCount();
        for (int row = 0; row < rowCount; ++row) {
            auto *w = static_cast<QhHeaderViewItem*>(this->cellWidget(row, column));
            if (!w || !w->inherits("QhHeaderViewItem"))
                continue;

            w->checkBox()->blockSignals(true);
            w->checkBox()->setCheckState((Qt::CheckState)state);
            w->checkBox()->blockSignals(false);
        }
    });
}

void QhTableWidget::associatedHorizontalHeaderCheckBoxStatus(
    QhHeaderViewItem *item, int column)
{
    connect(item, &QhHeaderViewItem::checkStateChanged, this, [this, column](int /*index*/, int state) {
        auto *hHeaderItem = horizontalHeaderItemAt(column);
        if (!hHeaderItem || state == Qt::PartiallyChecked)
            return;

        int rowCount = this->rowCount();
        QList<int> rows = this->checkedRows<QhHeaderViewItem>(column);
        hHeaderItem->blockSignals(true);
        if (rows.isEmpty()) {
            hHeaderItem->checkBox()->setTristate(false);
            hHeaderItem->checkBox()->setCheckState(Qt::Unchecked);
        } else if (rows.size() == rowCount) {
            hHeaderItem->checkBox()->setTristate(false);
            hHeaderItem->checkBox()->setCheckState(Qt::Checked);
        } else {
            hHeaderItem->checkBox()->setTristate(true);
            hHeaderItem->checkBox()->setCheckState(Qt::PartiallyChecked);
        }
        hHeaderItem->blockSignals(false);
    });
}

void QhTableWidget::resizeEvent(QResizeEvent *e)
{
    QTableWidget::resizeEvent(e);
    d->updateItemSize();
    d->updateFrozenTableGeometry();
}

QModelIndex QhTableWidget::moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
    QModelIndex current = QTableView::moveCursor(cursorAction, modifiers);

    if (d->frozenTableFront && cursorAction == MoveLeft && current.column() > 0 &&
        visualRect(current).topLeft().x() < d->frozenTableFront->columnWidth(0)) {
        const int newValue = this->horizontalScrollBar()->value() + visualRect(current).topLeft().x() -
                             d->frozenTableFront->columnWidth(0);
        this->horizontalScrollBar()->setValue(newValue);
    }
    if (d->frozenTableBehind && cursorAction == MoveLeft && current.column() > 0 &&
        visualRect(current).topLeft().x() < d->frozenTableBehind->columnWidth(0)) {
        const int newValue =
            horizontalScrollBar()->value() + visualRect(current).topLeft().x() - d->frozenTableBehind->columnWidth(0);
        horizontalScrollBar()->setValue(newValue);
    }
    return current;
}

void QhTableWidget::scrollTo(const QModelIndex &index, ScrollHint hint)
{
    if (index.column() > 0 || (d->frozenTableFront && !d->frozenTableFront->isVisible()))
        QTableView::scrollTo(index, hint);
    if (index.column() > 0 || (d->frozenTableBehind && !d->frozenTableBehind->isVisible()))
        QTableView::scrollTo(index, hint);
}

QhTableWidgetPrivate::QhTableWidgetPrivate(QhTableWidget *tbw) : tableWidget(tbw)
{
}

QhTableWidgetPrivate::~QhTableWidgetPrivate()
{
}

void QhTableWidgetPrivate::init()
{
    hHeaderView = new QhHeaderView(Qt::Horizontal);
    hHeaderView->setSectionResizeMode(QHeaderView::Fixed); // 默认列不能拖动
    tableWidget->setHorizontalHeader(hHeaderView);
}

void QhTableWidgetPrivate::initFrozenTable()
{
    if (!bInitFrozenTableFront && !bInitFrozenTableBehind) {
        // 滚动条同步
        connect(tableWidget->horizontalHeader(), &QHeaderView::sectionResized, this,
            [this](int logicalIndex, int /* oldSize */, int newSize) {
                if (frozenTableFront) {
                    int colCount = frozenTableFront->columnCount();
                    if (logicalIndex >= 0 && logicalIndex < colCount) {
                        frozenTableFront->setColumnWidth(logicalIndex, newSize);
                    }
                }
                if (frozenTableBehind) {
                    int col = columnToFrozenBehind(logicalIndex);
                    if (col >= 0) {
                        frozenTableBehind->setColumnWidth(col, newSize);
                    }
                }
                updateFrozenTableGeometry();
            });

        connect(tableWidget->verticalHeader(), &QHeaderView::sectionResized, this,
            [this](int logicalIndex, int /* oldSize */, int newSize) {
                if (frozenTableFront)
                    frozenTableFront->setRowHeight(logicalIndex, newSize);
                if (frozenTableBehind)
                    frozenTableBehind->setRowHeight(logicalIndex, newSize);
            });
    }

    if (frozenTableFront && !bInitFrozenTableFront) {
        bInitFrozenTableFront = true;
        connect(frozenTableFront->verticalScrollBar(), &QAbstractSlider::valueChanged, tableWidget->verticalScrollBar(),
            &QAbstractSlider::setValue);
        connect(tableWidget->verticalScrollBar(), &QAbstractSlider::valueChanged, frozenTableFront->verticalScrollBar(),
            &QAbstractSlider::setValue);
        frozenTableFront->setVerticalScrollMode(QTableWidget::ScrollPerPixel);
    }

    if (frozenTableBehind && !bInitFrozenTableBehind) {
        bInitFrozenTableBehind = true;
        connect(frozenTableBehind->verticalScrollBar(), &QAbstractSlider::valueChanged,
            tableWidget->verticalScrollBar(), &QAbstractSlider::setValue);
        connect(tableWidget->verticalScrollBar(), &QAbstractSlider::valueChanged,
            frozenTableBehind->verticalScrollBar(), &QAbstractSlider::setValue);
        frozenTableBehind->setVerticalScrollMode(QTableWidget::ScrollPerPixel);
    }

    tableWidget->setHorizontalScrollMode(QTableWidget::ScrollPerPixel);
    tableWidget->setVerticalScrollMode(QTableWidget::ScrollPerPixel);

    updateItemSize();
    updateFrozenTableGeometry();
}

void QhTableWidgetPrivate::initFrozenTable(QTableWidget **tb, QhHeaderView **header, int columnCount)
{
    (*header) = new QhHeaderView(Qt::Horizontal);
    (*header)->setSectionResizeMode(QHeaderView::Fixed); // 默认列不能拖动
    // (*header)->setStretchLastSection(true);

    (*tb) = new QTableWidget(tableWidget);
    (*tb)->setHorizontalHeader(*header);
    (*tb)->verticalHeader()->setVisible(false);
    (*tb)->setColumnCount(columnCount);
    (*tb)->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    (*tb)->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    (*tb)->setStyleSheet("QTableWidget{border: none}");
    (*tb)->setMinimumWidth(1);
}

void QhTableWidgetPrivate::updateItemSize()
{
    int w = tableWidget->horizontalHeader()->width();
    int usedWidth = 0;

    for (int col = 0; col < hItems.size(); ++col) {
        auto &item = hItems[col];
        item->setIndex(col);
        if (!item->isFillRemaiSize()) {
            usedWidth += item->size();
        }
    }

    for (int col = 0; col < hItems.size(); ++col) {
        auto &item = hItems[col];
        if (item->isFillRemaiSize()) {
            int fw = w - usedWidth;
            if (fw < item->size())
                fw = item->size();
            tableWidget->setColumnWidth(col, fw);
        } else {
            tableWidget->setColumnWidth(col, item->size());
        }
    }
}

void QhTableWidgetPrivate::updateFrozenTableGeometry(int behindWidth)
{
    if (frozenTableFront) {
        int x = tableWidget->verticalHeader()->width() + tableWidget->frameWidth();
        int y = tableWidget->frameWidth();
        int w = 0;
        for (int n = 0; n < frozenTableFront->columnCount(); ++n) {
            w += tableWidget->columnWidth(n);
        }
        int h = tableWidget->viewport()->height() + tableWidget->horizontalHeader()->height();
        frozenTableFront->setGeometry(x, y, w, h);
    }

    if (frozenTableBehind) {
        int w = behindWidth;
        int colCount = frozenTableBehind->columnCount();
        if (behindWidth < 0 && colCount > 0) {
            w = 0;
            for (int n = 0; n < colCount; ++n) {
                int col = columnFromFrozenBehind(n);
                w += tableWidget->columnWidth(col);
            }
        }
        // w -= 1;
        int vsw = tableWidget->verticalScrollBar()->isVisible() ? tableWidget->verticalScrollBar()->width() : 0;
        int x = tableWidget->width() - w - vsw - tableWidget->verticalHeader()->width() - tableWidget->frameWidth();
        int y = tableWidget->frameWidth();
        int h = tableWidget->viewport()->height() + tableWidget->horizontalHeader()->height();
        frozenTableBehind->setGeometry(x, y, w, h);
    }
}

int QhTableWidgetPrivate::columnToFrozenBehind(int column)
{
    if (!frozenTableBehind)
        return -1;

    int n = tableWidget->columnCount() - frozenTableBehind->columnCount();
    return column - n;
}

int QhTableWidgetPrivate::columnFromFrozenBehind(int column)
{
    if (!frozenTableBehind)
        return -1;

    int n = tableWidget->columnCount() - frozenTableBehind->columnCount();
    return column + n;
}
