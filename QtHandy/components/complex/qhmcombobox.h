#ifndef QHMCOMBOBOX_H
#define QHMCOMBOBOX_H

/**
 * @file       qhmcombobox.h
 * @brief      多选下拉框
 *
 * @author     wmz
 * @date       2026/06/30
 * @history
 */

#include "qhcombobox.h"
#include "QH_global.h"

class QhMComboBoxPrivate;

class QTHANDY_EXPORT QhMComboBox: public QhComboBox
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhMComboBox)

public:
    QhMComboBox(QWidget *parent = nullptr);
    ~QhMComboBox();

    void addItem(const QString &text, const QVariant &userData = QVariant());
    void addItems(const QStringList &texts);

    void setSelects(const QStringList &texts);

    QStringList selectTexts() const;

    void hidePopup() override;
    void showPopup() override;
};

#endif // QHMCOMBOBOX_H
