#ifndef QHLINEEDITSEARCH_H
#define QHLINEEDITSEARCH_H

#include <QPushButton>
#include "qhlineedit.h"
#include "QH_global.h"

class QhLineEditSearchRightPrivate;

class QTHANDY_EXPORT QhLineEditSearchRight : public QhLineEditSub
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhLineEditSearchRight)

public:
    enum SearchState { NoSearch, Search };

    QhLineEditSearchRight(QWidget *parent = nullptr);
    ~QhLineEditSearchRight();

    QPushButton *searchButton() const;

    SearchState searchState() const;

    /// @biref When canceling the search, clear the text（by Button or setSearchState()）
    bool isClearTextAt() const;

    void setSearchState(SearchState state);
    void setClearTextAt(bool b);

    int validWidth() override;

signals:
    void searchStateChanged(int state);
};

class QTHANDY_EXPORT QhLineEditSearch : public QhLineEdit
{
    Q_OBJECT

public:
    QhLineEditSearch(QWidget *parent = nullptr);
    QhLineEditSearch(const QString &contents, QWidget *parent = nullptr);
    QhLineEditSearch(QhLineEditSub *leftWidget, QWidget *parent = nullptr);
    ~QhLineEditSearch();

    QhLineEditSearchRight *rightWidgetSearch() const;
};

#endif // QHLINEEDITSEARCH_H
