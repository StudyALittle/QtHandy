#ifndef QHPROGRESSBAR_H
#define QHPROGRESSBAR_H

#include <QProgressBar>
#include "QH_global.h"

class QhProgressBarPrivate;

class QTHANDY_EXPORT QhProgressBar : public QProgressBar
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhProgressBar)
    Q_PROPERTY_EX(QColor, Background)
    Q_PROPERTY_EX(QColor, ChunkBackground)

public:
    QhProgressBar(QWidget *parent = nullptr);
    ~QhProgressBar();

    bool isRoundedCorner() const;
    void setRoundedCorner(bool b);

    QColor getBackground() const;
    QColor getChunkBackground() const;

    void setBackground(const QColor &color);
    void setChunkBackground(const QColor &color);

protected:
    void paintEvent(QPaintEvent *e) override;
};

#endif // QHPROGRESSBAR_H
