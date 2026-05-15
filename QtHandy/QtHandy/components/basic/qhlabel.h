#ifndef QHLABEL_H
#define QHLABEL_H

#include <QLabel>
#include "QH_global.h"

class QhLabelPrivate;

class QTHANDY_EXPORT QhLabel: public QLabel
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhLabel)

public:
    enum RequiredMode {
        NoRequired,         // Not required
        Required,           // Required field label (Add "*" at the beginning of the text)
        RequiredPlaceholder // Required item label placeholder
    };

    QhLabel(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    QhLabel(const QString &text, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~QhLabel();

    QString text() const;

    QString placeholderText() const;

    /// @brief It is effective when WordWrap is set to true
    int maxLine() const;

    /// @brief Whether to display ellipsis when the text is too long
    bool isEllipsis() const;

    /// @brief Placeholder pattern
    RequiredMode requiredMode() const;

    /// @brief Mandatory field placeholder, such as "   "
    QString requiredPlaceholderText() const;

    /// @brief Mandatory field markers, such as "*"
    QString requiredMarkText() const;

    void setText(const QString &text);
    void setMaxLine(int n);
    void setEllipsis(bool b);
    void setRequiredMode(RequiredMode md);

    void setRequiredPlaceholderText(const QString &text);
    void setRequiredMarkText(const QString &text);

    void setPlaceholderText(const QString &text);

    void clear();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};

#endif // QHLABEL_H
