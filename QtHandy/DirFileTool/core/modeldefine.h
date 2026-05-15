#ifndef MODELDEFINE_H
#define MODELDEFINE_H

#include <QString>
#include <QSharedPointer>

struct DirGroupModel
{
    using Ptr = QSharedPointer<DirGroupModel>;

    int id;
    int parentId;
    QString name;
    int sort;
    QString description;
    QString createTime;
    QString updateTime;

    QList<DirGroupModel::Ptr> childList;
};

struct DirGroupDirModel
{
    using Ptr = QSharedPointer<DirGroupDirModel>;
    
    int id;
    int groupId;
    QString dirPath;
    QString name;
    int sort;
    QString description;
    QString createTime;
    QString updateTime;
};

#endif // MODELDEFINE_H
