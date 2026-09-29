#ifndef QHSVPANEL_H
#define QHSVPANEL_H

/**
 * @file       qhsvpanel.h
 * @brief      SV（饱和度-亮度）选择区
 *
 * @author     wmz
 * @date       2026/09/29
 * @history
 */

#include <QWidget>
#include "QH_global.h"

class QhSVPanelPrivate;

class QTHANDY_EXPORT QhSVPanel: public QWidget
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhSVPanel)

public:
    QhSVPanel(QWidget *parent = nullptr);
    ~QhSVPanel();

    qreal hue() const;
    qreal saturation() const;
    qreal value() const;

    QColor currentColor() const;

signals:
    void colorChanged(const QColor &color);

public slots:
    void setHue(qreal h);
    void setColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
};

#endif // QHSVPANEL_H
