#ifndef QHMESSAGEBOX_H
#define QHMESSAGEBOX_H

/**
 * @file       Qhmessagebox.h
 * @brief      Message prompt box
 *
 * @author     wmz
 * @date       2026/02/27
 * @history
 */

#include "qhbasepopup.h"
#include "QH_global.h"

class QhMessageBoxPrivate;

class QTHANDY_EXPORT QhMessageBox: public QhBasePopup
{
    Q_OBJECT

public:
    enum Icon {
        NoIcon,
        Question,
        Information,
        Warning,
        Critical,
    };

    QhMessageBox(QWidget *parent = nullptr);
    ~QhMessageBox();

    void setMessage(const QString &text);

    static Button question(QWidget *widget,
        const QString &title, const QString &text, Buttons buttons = ButtonOk);

    static Button information(QWidget *widget,
        const QString &title, const QString &text, Buttons buttons = ButtonOk);

    static Button warning(QWidget *widget,
        const QString &title, const QString &text, Buttons buttons = ButtonOk);

    static Button critical(QWidget *widget,
        const QString &title, const QString &text, Buttons buttons = ButtonOk);

    static Button message(Icon icon, QWidget *widget,
        const QString &title, const QString &text, Buttons buttons = ButtonAll);

protected:
    virtual void init(Icon icon);

private:
    QhMessageBoxPrivate *d;
    Q_DISABLE_COPY(QhMessageBox)
    friend class QhMessageBoxPrivate;
};

#endif // QHMESSAGEBOX_H
