#include "qhsqltemplate.h"
#include "qhsqltemplate_p.h"
#include <QFile>
#include <QDomComment>
#include <QDebug>

QhSqlTemplate::QhSqlTemplate(const QString &fileName):
    d(new QhSqlTemplatePrivate)
{
    d->fileName = fileName;
    d->parseXml();
}

QhSqlTemplate::QhSqlTemplate(const QString &fileName, const QString &modeName):
    d(new QhSqlTemplatePrivate)
{
    d->fileName = fileName;
    d->modeName = modeName;
    d->parseXml();
}

QhSqlTemplate::~QhSqlTemplate()
{

}

QString QhSqlTemplate::modeName() const
{
    return d->modeName;
}

QString QhSqlTemplate::tableName() const
{
    return d->tableName;
}

void QhSqlTemplate::setModeName(const QString &modeName)
{
    d->modeName = modeName;
}

QString QhSqlTemplate::getBindSql(SqlType type,
    const QString &name, qint64 limit, qint64 offset,
    QVector<OrderType> orders, const QString &replace) const
{
    QString sql;
    if (!d->tempSqls.contains(type))
        return sql;

    auto &typeSqls = d->tempSqls[type];
    if (!typeSqls.contains(name))
        return sql;

    auto sqlTemplate = typeSqls.value(name);

    // 替换orderBy
    if (orders.size() > 0) {
        int index = 0;
        for (int n = 0; n < sqlTemplate.sqlFragments.size(); ++n) {
            auto &frag = sqlTemplate.sqlFragments[n];
            if (frag.type != QhSqlTemplatePrivate::EFT_AESORDESCReplace) {
                continue;
            }

            if (index < orders.size()) {
                frag.strFragment = (orders[index] == OrderAsc ? "ASC" : "DESC");
            }
            if (++index >= orders.size()) {
                break;
            }
        }
    }

    for (int n = 0; n < sqlTemplate.sqlFragments.size(); ++n) {
        auto &frag = sqlTemplate.sqlFragments[n];
        switch (frag.type)
        {
        case QhSqlTemplatePrivate::EFT_Normal: {
            sql += frag.strFragment;
            break;
        }
        case QhSqlTemplatePrivate::EFT_ModeNameReplace: {
            sql += d->modeName;
            break;
        }
        case QhSqlTemplatePrivate::EFT_ValueReplace: {
            sql += replace;
            break;
        }
        case QhSqlTemplatePrivate::EFT_AESORDESCReplace: {
            sql += frag.strFragment;
            break;
        }
        case QhSqlTemplatePrivate::EFT_LimitReplace: {
            if (limit >= 0)
                sql += QString::number(limit);
            break;
        }
        case QhSqlTemplatePrivate::EFT_OffsetReplace: {
            if (offset >= 0)
                sql += QString::number(offset);
            break;
        }
        default:
            break;
        }
    }

    return sql;
}

QhSqlTemplatePrivate::QhSqlTemplatePrivate()
{

}

QhSqlTemplatePrivate::~QhSqlTemplatePrivate()
{

}

// <user>
// <insert>
//     <addUser des="添加用户">
//         INSERt INTO user (name, nickname, account, password, sex, phone, email)
//         VALUES (:name, :nickname, :account, :password, :sex, :phone, :email);
//     </addUser>
// </insert>
// </user>
void QhSqlTemplatePrivate::parseXml()
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "error open sql template file：" << file.errorString();
        return;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qDebug() << "error doc setContent";
        return;
    }

    QDomElement docElem = doc.documentElement();
    tableName = docElem.tagName();

    QDomNodeList nodeList = docElem.childNodes();
    for (int i = 0; i < nodeList.size(); ++i) {
        QDomElement element = nodeList.at(i).toElement();
        if (element.isNull()) {
            continue;
        }

        parseSqls(element);
    }
}

void QhSqlTemplatePrivate::parseSqls(QDomElement &sqlsElement)
{
    QhSqlTemplate::SqlType sqlType;
    QString tagName = sqlsElement.tagName();

    if (tagName == "insert") {
        sqlType = QhSqlTemplate::SqlInsert;
    } else if (tagName == "update") {
        sqlType = QhSqlTemplate::SqlUpdate;
    } else if (tagName == "delete") {
        sqlType = QhSqlTemplate::SqlDelete;
    } else if (tagName == "select") {
        sqlType = QhSqlTemplate::SqlSelect;
    } else {
        qDebug() << "error sql type: " << tagName;
        return;
    }

    QDomNodeList nodeList = sqlsElement.childNodes();
    for (int i = 0; i < nodeList.size(); ++i) {
        QDomElement element = nodeList.at(i).toElement();
        if (element.isNull()) {
            continue;
        }

        QString sqlName = element.tagName();
        QString sql = element.text().simplified();

        if (sql.isEmpty() || sqlName.isEmpty()) {
            qDebug() << "error sql: " << sqlName;
            continue;
        }

        tempSqls[sqlType].insert(sqlName, parseSqlTemplate(sqlName, sql));
    }
}

QhSqlTemplatePrivate::SqlTemplate QhSqlTemplatePrivate::parseSqlTemplate(const QString &name, const QString &sql)
{
    SqlTemplate sqlTemplate;
    sqlTemplate.name = name;
    sqlTemplate.sql = sql;

    QString _sql = sql;
    while (true) {
        // 找到类型前面的
        int pos = _sql.indexOf(":", 0);
        if (pos < 0) {
            // 结束
            sqlTemplate.sqlFragments.append(SqlFragment{
                SqlFragmentType::EFT_Normal, _sql
            });
            break;
        }

        // 剪切前面的
        QString fragLeft = _sql.left(pos);
        if (!fragLeft.isEmpty()) {
            sqlTemplate.sqlFragments.append(SqlFragment{
                SqlFragmentType::EFT_Normal, fragLeft
            });
            _sql.remove(0, pos);
        }

        static QStringList replaceList = {":[AESORDESC]", ":[LIMIT]", ":[OFFSET]", ":[MODENAME]"};

        // 根据类型剪切片段
        if (_sql.startsWith(replaceList.at(0))) {
            _sql.remove(0, replaceList.at(0).length());
            sqlTemplate.sqlFragments.append(
                SqlFragment{SqlFragmentType::EFT_AESORDESCReplace, replaceList.at(0)});
            continue;
        } else if (_sql.startsWith(replaceList.at(1))) {
            _sql.remove(0, replaceList.at(1).length());
            sqlTemplate.sqlFragments.append(
                SqlFragment{SqlFragmentType::EFT_LimitReplace, replaceList.at(1)});
            continue;
        } else if (_sql.startsWith(replaceList.at(2))) {
            _sql.remove(0, replaceList.at(2).length());
            sqlTemplate.sqlFragments.append(
                SqlFragment{SqlFragmentType::EFT_OffsetReplace, replaceList.at(2)});
            continue;
        } else if (_sql.startsWith(replaceList.at(3))) {
            _sql.remove(0, replaceList.at(3).length());
            sqlTemplate.sqlFragments.append(
                SqlFragment{SqlFragmentType::EFT_ModeNameReplace, replaceList.at(3)});
            continue;
        } else {
            // 找到空格和逗号
            int posSpace = _sql.indexOf(" ");
            int posComma = _sql.indexOf(",");
            if (posSpace < 0 && posComma < 0) {
                // 找不到空格和逗号, 找括号结束
                posSpace = _sql.indexOf(")");
                if (posSpace < 0) {
                    // 找分号结束
                    posSpace = _sql.indexOf(";");
                    if (posSpace < 0) {
                        sqlTemplate.sqlFragments.append(
                            SqlFragment{SqlFragmentType::EFT_ValueReplace, _sql});
                        break;
                    }
                }
            } else if (posSpace >= 0 && posComma >= 0) {
                // 以最先找到的为主
                posSpace = qMin(posSpace, posComma);
            } else if (posComma >= 0) {
                posSpace = posComma;
            }

            sqlTemplate.sqlFragments.append(
                SqlFragment{SqlFragmentType::EFT_ValueReplace, _sql.left(posSpace)});
            _sql.remove(0, posSpace);
        }
    }

    return sqlTemplate;
}
