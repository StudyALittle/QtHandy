#ifndef QHIMAGEBUTTON_H
#define QHIMAGEBUTTON_H

#include <QPushButton>
#include "QH_global.h"

class QhImageButtonPrivate;

class QTHANDY_EXPORT QhImageButton: public QPushButton
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhImageButton)

    Q_PROPERTY_EX(QSize, LeftIconSize)
    Q_PROPERTY_EX(QString, LeftIconPath)
    Q_PROPERTY_EX(QSize, RightIconSize)
    Q_PROPERTY_EX(QString, RightIconPath)
    Q_PROPERTY_EX(int, TextOffset)

public:
    QhImageButton(QWidget *parent = nullptr);
    QhImageButton(const QString &text, QWidget *parent = nullptr);
    ~QhImageButton();

    QString text() const;
    bool isLeftIconVisible() const;
    bool isRightIconVisible() const;

    void setText(const QString &text);
    void setLeftIconVisible(bool b);
    void setRightIconVisible(bool b);

    /// Q_PROPERTY
    QSize getLeftIconSize() const;
    QString getLeftIconPath() const;
    QSize getRightIconSize() const;
    QString getRightIconPath() const;
    int getTextOffset() const;

    void setLeftIconSize(const QSize &size);
    void setLeftIconPath(const QString &path);
    void setRightIconSize(const QSize &size);
    void setRightIconPath(const QString &path);
    void setTextOffset(int n);

protected:
    void paintEvent(QPaintEvent *e) override;
};

#endif // QHIMAGEBUTTON_H
