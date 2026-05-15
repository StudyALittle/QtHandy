#ifndef QHSQLTEMPLATE_H
#define QHSQLTEMPLATE_H

#include <QObject>
#include "QH_global.h"

class QhSqlTemplatePrivate;

class QTHANDY_EXPORT QhSqlTemplate
{
    Q_PRIVATE_VARIABLE(QhSqlTemplate)

public:
    enum SqlType { SqlSelect, SqlInsert, SqlUpdate, SqlDelete };

    enum OrderType { OrderAsc, OrderDes };

    QhSqlTemplate(const QString &fileName);
    QhSqlTemplate(const QString &fileName, const QString &modeName);
    virtual ~QhSqlTemplate();

    QString modeName() const;
    QString tableName() const;

    void setModeName(const QString &modeName);

    /// @brief 获取绑定的sql语句
    /// @param type sql类型
    /// @param name sql名称
    /// @param limit 查询结果限制数量
    /// @param offset 查询结果偏移量
    /// @param orders 排序字段
    /// @param replace 绑定参数替换符
    QString getBindSql(SqlType type, const QString &name, qint64 limit, qint64 offset, QVector<OrderType> orders,
        const QString &replace = "?") const;

    QString getBindSql(
        SqlType type, const QString &name, qint64 limit, qint64 offset, const QString &replace = "?") const
    {
        return getBindSql(type, name, limit, offset, {}, replace);
    }

    QString getBindSql(SqlType type, const QString &name, QVector<OrderType> orders, const QString &replace = "?") const
    {
        return getBindSql(type, name, -1, -1, orders, replace);
    }

    QString getBindSql(SqlType type, const QString &name, const QString &replace = "?") const
    {
        return getBindSql(type, name, -1, -1, QVector<OrderType>{}, replace);
    }
};

#endif // QHSQLTEMPLATE_H
