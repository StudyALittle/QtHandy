#ifndef QHFLOWLAYOUT_H
#define QHFLOWLAYOUT_H

#include <QLayout>
#include <QStyle>
#include "QH_global.h"

class QhFlowLayoutPrivate;

class QTHANDY_EXPORT QhFlowLayout : public QLayout
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhFlowLayout)

public:
    QhFlowLayout(QWidget *parent = nullptr);
    ~QhFlowLayout();

    void setHorizontalSpacing(int space);
    void setVerticalSpacing(int space);

    void addItem(QLayoutItem *item) override;
    QLayoutItem *itemAt(int index) const override;
    QLayoutItem *takeAt(int index) override;

    Qt::Orientations expandingDirections() const override;
    int count() const override;
    int horizontalSpacing() const;
    int verticalSpacing() const;
    bool hasHeightForWidth() const override;
    int heightForWidth(int width) const override;

    QSize minimumSize() const override;
    QSize sizeHint() const override;
    void setGeometry(const QRect &rect) override;

private:
    int doLayout(const QRect &rect, bool testOnly) const;
    int smartSpacing(QStyle::PixelMetric pm) const;
};

#endif // QHFLOWLAYOUT_H
