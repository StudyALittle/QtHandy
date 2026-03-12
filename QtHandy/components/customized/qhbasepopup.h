#ifndef QHBASEPOPUP_H
#define QHBASEPOPUP_H

/**
 * @file       Qhbasepopup.h
 * @brief      Pop-up base class, including close, cancel, and confirm buttons
 *
 * @author     wmz
 * @date       2026/01/06
 * @history
 */

#include <QDialog>
#include <QLabel>
#include "qhframelesswindow.h"
#include "QH_global.h"

class QhBasePopupPrivate;
class QhBasePopupContent;

class QTHANDY_EXPORT QhBasePopup: public QhFramelessDialog
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhBasePopup)

    Q_PROPERTY_EX(int, WidgetTitleSpace)
    Q_PROPERTY_EX(int, WidgetButtonsSpace)
    Q_PROPERTY_EX(QString, WidgetTitleMargins)
    Q_PROPERTY_EX(QString, WidgetButtonsMargins)

public:
    enum Button
    {
        ButtonOk        = 0x0001,
        ButtonCancel    = 0x0010,
        ButtonClose     = 0x0100,
        ButtonAll       = ButtonOk | ButtonCancel | ButtonClose
    };
    Q_DECLARE_FLAGS(Buttons, Button)

    QhBasePopup(QWidget *parent = nullptr);
    QhBasePopup(const QString &title, QWidget *parent = nullptr);
    ~QhBasePopup();

    QPushButton *button(Button btn) const;
    Buttons buttons() const;
    QString buttonText(Button btn) const;
    bool buttonEnable(Button btn) const;

    QString title() const;

    QLabel *iconLabel() const;
    QWidget *contentWidget() const;
    QWidget *takeContentWidget() const;

    Button closedButton() const;

    void setButtons(Buttons btns);
    void setButtonText(Button btn, const QString &text);
    void setButtonsEnable(Buttons btns, bool enable);
    void setButtonEnable(Button btn, bool enable);

    void setTitle(const QString &text);

    void setContentWidget(QWidget *w);
    void setContentWidget(QhBasePopupContent *w);

    int getWidgetTitleSpace() const;
    void setWidgetTitleSpace(int space);

    int getWidgetButtonsSpace() const;
    void setWidgetButtonsSpace(int space);

    QString getWidgetTitleMargins() const;
    void setWidgetTitleMargins(const QString &mgs);

    QString getWidgetButtonsMargins() const;
    void setWidgetButtonsMargins(const QString &mgs);

protected:
    /// @brief 点击确定按钮后（返回true：关闭界面（默认）；false：不关闭界面）
    virtual bool afterButtonOk();
    /// @brief 点击取消按钮后（返回true：关闭界面（默认）；false：不关闭界面）
    virtual bool afterButtonCancel();
    /// @brief 点击关闭按钮后（返回true：关闭界面（默认）；false：不关闭界面）
    virtual bool afterButtonClose();
};

#endif // QHBASEPOPUP_H
