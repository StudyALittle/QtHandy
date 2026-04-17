#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <qhdatabase.h>
#include "dirgroupdb.h"
#include "dirgroupdirdb.h"

class DBManager : public QObject
{
    Q_OBJECT

public:
    static DBManager &instance()
    {
        static DBManager manager;
        return manager;
    }

    ~DBManager();
    bool initDB(const QString &dbPath);

    QhDataBase &db()
    {
        return m_db;
    }

    DirGroupDB *dirGroupDB()
    {
        return m_dirGroupDB;
    };

    DirGroupDirDB *dirGroupDirDB()
    {
        return m_dirGroupDirDB;
    };

protected:
    DBManager();

private:
    QhDataBase m_db;

    DirGroupDB *m_dirGroupDB = nullptr;
    DirGroupDirDB *m_dirGroupDirDB = nullptr;
};

#endif // DBMANAGER_H
