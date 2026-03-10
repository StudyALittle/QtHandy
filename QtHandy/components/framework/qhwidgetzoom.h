#ifndef QHWIDGETZOOM_H
#define QHWIDGETZOOM_H

/**
 * @file       Qhwidgetzoom.h
 * @brief      {文件说明}
 *
 * @author     wmz
 * @date       2026/03/02
 * @history
 */

#include <QWidget>
#include "QH_global.h"

class QhWidgetZoomPrivate;

class QTHANDY_EXPORT QhWidgetZoom
{
    Q_PRIVATE_VARIABLE(QhWidgetZoom)

public:
    static QhWidgetZoom &instance();

    QhWidgetZoom();
    ~QhWidgetZoom();

    /// @brief Get the default screen zoom ratio
    static qreal defaultScreenZoom();

    /// @brief Get the current screen zoom ratio, "w" on the screen
    static qreal screenZoomUnderWidget(QWidget *w);

    /// @brief Conversion between pt and px
    static qreal ptToPx(QWidget *w, qreal pt);
    static qreal pxToPt(QWidget *w, qreal px);

    /// @brief Whether to enable zoom
    bool enableZoom() const;

    /// @brief Obtain effective scaling (if the scaling exceeds the maximum value, return the maximum value)
    qreal validZoom() const;

    /// @brief zoom
    qreal zoom() const;

    /// @brief Maximum zoom
    qreal maxZoom() const;

    void setEnableZoom(bool enableZoom);
    void setMaxZoom(qreal maxZoom);
    void setZoom(qreal zoom);

    /// @brief Calculate the zoom size
    qreal calcZoomSize(qreal s) const;
    QSize calcZoomSize(const QSize &size) const;
    QRect calcZoomSize(const QRect &rt) const;

    qreal calcZoomSize(qreal s, qreal scale) const;
    QSize calcZoomSize(const QSize &size, qreal scale) const;
    QRect calcZoomSize(const QRect &rt, qreal scale) const;

    /// @brief Widget zoom
    void zoomWidget(QWidget *widget);

    /// @brief Zoom qss related code
    QString zoomQssPx(const QString &qss,
        const QVector<QString> &replaceAttributes = {
            "font-size", "_fontSize", "radius",
            "_padding", "padding", "padding-left", "padding-right",
            "padding-top", "padding-bottom", "min-height"
        });

    static void replaceQssSize(const QString &replaceName, QString &qss, int fromEd, qreal factor);
};

#endif // QHWIDGETZOOM_H
