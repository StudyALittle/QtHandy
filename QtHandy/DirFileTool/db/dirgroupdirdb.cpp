#include "dirgroupdirdb.h"
#include <QDebug>
#include "dbmanager.h"

DirGroupDirDB::DirGroupDirDB() : QhSqlTemplate(":/resource/sql/dir_group_dir.xml")
{
}

int DirGroupDirDB::addDirGroupDir(const DirGroupDirModel &model)
{
    QString sql = this->getBindSql(QhSqlTemplate::SqlInsert, "add");
    qint64 id = 0;
    if (DBManager::instance().db().execAffectedRows(
            sql, &id, nullptr, {model.groupId, model.dirPath, model.sort, model.name, model.description}) < 0) {
        qDebug() << "Failed to add directory group directory:" << DBManager::instance().db().lastError().text();
        return -1;
    }
    return static_cast<int>(id);
}

bool DirGroupDirDB::updateDirGroupDir(const DirGroupDirModel &model)
{
    QString sql = this->getBindSql(QhSqlTemplate::SqlUpdate, "modify");
    if (!DBManager::instance().db().exec(
            sql, {model.groupId, model.dirPath, model.sort, model.name, model.description, model.id})) {
        qDebug() << "Failed to update directory group directory:" << DBManager::instance().db().lastError().text();
        return false;
    }
    return true;
}

bool DirGroupDirDB::deleteDirGroupDirById(int id)
{
    QString sql = this->getBindSql(QhSqlTemplate::SqlDelete, "removeById");
    if (!DBManager::instance().db().exec(sql, {id})) {
        qDebug() << "Failed to delete directory group directory:" << DBManager::instance().db().lastError().text();
        return false;
    }
    return true;
}

bool DirGroupDirDB::deleteDirGroupDirByGroupId(int groupId)
{
    QString sql = this->getBindSql(QhSqlTemplate::SqlDelete, "removeByGroupId");
    if (!DBManager::instance().db().exec(sql, {groupId})) {
        qDebug() << "Failed to delete directory group directories by group ID:"
                 << DBManager::instance().db().lastError().text();
        return false;
    }
    return true;
}

QList<DirGroupDirModel::Ptr> DirGroupDirDB::getDirGroupDirList()
{
    QString sql = this->getBindSql(QhSqlTemplate::SqlSelect, "query");
    auto data = DBManager::instance().db().query(sql);
    return tableDataToDirGroupDirs(data);
}

QMap<int,QList<DirGroupDirModel::Ptr>> DirGroupDirDB::dirGroupDirListToMap(const QList<DirGroupDirModel::Ptr>& list)
{
    QMap<int, QList<DirGroupDirModel::Ptr>> map;
    for (const auto &groupDir : list) {
        map[groupDir->groupId].append(groupDir);
    }
    return map;
}


QList<DirGroupDirModel::Ptr> DirGroupDirDB::tableDataToDirGroupDirs(const QhDataBase::Data &data)
{
    QList<DirGroupDirModel::Ptr> groupDirs;
    for (const auto &row : data) {
        auto groupDir = tableDataToDirGroupDirModel(row);
        if (groupDir)
            groupDirs.append(groupDir);
    }
    return groupDirs;
}

DirGroupDirModel::Ptr DirGroupDirDB::tableDataToDirGroupDirModel(const QhDataBase::Row &row)
{
    auto groupDir = DirGroupDirModel::Ptr(new DirGroupDirModel);
    groupDir->id = row.value("id").toInt();
    groupDir->groupId = row.value("group_id").toInt();
    groupDir->dirPath = row.value("dir_path").toString();
    groupDir->name = row.value("name").toString();
    groupDir->sort = row.value("sort").toInt();
    groupDir->description = row.value("description").toString();
    groupDir->createTime = row.value("create_time").toString();
    groupDir->updateTime = row.value("update_time").toString();
    return groupDir;
}
