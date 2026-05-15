#ifndef QHDATABASE_P_H
#define QHDATABASE_P_H

#include "qhdatabase.h"

class QhDataBasePrivate
{
public:
    QhDataBasePrivate(QhDataBase *q);
    ~QhDataBasePrivate();

    QhDataBase *ptr;
    QSqlDatabase db;
    QSqlError sqlLastError;

    QSharedPointer<QSqlQueryModel> queryModel(
        const QString& sql, const QList<QVariant> &datas = QList<QVariant>());

    bool queryExec(QSqlQuery& sqlQuery,
        const QList<QVariant> &datas,
        const QString& sql = QString());
};

#endif // QHDATABASE_P_H
