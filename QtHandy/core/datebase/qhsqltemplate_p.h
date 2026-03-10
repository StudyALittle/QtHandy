#ifndef QHSQLTEMPLATE_P_H
#define QHSQLTEMPLATE_P_H

#include <QList>
#include <QMap>
#include <QDomDocument>
#include "qhsqltemplate.h"

class QhSqlTemplatePrivate
{
public:
    enum SqlFragmentType
    {
        EFT_Normal,
        EFT_ModeNameReplace,    // 模式名称替换
        EFT_ValueReplace,       // 值替换
        EFT_AESORDESCReplace,   // 排序方式替换
        EFT_LimitReplace,       // 限制数量替换
        EFT_OffsetReplace       // 偏移量替换
    };
    struct SqlFragment
    {
        SqlFragmentType type;
        QString strFragment;
    };

    struct SqlTemplate
    {
        QString name;                       // sql名称
        QString sql;                        // sql语句
        QList<SqlFragment> sqlFragments;    // sql片段
    };

    QhSqlTemplatePrivate();
    ~QhSqlTemplatePrivate();

    QDomDocument xmlDoc; // xml文档对象
    QString fileName;    // xml文件名称

    /// sql模板板，
    /// first:sql类型,
    /// second:
    ///     key:sql名称
    ///     value:sql模板
    QMap<QhSqlTemplate::SqlType, QMap<QString, SqlTemplate> > tempSqls;

    QString modeName;;      // 模式名称
    QString tableName;      // 表名称

    /// @brief 解析xml文件
    void parseXml();
    void parseSqls(QDomElement& sqlsElement);
    SqlTemplate parseSqlTemplate(const QString &name, const QString &sql);
};

#endif // QHSQLTEMPLATE_P_H
