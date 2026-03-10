#ifndef QHLINEEDIT_H
#define QHLINEEDIT_H

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include "QH_global.h"

class QhLineEditSub;
class QhLineEditPrivate;
class QhLineEditLeftPrivate;
class QhLineEditRightPrivate;

class QTHANDY_EXPORT QhLineEdit: public QLineEdit
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhLineEdit)

    Q_PROPERTY_EX(QString, LayoutMargins)

public:
    QhLineEdit(QWidget *parent = nullptr);
    QhLineEdit(const QString &contents, QWidget *parent = nullptr);
    QhLineEdit(QhLineEditSub *leftWidget, QhLineEditSub *rightWidget, QWidget *parent = nullptr);
    ~QhLineEdit();

    QhLineEditSub *leftWidget() const;
    template<class T>
    T leftWidgetC() const { return static_cast<T>(leftWidget()); }

    QhLineEditSub *rightWidget() const;
    template<class T>
    T rightWidgetC() const { return static_cast<T>(rightWidget()); }

    QMargins textMargins() const;

    void setTextMargins(int left, int top, int right, int bottom);
    void setTextMargins(const QMargins &margins);

    void resetMargin();

    /// Validate

    /// @brief Is the text validation effective
    /// note: It takes effect only after setting the Validator
    bool isTextValidateValid();

    /// @brief Input text verification function,
    /// If there is a verification error, return false
    void setTextValidate(std::function<bool(QhLineEdit*)> func);

    /// @brief Set validator
    /// @param valid: validator
    /// @param bEmptyNoError: When true, An empty string indicates a correct format
    void setTextValidator(const QValidator *validator, bool bEmptyNoError = false);

    /// Q_PROPERTY
    QString getLayoutMargins() const;
    void setLayoutMargins(const QString &str);

signals:
    void focusIn();
    void focusOut();
    void clicked();

protected:
    void resizeEvent(QResizeEvent *e) override;
    void showEvent(QShowEvent *e) override;
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

class QTHANDY_EXPORT QhLineEditSub: public QWidget
{
    Q_OBJECT
    friend class QhLineEdit;
    friend class QhLineEditPrivate;

public:
    QhLineEditSub(QWidget *parent = nullptr);
    ~QhLineEditSub();

    virtual int validWidth() = 0;

protected:
    QhLineEdit *lineEdit = nullptr;
};

class QTHANDY_EXPORT QhLineEditLeft: public QhLineEditSub
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhLineEditLeft)

public:
    QhLineEditLeft(QWidget *parent = nullptr);
    ~QhLineEditLeft();

    QLabel *label();
    int validWidth() override;
};

class QTHANDY_EXPORT QhLineEditRight: public QhLineEditSub
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhLineEditRight)

public:
    QhLineEditRight(QWidget *parent = nullptr);
    ~QhLineEditRight();

    QAbstractButton *button();
    int validWidth() override;

    void setPasswdModeEnable(bool bPasswd);
    void setPasswdMode(bool bPasswd);
    void switchPasswdMode();

signals:
    void clicked(bool checked = false);
};

#endif // QHLINEEDIT_H
