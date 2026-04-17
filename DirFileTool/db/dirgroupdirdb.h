#ifndef DIRGROUPDIRDB_H
#define DIRGROUPDIRDB_H

#include <qhsqltemplate.h>
#include <qhdatabase.h>
#include "core/modeldefine.h"

class DirGroupDirDB : public QhSqlTemplate
{
public:
    DirGroupDirDB();

    int addDirGroupDir(const DirGroupDirModel &model);
    bool updateDirGroupDir(const DirGroupDirModel &model);
    bool deleteDirGroupDirById(int id);
    bool deleteDirGroupDirByGroupId(int groupId);
    QList<DirGroupDirModel::Ptr> getDirGroupDirList();

    static QMap<int, QList<DirGroupDirModel::Ptr> > dirGroupDirListToMap(const QList<DirGroupDirModel::Ptr> &list);

protected:
    QList<DirGroupDirModel::Ptr> tableDataToDirGroupDirs(const QhDataBase::Data &data);
    DirGroupDirModel::Ptr tableDataToDirGroupDirModel(const QhDataBase::Row &row);
};

#endif // DIRGROUPDIRDB_H
