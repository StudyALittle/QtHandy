#ifndef QHDATABASE_H
#define QHDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSharedPointer>
#include "QH_global.h"

class QhDataBasePrivate;

class QTHANDY_EXPORT QhDataBase : public QObject
{
    Q_OBJECT
    Q_PRIVATE_VARIABLE(QhDataBase)

public:
    using Row = QMap<QString, QVariant>;
    using Data = QList<Row>;

    QhDataBase(QObject *parent = nullptr);
    ~QhDataBase();

    QSqlDatabase &db() const;

    bool open(const QString &ip, const int &port, const QString databaseName, const QString &userName,
        const QString &password, const QString &dbType = "QDM", const QString &conName = "default");

    bool isError() const;

    /// @brief tables
    QStringList tables(QSql::TableType type = QSql::Tables) const;

    /// @brief 查询数据
    Data query(const QString &sql, const QList<QVariant> &datas = {});

    template <class T>
    void query(QList<T> &out, const QString &sql, const QList<QVariant> &datas = QList<QVariant>())
    {
        auto sqlQuery = queryModel(sql, datas);

        int count = sqlQuery->rowCount();
        for (int i = 0; i < count; i++) {
            auto rec = sqlQuery->record(i);

            T row;
            int countRec = rec.count();
            for (int j = 0; j < countRec; j++) {
                row.setDBFiledValue(rec.field(j).name(), rec.value(j));
            }
            out.append(row);
        }

        return out;
    }

    /// @brief query：查询数据
    /// @param sql：sql语句
    /// @param datas：绑定参数
    /// @return
    QSharedPointer<QSqlQuery> queryExec(const QString &sql, const QList<QVariant> &datas = QList<QVariant>());

    /// @brief queryCount：查询数据条数(返回-1表示语句执行错误)
    /// @param sql：sql语句
    /// @param datas：绑定参数
    /// @return
    qint64 queryCount(const QString &sql, const QList<QVariant> &datas = QList<QVariant>());

    /// @brief exec：执行数据
    /// @param sql：sql语句
    /// @return
    bool exec(const QString &sql, const QList<QVariant> &datas = {});

    /// @brief execAffectedRows：执行数据（返回成功条数）
    /// @param sql：sql语句
    /// @param lastInsertId：返回插入数据的ID
    /// @param insertId：返回插入数据的ID，目前只对高斯数据库（插入语句示例：INSERT INTO user (name) VALUES ('u3')
    /// RETURNING id;）
    /// @param datas：绑定参数
    /// @return 错误返回值小于0
    int execAffectedRows(const QString &sql, qint64 *lastInsertId = nullptr, qint64 *insertId = nullptr,
        const QList<QVariant> &datas = QList<QVariant>());
    int execAffectedRows(const QString &sql, const QList<QVariant> &datas = QList<QVariant>())
    {
        return execAffectedRows(sql, nullptr, nullptr, datas);
    }

    /// @brief transaction：开启事务
    bool transaction();

    /// @brief commit：提交事务
    bool commit();

    /// @brief rollback：回滚事务
    bool rollback();

protected:
    QSharedPointer<QSqlQueryModel> queryModel(const QString &sql, const QList<QVariant> &datas = QList<QVariant>());
};

#endif // QHDATABASE_H
