#ifndef QHLINEEDIT_P_H
#define QHLINEEDIT_P_H

#include "qhlineedit.h"

class QhLineEditLeftPrivate: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhLineEditLeftPrivate)

public:
    QhLineEditLeftPrivate(QhLineEditLeft *p);
    ~QhLineEditLeftPrivate();

    void init();
    int width();

    QhLineEditLeft *ptr;

    QLabel *label = nullptr;
};

class QhLineEditRightPrivate: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhLineEditRightPrivate)

public:
    QhLineEditRightPrivate(QhLineEditRight *p);
    ~QhLineEditRightPrivate();

    void init();
    int width();

    QhLineEditRight *ptr;

    QPushButton *button = nullptr;

    bool bConClicked = false;

public slots:
    void onClicked(bool checked = false);
};

class QhLineEditPrivate: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhLineEditPrivate)

public:
    explicit QhLineEditPrivate(QhLineEdit *p);

    void init(QhLineEditSub *leftWidget, QhLineEditSub *rightWidget);
    void checkTextFormat();
    void resetMargin();

    QhLineEdit *ptr;

    QhLineEditSub *widgetLeft = nullptr;
    QhLineEditSub *widgetRight = nullptr;

    /// text margins
    QMargins margins;

    std::function<bool(QhLineEdit*)> textValidateFunction = nullptr;
    bool bValidateEmptyNoError = false;
};

#endif // QHLINEEDIT_P_H
