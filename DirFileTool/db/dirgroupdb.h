#ifndef DIRGROUPDB_H
#define DIRGROUPDB_H

#include <qhsqltemplate.h>
#include <qhdatabase.h>
#include "core/modeldefine.h"

class DirGroupDB : public QhSqlTemplate
{
public:
    DirGroupDB();

    int addDirGroup(const DirGroupModel &model);
    bool updateDirGroup(const DirGroupModel &model);
    bool deleteDirGroup(int id);
    QList<DirGroupModel::Ptr> getDirGroupList();

    static QList<DirGroupModel::Ptr> listToTree(const QList<DirGroupModel::Ptr> &list);

private:
    QList<DirGroupModel::Ptr> tableDataToDirGroups(const QhDataBase::Data &data);
    DirGroupModel::Ptr tableDataToDirGroupModel(const QhDataBase::Row &row);
};

#endif // DIRGROUPDB_H
