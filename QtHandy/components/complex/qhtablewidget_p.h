#ifndef QHTABLEWIDGET_P_H
#define QHTABLEWIDGET_P_H

#include <QAbstractItemView>
#include "qhtablewidget.h"
#include "qhtablewidgetitem.h"

class QhTableWidgetPrivate : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QhTableWidgetPrivate)

public:
    QhTableWidgetPrivate(QhTableWidget *tbw);
    ~QhTableWidgetPrivate();

    void init();
    void initFrozenTable();
    void initFrozenTable(QTableWidget **tb, QhHeaderView **header, int columnCount);
    void updateItemSize();
    void updateFrozenTableGeometry(int behindWidth = -1);
    int columnToFrozenBehind(int column);
    int columnFromFrozenBehind(int column);

    QhTableWidget *tableWidget;
    QhHeaderView *hHeaderView;
    QList<QhTableWidgetItem *> hItems;

    // 冻结前面的表格（一般用于复选框选择）
    bool bInitFrozenTableFront = false;
    QTableWidget *frozenTableFront = nullptr;
    QhHeaderView *hHeaderViewFront = nullptr;
    // 冻结后面的表格（一般用于放置操作按钮）
    bool bInitFrozenTableBehind = false;
    QTableWidget *frozenTableBehind = nullptr;
    QhHeaderView *hHeaderViewBehind = nullptr;
};

class QTHANDY_EXPORT QhTableWidgetItemPrivate
{
public:
    QhTableWidgetItemPrivate()
    {
    }
    ~QhTableWidgetItemPrivate()
    {
    }

    int index;                         // 索引
    QString name;                      // 项名称
    int size = 50;                     // 大小
    bool bFillRemaiSize = false;       // 补齐剩余的大小，只有一个有效
    QTableWidgetItem *item = nullptr;  // qt item
    QhHeaderViewItem *hitem = nullptr; // 表头自定义item
};

#endif // QHTABLEWIDGET_P_H
