#ifndef QHBASEPOPUPCONTENT_H
#define QHBASEPOPUPCONTENT_H

/**
 * @file       Qhbasepopupcontent.h
 * @brief      Pop-up base class content window
 *
 * @author     wmz
 * @date       2026/02/27
 * @history
 */

#include <QWidget>
#include "QH_global.h"

class QhBasePopup;

class QTHANDY_EXPORT QhBasePopupContent: public QWidget
{
    Q_OBJECT

public:
    QhBasePopupContent(QWidget *parent = nullptr);

    QhBasePopup *basePopup();

protected:
    /// @brief 点击确定按钮后（返回true：关闭界面（默认）；false：不关闭界面）
    virtual bool afterButtonOk();
    /// @brief 点击取消按钮后（返回true：关闭界面（默认）；false：不关闭界面）
    virtual bool afterButtonCancel();
    /// @brief 点击关闭按钮后（返回true：关闭界面（默认）；false：不关闭界面）
    virtual bool afterButtonClose();

    void setBasePopup(QhBasePopup *basePopup);

private:
    QhBasePopup *m_qBasePopup = nullptr;
    friend class QhBasePopup;
    friend class QhBasePopupPrivate;
};

#endif // QHBASEPOPUPCONTENT_H
