#ifndef QHPUSHBUTTON_H
#define QHPUSHBUTTON_H

#include <QPushButton>
#include <qhlabel.h>
#include "qhqss.h"
#include "QH_global.h"

class QhPushButtonPrivate;

class QTHANDY_EXPORT QhPushButton: public QPushButton
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhPushButton)

//    Q_PROPERTY_EX(int, TextOffset)

public:
    QhPushButton(QWidget *parent = nullptr);
    QhPushButton(const QString &text, QWidget *parent = nullptr);
    QhPushButton(const QIcon &icon, const QString &text, QWidget *parent = nullptr);
    ~QhPushButton();

    bool isImageMode() const;

    /// @brief
    QString text() const;

    /// @brief
    QhLabel *textLabel() const;

    /// @brief
    QhLabel *iconLeft() const;

    /// @brief
    QhLabel *iconRight() const;

    /// @brief
    void setImageMode(bool b);

    /// @brief
    void setText(const QString &text);

    /// @brief
    // bool setProperty(const char *name, const QVariant &value);
    void attachPropertyState(const QString &value);

protected:
    void paintEvent(QPaintEvent *e) override;
};

#endif // QHPUSHBUTTON_H
