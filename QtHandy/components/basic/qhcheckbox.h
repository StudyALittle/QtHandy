#ifndef QHCHECKBOX_H
#define QHCHECKBOX_H

#include <QCheckBox>
#include "QH_global.h"

class QhCheckBoxPrivate;

class QTHANDY_EXPORT QhCheckBox: public QCheckBox
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhCheckBox)

public:
    QhCheckBox(QWidget *parent = nullptr);
    QhCheckBox(const QString &text, QWidget *parent = nullptr);
    QhCheckBox(bool bLockState, const QString &text, QWidget *parent = nullptr);
    ~QhCheckBox();

    /// @brief Set whether to lock the current state
    void setLockState(bool b);

    /// @brief Is the current state locked(default false),
    /// Warning: Only lock the state switching triggered by clicking on the interface
    bool isLockState() const;

protected:
    void nextCheckState() override;
};

#endif // QHCHECKBOX_H
