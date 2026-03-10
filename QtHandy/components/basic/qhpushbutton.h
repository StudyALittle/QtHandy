#ifndef QHPUSHBUTTON_H
#define QHPUSHBUTTON_H

#include <QPushButton>
#include "qhqss.h"
#include "QH_global.h"

class QhPushButtonPrivate;

class QTHANDY_EXPORT QhPushButton: public QPushButton
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhPushButton)

public:
    QhPushButton(QWidget *parent = nullptr);
    QhPushButton(const QString &text, QWidget *parent = nullptr);
    QhPushButton(const QIcon &icon, const QString &text, QWidget *parent = nullptr);
    ~QhPushButton();

    /// @brief: Is it icon mode.
    /// When it is false, all the following parameters are invalid
    bool isImageMode() const;

    /// @brief text
    QString text() const;

    void setImageMode(bool b);
    void setText(const QString &text);

    void resizeUpdate();

    QhQss *handyQss();

protected:
    void paintEvent(QPaintEvent *e) override;
};

#endif // QHPUSHBUTTON_H
