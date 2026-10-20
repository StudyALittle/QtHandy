#include "qhlineeditsearch.h"
#include "qhlineeditsearch_p.h"
#include <QLayout>
#include "qhwidgetutil.h"

QhLineEditSearch::QhLineEditSearch(QWidget *parent) : QhLineEdit(nullptr, new QhLineEditSearchRight, parent)
{
    this->rightWidget()->setVisible(true);
}

QhLineEditSearch::QhLineEditSearch(const QString &contents, QWidget *parent) :
    QhLineEdit(nullptr, new QhLineEditSearchRight, parent)
{
    this->setText(contents);
    this->rightWidget()->setVisible(true);
}

QhLineEditSearch::QhLineEditSearch(QhLineEditSub *leftWidget, QWidget *parent) :
    QhLineEdit(leftWidget, new QhLineEditSearchRight, parent)
{
    this->rightWidget()->setVisible(true);
}

QhLineEditSearch::~QhLineEditSearch()
{
}

QhLineEditSearchRight *QhLineEditSearch::rightWidgetSearch() const
{
    return static_cast<QhLineEditSearchRight *>(this->rightWidget());
}

QhLineEditSearchRight::QhLineEditSearchRight(QWidget *parent) :
    QhLineEditSub(parent), d(new QhLineEditSearchRightPrivate(this))
{
    this->setAttribute(Qt::WA_StyledBackground);
    d->searchState = NoSearch;

    // this->setStyleSheet("background: gray;");

    auto *ly = new QHBoxLayout(this);
    d->buttonSearch = new QPushButton;
    d->buttonSearch->setFixedSize(12, 12);
    d->buttonSearch->setObjectName("ButtonSearch");
    ly->addWidget(d->buttonSearch);
    ly->setContentsMargins(8, 8, 8, 8);

    d->updateStyleProperty();

    connect(d->buttonSearch, &QPushButton::clicked, this,
        [this]() { setSearchState(d->searchState == NoSearch ? Search : NoSearch); });
}

QhLineEditSearchRight::~QhLineEditSearchRight()
{
}

QPushButton *QhLineEditSearchRight::searchButton() const
{
    return d->buttonSearch;
}

bool QhLineEditSearchRight::isClearTextAt() const
{
    return d->bClearTextAtCancelSearch;
}

void QhLineEditSearchRight::setSearchState(SearchState state)
{
    if (d->searchState == state)
        return;

    d->searchState = state;
    if (d->searchState == NoSearch && d->bClearTextAtCancelSearch && this->lineEdit) {
        this->lineEdit->clear();
    }
    d->updateStyleProperty();
    emit searchStateChanged(state);
}

void QhLineEditSearchRight::setClearTextAt(bool b)
{
    d->bClearTextAtCancelSearch = b;
}

QhLineEditSearchRight::SearchState QhLineEditSearchRight::searchState() const
{
    return d->searchState;
}

int QhLineEditSearchRight::validWidth()
{
    int w = 0;
    if (this->isVisible()) {
        if (this->layout()) {
            auto mgs = this->layout()->contentsMargins();
            w = d->buttonSearch->width() + mgs.left() + mgs.right();
            w = qMax(w, this->width());
        } else {
            w = this->width();
        }
    }
    return w;
}

QhLineEditSearchRightPrivate::QhLineEditSearchRightPrivate(QhLineEditSearchRight *lSearchRight) :
    lineEditSearchRight(lSearchRight)
{
}

QhLineEditSearchRightPrivate::~QhLineEditSearchRightPrivate()
{
}

void QhLineEditSearchRightPrivate::updateStyleProperty()
{
    buttonSearch->setProperty("search", searchState == QhLineEditSearchRight::Search ? "true" : "false");
    QhWidgetUtil::updateQssStyle(buttonSearch);
}
