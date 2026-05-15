#ifndef QHNAVBAR_H
#define QHNAVBAR_H

#include <QWidget>
#include "qhnavbaritem.h"
#include "QH_global.h"

class QhNavbarProxy;
class QhNavbarPrivate;

class QTHANDY_EXPORT QhNavbar: public QWidget
{
    Q_OBJECT

public:
    /// @brief The Direction enum
    enum Direction { Vertical, Horizontal, CustomDirection };

    /// @brief The Position enum
    enum Position { Left, Right, Top, Bottom, Equality, CustomPosition };

    QhNavbar(int direction, int  position,
        QhNavbarProxy *proxy, QWidget *parent = nullptr);
    ~QhNavbar();

    QhNavbarProxy *navbarProxy() const;

    int direction() const;
    int position() const;

    QList<QhNavbarItem*> items() const;
    QhNavbarItem *item(qint64 id) const;
    QhNavbarItem *checkedItem() const;
    QhNavbarItem *lastCheckedItem() const;
    QhNavbarItem* parentItem(qint64 id) const;

    bool isChildChecked(QhNavbarItem *item) const;
    bool isChildExpand(QhNavbarItem *item) const;

    int itemLevel(QhNavbarItem *item) const;
    int itemSpace(qint64 pid, int level = 1) const;

    void setItems(const QList<QhNavbarItem*> &items);

    void setChecked(qint64 id, bool bExpand = true);
    void setItemSpace(int space, qint64 pid, int level = 1);
    void setItemChildExpand(QhNavbarItem *item, bool bExpand);
    void setItemParentExpand(QhNavbarItem *item, bool bExpand);

    QLayout *getLayout(qint64 pid, int level);

signals:
    void itemChecked(qint64 id);

protected:
    QhNavbarItem *item(const QList<QhNavbarItem*> &items, qint64 id) const;
    QhNavbarItem *checkedItem(const QList<QhNavbarItem*> &items) const;
    QhNavbarItem* parentItem(const QList<QhNavbarItem*> &items, qint64 id) const;
    bool isExistChecked(const QList<QhNavbarItem*> &items) const;
    int itemLevel(const QList<QhNavbarItem*> &items, qint64 id, int level) const;
    int itemCount() const;
    void itemCount(const QList<QhNavbarItem*> &items, int &cnt) const;

    void recordLayout(qint64 pid, int level, QLayout *layout);
    void removeLayout(qint64 pid, int level);

    void setItemsToLayout(const QList<QhNavbarItem*> &items);
    void setItemsToLayout(const QList<QhNavbarItem*> &items, qint64 pid, int level);

protected slots:
    void onItemClicked(qint64 id);

private:
    QhNavbarPrivate *d;
    Q_DISABLE_COPY(QhNavbar)
    friend class QhNavbarPrivate;
    friend class QhNavbarProxy;
};

#endif // QHNAVBAR_H
