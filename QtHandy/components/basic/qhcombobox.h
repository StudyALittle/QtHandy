#ifndef QHCOMBOBOX_H
#define QHCOMBOBOX_H

#include <QComboBox>
#include "QH_global.h"

class QhComboBoxPrivate;

class QTHANDY_EXPORT QhComboBox: public QComboBox
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhComboBox)

public:
    QhComboBox(QWidget *parent = nullptr);
    QhComboBox(bool bModifyByWheel, QWidget *parent = nullptr);
    ~QhComboBox();

    /// @brief Can the values be switched using the mouse wheel(default false)
    bool isModifyByWheel() const;

    void setModifyByWheel(bool b);

    void clearItems();

protected:
    void wheelEvent(QWheelEvent *e) override;
};

#endif // QHCOMBOBOX_H
