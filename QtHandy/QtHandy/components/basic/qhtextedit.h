#ifndef QHTEXTEDIT_H
#define QHTEXTEDIT_H

#include <QLabel>
#include <QTextEdit>
#include "QH_global.h"

class QhTextEditPrivate;

class QTHANDY_EXPORT QhTextEdit: public QTextEdit
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhTextEdit)

    Q_PROPERTY_EX(QString, LabelMargins)

public:
    QhTextEdit(QWidget *parent = nullptr);
    QhTextEdit(const QString &text, QWidget *parent = nullptr);
    ~QhTextEdit();

    /// @brief Maximum text length that can be input
    int textMaxLenght();

    /// @brief Set the maximum input text length
    /// note: When it is less than or equal to 0, there is no length restriction
    void setTextMaxLenght(int len);

    /// Q_PROPERTY
    QString getLabelMargins() const;
    void setLabelMargins(const QString &str);

protected:
    void resizeEvent(QResizeEvent *e) override;
};

#endif // QHTEXTEDIT_H
