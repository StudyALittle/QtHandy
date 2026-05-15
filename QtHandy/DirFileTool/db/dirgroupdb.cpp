#include "dirgroupdb.h"
#include <QDebug>
#include "dbmanager.h"

DirGroupDB::DirGroupDB() : QhSqlTemplate(":/resource/sql/dir_group.xml")
{
}

int DirGroupDB::addDirGroup(const DirGroupModel &model)
{
    QString sql = this->getBindSql(QhSqlTemplate::SqlInsert, "add");
    qint64 id = 0;
    if (DBManager::instance().db().execAffectedRows(
            sql, &id, nullptr, {model.parentId, model.name, model.sort, model.description}) < 0) {
        qDebug() << "Failed to add directory group:" << DBManager::instance().db().lastError().text();
        return -1;
    }
    return static_cast<int>(id);
}

bool DirGroupDB::updateDirGroup(const DirGroupModel &model)
{
    QString sql = this->getBindSql(QhSqlTemplate::SqlUpdate, "modify");
    if (!DBManager::instance().db().exec(sql, {model.parentId, model.name, model.sort, model.description, model.id})) {
        qDebug() << "Failed to update directory group:" << DBManager::instance().db().lastError().text();
        return false;
    }
    return true;
}

bool DirGroupDB::deleteDirGroup(int id)
{
    QString sql = this->getBindSql(QhSqlTemplate::SqlDelete, "remove");
    if (!DBManager::instance().db().exec(sql, {id})) {
        qDebug() << "Failed to delete directory group:" << DBManager::instance().db().lastError().text();
        return false;
    }
    return true;
}

QList<DirGroupModel::Ptr> DirGroupDB::getDirGroupList()
{
    QString sql = this->getBindSql(QhSqlTemplate::SqlSelect, "query");
    auto data = DBManager::instance().db().query(sql);
    return tableDataToDirGroups(data);
}

QList<DirGroupModel::Ptr> DirGroupDB::listToTree(const QList<DirGroupModel::Ptr> &list)
{
    QList<DirGroupModel::Ptr> trees;
    for (auto &item : list) {
        if (item->parentId == -1) {
            trees.append(item);
        } else {
            for (auto &parent : list) {
                if (parent->id == item->parentId) {
                    parent->childList.append(item);
                    break;
                }
            }
        }
    }
    return trees;
}

QList<DirGroupModel::Ptr> DirGroupDB::tableDataToDirGroups(const QhDataBase::Data &data)
{
    QList<DirGroupModel::Ptr> groups;
    for (const auto &row : data) {
        auto group = tableDataToDirGroupModel(row);
        if (group)
            groups.append(group);
    }
    return groups;
}

DirGroupModel::Ptr DirGroupDB::tableDataToDirGroupModel(const QhDataBase::Row &row)
{
    auto group = DirGroupModel::Ptr(new DirGroupModel);
    group->id = row.value("id").toInt();
    group->parentId = row.value("parent_id").toInt();
    group->name = row.value("name").toString();
    group->sort = row.value("sort").toInt();
    group->description = row.value("description").toString();
    group->createTime = row.value("create_time").toString();
    group->updateTime = row.value("update_time").toString();
    return group;
}
