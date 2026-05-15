#ifndef QHNAVBARITEM_H
#define QHNAVBARITEM_H

#include <QWidget>
#include <QVariant>
#include "QH_global.h"

class QhNavbar;
class QhNavbarProxy;
class QhNavbarItemPrivate;

class QTHANDY_EXPORT QhNavbarItem: public QObject
{
    Q_OBJECT

public:
    constexpr static qint64 INVALIDID = -99999999; // 无效ID

    QhNavbarItem(qint64 id, QObject *parent = nullptr);
    QhNavbarItem(qint64 id, const QString &name, QObject *parent = nullptr);
    QhNavbarItem(qint64 id, const QString &name,
        const QList<QhNavbarItem*> &childs,
        const QVariant &customParam = QVariant(), QObject *parent = nullptr);
    ~QhNavbarItem();

    qint64 id() const;
    QString name() const;
    QList<QhNavbarItem*> childItems() const;
    QVariant customParam() const;

    bool isChecked() const;
    bool isChildExpand() const;

    QWidget *widget() const;

    template<class T>
    T *widgetConvert() const { return static_cast<T*>(widget()); }

    void setName(const QString &name);

protected:
    void setChecked(bool b);
    void setChildExpand(bool b);
    void setWidget(QWidget *w);
    void setNavbar(QhNavbar *navbar);

private:
    QhNavbarItemPrivate *d;
    Q_DISABLE_COPY(QhNavbarItem)
    friend class QhNavbarItemPrivate;
    friend class QhNavbar;
};

#endif // QHNAVBARITEM_H
