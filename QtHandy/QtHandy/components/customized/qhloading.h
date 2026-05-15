#ifndef QHLOADING_H
#define QHLOADING_H

/**
 * @file       Qhloading.h
 * @brief      Loading box needs to be attached to a parent class
 *
 * @author     wmz
 * @date       2026/02/28
 * @history
 */

#include <QWidget>
#include "QH_global.h"

class QhLoadingPrivate;

class QTHANDY_EXPORT QhLoading: public QWidget
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhLoading)

public:
    QhLoading(QWidget *parent);
    ~QhLoading();

    /// @brief @brief showLoadding：打开加载窗口（参数时间都为毫秒）
    /// @param nWaitShowTimeSpace:
    /// 调用此函数后，nWaitShowTimeSpace时间内不显示窗口，
    /// 在这个时间段内调用closeLoadding函数，此加载窗口就会关闭，不会显示
    /// @param nMinShowTimeSpace:
    /// 在nWaitShowTimeSpace时间内未调用closeLoadding函数，窗口显示时间最小为nMinShowTimeSpace，
    /// 即使调用closeLoadding函数，窗口也会显示最小为nMinShowTimeSpace毫秒
    void showLoadding(int nWaitShowTimeSpace = 200, int nMinShowTimeSpace = 2000);

    /// @brief closeLoadding：关闭加载窗口
    void closeLoadding();

    /// @brief
    void updateSize();

    virtual void startLoadding() = 0;
    virtual void stopLoadding() = 0;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // QHLOADING_H
