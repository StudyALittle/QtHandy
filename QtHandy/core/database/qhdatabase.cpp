#include "qhdatabase.h"
#include "qhdatabase_p.h"
#include <QSharedPointer>
#include <QFileInfo>
#include <QDir>
#include <QDebug>

QhDataBase::QhDataBase(QObject *parent) : QObject(parent), d(new QhDataBasePrivate(this))
{
}

QhDataBase::~QhDataBase()
{
}

QSqlDatabase &QhDataBase::db() const
{
    return d->db;
}

bool QhDataBase::open(const QString &ip, const int &port, const QString databaseName, const QString &userName,
    const QString &password, const QString &dbType, const QString &conName)
{
    bool bConName = QSqlDatabase::contains(conName);
    if (!bConName) {
        d->db = QSqlDatabase::addDatabase(dbType, conName);
    } else {
        d->db = QSqlDatabase::database(conName);
    }

    if (dbType == "QSQLITE") {
        QFileInfo finfo(databaseName);
        if (!finfo.dir().exists())
            finfo.dir().mkpath(finfo.dir().path());
        d->db.setDatabaseName(databaseName);
        d->db.setUserName(userName);
        d->db.setPassword(password);
    } else {
        d->db.setHostName(ip);
        d->db.setPort(port);
        d->db.setDatabaseName(databaseName);
        d->db.setUserName(userName);
        d->db.setPassword(password);
    }
    return d->db.open();
}

bool QhDataBase::open(const QString &path, const QString &userName, const QString &password, const QString &conName)
{
    return open(QString(), -1, path, userName, password, "QSQLITE", conName);
}

bool QhDataBase::isError() const
{
    return d->db.lastError().type() != QSqlError::NoError || d->sqlLastError.type() != QSqlError::NoError;
}

QStringList QhDataBase::tables(QSql::TableType type) const
{
    return d->db.tables(type);
}

QhDataBase::Data QhDataBase::query(const QString &sql, const QList<QVariant> &datas)
{
    Data data;
    auto sqlQuery = d->queryModel(sql, datas);

    int count = sqlQuery->rowCount();
    for (int i = 0; i < count; i++) {
        auto rec = sqlQuery->record(i);
        QMap<QString, QVariant> row;

        int countRec = rec.count();
        for (int j = 0; j < countRec; j++) {
            row.insert(rec.field(j).name().toLower(), rec.value(j));
        }
        data.append(row);
    }
    return data;
}

QSharedPointer<QSqlQuery> QhDataBase::queryExec(const QString &sql, const QList<QVariant> &datas)
{
    auto sqlQuery = QSharedPointer<QSqlQuery>::create(db());
    if (!d->queryExec(*sqlQuery, datas, sql)) { /*error*/
    }
    return sqlQuery;
}

qint64 QhDataBase::queryCount(const QString &sql, const QList<QVariant> &datas)
{
    qint64 count = -1;
    QSqlQuery query(db());
    if (!d->queryExec(query, datas, sql)) {
        return count;
    }

    if (query.next()) {
        count = query.value(0).toInt();
    }
    return count;
}

bool QhDataBase::exec(const QString &sql, const QList<QVariant> &datas)
{
    QSqlQuery query(db());
    return d->queryExec(query, datas, sql);
}

int QhDataBase::execAffectedRows(
    const QString &sql, qint64 *lastInsertId, qint64 *insertId, const QList<QVariant> &datas)
{
    QSqlQuery query(db());
    if (!d->queryExec(query, datas, sql)) {
        return -1; // 执行错误
    }

    if (insertId) {
        *insertId = query.next() ? query.value(0).toInt() : -1;
    }
    if (lastInsertId) {
        *lastInsertId = query.lastInsertId().toInt();
    }
    return query.numRowsAffected();
}

bool QhDataBase::transaction()
{
    bool ret = d->db.transaction();
    d->sqlLastError = db().lastError();
    return ret;
}

bool QhDataBase::commit()
{
    bool ret = d->db.commit();
    d->sqlLastError = db().lastError();
    return ret;
}

bool QhDataBase::rollback()
{
    bool ret = d->db.rollback();
    d->sqlLastError = db().lastError();
    return ret;
}

QSqlError QhDataBase::lastError() const
{
    return d->db.lastError();
}

QSharedPointer<QSqlQueryModel> QhDataBase::queryModel(const QString &sql, const QList<QVariant> &datas)
{
    return d->queryModel(sql, datas);
}

QhDataBasePrivate::QhDataBasePrivate(QhDataBase *q)
{
}

QhDataBasePrivate::~QhDataBasePrivate()
{
}

QSharedPointer<QSqlQueryModel> QhDataBasePrivate::queryModel(const QString &sql, const QList<QVariant> &datas)
{
    auto model = QSharedPointer<QSqlQueryModel>::create();

    QSqlQuery query(db);
    if (!queryExec(query, datas, sql)) {
        return model;
    }

    model->setQuery(query);
    while (model->canFetchMore()) {
        model->fetchMore();
    }
    return model;
}

bool QhDataBasePrivate::queryExec(QSqlQuery &sqlQuery, const QList<QVariant> &datas, const QString &sql)
{
    sqlLastError = QSqlError();

    auto doExec = [this](QSqlQuery &sqlQuery, const QList<QVariant> &datas, const QString &sql) -> bool {
        bool result = false;
        if (datas.isEmpty()) {
            result = sqlQuery.exec(sql);
        } else {
            if (!sqlQuery.prepare(sql)) {
                sqlLastError = sqlQuery.lastError();
                qWarning() << "sqlQuery prepare error: " << sqlLastError << "; db is open: " << db.isOpen();
                return result;
            }
            foreach (const QVariant &data, datas) {
                sqlQuery.addBindValue(data);
            }
            result = sqlQuery.exec();
        }
        return result;
    };

    bool result = doExec(sqlQuery, datas, sql);

    /// 连接错误,执行一次重连(连接可能被数据主动断开，目前只在mysql发现过)
    if (!result &&
        ("2006" == sqlQuery.lastError().nativeErrorCode() || "2013" == sqlQuery.lastError().nativeErrorCode())) {
        if (db.open()) {
            sqlQuery = QSqlQuery(db);
            result = doExec(sqlQuery, datas, sql);
        }
    }

    if (!result) {
        sqlLastError = sqlQuery.lastError();
        qWarning() << "sqlQuery exec error: " << sqlLastError.text();
    } else {
        sqlLastError = QSqlError();
    }
    return result;
}
