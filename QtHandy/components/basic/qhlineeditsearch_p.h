#ifndef QHLINEEDITSEARCH_P_H
#define QHLINEEDITSEARCH_P_H

#include <QPushButton>
#include "qhlineeditsearch.h"

class QhLineEditSearchRightPrivate : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhLineEditSearchRightPrivate)

public:
    QhLineEditSearchRightPrivate(QhLineEditSearchRight *lSearchRight);
    ~QhLineEditSearchRightPrivate();

    void updateStyleProperty();

    QhLineEditSearchRight *lineEditSearchRight;
    QPushButton *buttonSearch;
    QhLineEditSearchRight::SearchState searchState;

    bool bClearTextAtCancelSearch = true;
};

#endif // QHLINEEDITSEARCH_P_H
