#include "dbmanager.h"
#include <QFile>
#include <QDebug>
#include <qhdefine.h>

DBManager::DBManager()
{
}

DBManager::~DBManager()
{
    DELETE_OBJECT(m_dirGroupDB)
    DELETE_OBJECT(m_dirGroupDirDB)
}

bool DBManager::initDB(const QString& dbPath)
{
    bool ret = m_db.open(dbPath, "test", "test");
    if (!ret) {
        qDebug() << "Failed to open db:" << m_db.lastError().text();
        return false;
    }

    /// 创建表
    auto createTable = [this](const QString& path) {
        QFile sqlFile(path);
        if (sqlFile.open(QIODevice::ReadOnly)) {
            QString sql = sqlFile.readAll();
            m_db.exec(sql);
            sqlFile.close();
        } else {
            qDebug() << "Failed to open SQL file:" << sqlFile.errorString();
            return false;
        }
        return true;
    };

    if (!createTable(":/resource/sql/dir_group.sql")) {
        return false;
    }
    if (!createTable(":/resource/sql/dir_group_dir.sql")) {
        return false;
    }

    m_dirGroupDB = new DirGroupDB;
    m_dirGroupDirDB = new DirGroupDirDB;

    return ret;
}
