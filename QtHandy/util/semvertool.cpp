#include "semvertool.h"

using namespace semvertool;

SemverVersion::SemverVersion()
{

}

SemverVersion::SemverVersion(const QString &str)
{
    m_originalStr = str;
    m_ver = fromString(str).version();
}

SemverVersion::SemverVersion(const Version &ver)
{
    m_ver = ver;
}

SemverVersion::SemverVersion(const Version &ver, const QString &originalStr)
{
    m_ver = ver;
    m_originalStr = originalStr;
}

/// 返回版本信息
Version SemverVersion::version() const
{
    return m_ver;
}

EVerCompareType SemverVersion::compare(const SemverVersion &sver1, const SemverVersion &sver2)
{
    return compare(sver1.version(), sver2.version());
}

EVerCompareType SemverVersion::compare(const Version &ver1, const Version &ver2)
{
    auto cklistisAllZero = [](const QVector<QString> &vec, int index = 0)
    {
        for (int n = index; n < vec.size(); ++n) {
            for (int m = 0; m < vec.at(n).size(); ++m) {
                if (vec.at(n).at(m) != '0')
                    return false;
            }
            // if (vec.at(n) != "0")
            //     return false;
        }
        return true;
    };

    auto regItems = [](const QString &text)
    {
        QList<QString> list;
        int lastIndex = 0;
        QRegularExpression pattern(QRegularExpression::escape(QString(g_strRegularPar)));
        auto matchIterator = pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            if (!match.capturedLength())
                continue;

            int matchLen = match.capturedEnd() - match.capturedStart();
            QString textNormal = text.mid(lastIndex, match.capturedStart() - lastIndex);
            if (!textNormal.isEmpty())
                list.append(textNormal);
            lastIndex = match.capturedStart() + matchLen;
        }
        auto strEnd = text.mid(lastIndex, text.size() - lastIndex);
        if (!strEnd.isEmpty())
            list.append(strEnd);

        return list;
    };

    auto comItem = [](const QString &str1, const QString &str2)
    {
        if (str1 == str2)
            return E_VCT_Equal;

        bool bOk1, bOk2;
        quint64 n1 = str1.toULongLong(&bOk1);
        quint64 n2 = str2.toULongLong(&bOk2);

        // 只有数字的标识符以数值高低比较。
        if (bOk1 && bOk2) {
            if (n1 > n2)
                return E_VCT_Greater;
            else if (n1 < n2)
                return E_VCT_Less;

            return E_VCT_Equal;
        }

        // 数字的标识符比非数字的标识符优先层级低。
        if (bOk1 && !bOk2)
            return E_VCT_Less;
        else if (bOk2 && !bOk1)
            return E_VCT_Greater;

        // 有字母或连接号时则逐字以 ASCII 的排序来比较。
        int n = 0;
        for (;; ++n) {
            if (n < str1.size() && n < str2.size()) {
                if (str1.at(n) < str2.at(n))
                    return E_VCT_Less;
                if (str1.at(n) > str2.at(n))
                    return E_VCT_Greater;
                continue;
            }
            break;
        }

        if (str1.size() > str2.size())
            return E_VCT_Greater;
        if (str1.size() < str2.size())
            return E_VCT_Less;

        return E_VCT_Equal;
    };

    if (!ver1.isValid() || !ver2.isValid())
        return E_VCT_Invalid;

    // 1:0 1:2 1:1
    SEMVER_NUM_COMPER(first)
    SEMVER_NUM_COMPER(major)
    SEMVER_NUM_COMPER(minor)
    SEMVER_NUM_COMPER(micro)

    // micro后面的数据比较：2024.0.3.20 比较 2025.0.7
    for (int n = 3; n < ver1.segments.size()
                    || n < ver2.segments.size(); ++n) {

        if (n < ver1.segments.size()
            && n < ver2.segments.size()) {
            // compare
            if (ver1.segments.at(n) > ver2.segments.at(n))
                return E_VCT_Greater;
            else if (ver1.segments.at(n) < ver2.segments.at(n))
                return E_VCT_Less;

            continue;
        }

        if (n >= ver1.segments.size()
            && n >= ver2.segments.size()) {
            // equal
            break;
        } else if (n >= ver1.segments.size()) {
            // ver1的数量比较少
            if (!cklistisAllZero(ver2.segments, n))
                return E_VCT_Less;

            // ver2的数量比较多，但是后面数值都为0，判断相等
            break;
        } else if (n >= ver2.segments.size()) {
            if (!cklistisAllZero(ver1.segments, n))
                return E_VCT_Greater;
            break;
        }
    }

    // 1.0.0-alpha < 1.0.0
    if (ver1.preStr.isEmpty() && !ver2.preStr.isEmpty())
        return E_VCT_Greater;
    if (ver2.preStr.isEmpty() && !ver1.preStr.isEmpty())
        return E_VCT_Less;

    // 比较先行版本类型（通过字符比较）
    // SEMVER_NUM_COMPER(preType)

    QString preTemp1 = ver1.preStr.toLower();
    QString preTemp2 = ver2.preStr.toLower();
    if (preTemp1 == preTemp2 || (preTemp1.isEmpty() && preTemp2.isEmpty()))
        return E_VCT_Equal;

    auto items1 = regItems(preTemp1);   // 解析成多项
    auto items2 = regItems(preTemp2);   // 解析成多项

    // 只有数字的标识符以数值高低比较。
    // 有字母或连接号时则逐字以 ASCII 的排序来比较。
    // 数字的标识符比非数字的标识符优先层级低。
    for (int n = 0; ; ++n) {
        if (n < items1.size() && n < items2.size()) {
            auto comp = comItem(items1.at(n), items2.at(n));
            if (comp != E_VCT_Equal)
                return comp;
            continue;
        }
        break;
    }

    // 若开头的标识符都相同时，栏位比较多的先行版本号优先层级比较高。
    if (items1.size() > items2.size())
        return E_VCT_Greater;
    else if (items1.size() < items2.size())
        return E_VCT_Less;

    return E_VCT_Equal;
}

EVerCompareType SemverVersion::compare(const QString &ver1, const QString &ver2)
{
    return compare(SemverVersion::fromString(ver1), SemverVersion::fromString(ver2));
}

/// <valid semver> ::= <version core>
///                    | <version core> "-" <pre-release>
///                    | <version core> "+" <build>
///                    | <version core> "-" <pre-release> "+" <build>
SemverVersion SemverVersion::fromString(const QString &str)
{
    Version ver;

    if (str.size() < g_verMinSize)
        return SemverVersion(ver);

    QString strTemp = str;
    QString preStr;
    QString preTypeStr;
    QString buildStr;
    EPreType preType = E_NonePre;
    quint16 first = 0;
    EVersionType verType = E_Semver;

    // 编译版本信息
    int idxBuild = strTemp.indexOf(g_buildPrefix);
    if (idxBuild >= 0) {
        if (idxBuild < g_verMinSize)
            return SemverVersion(ver, str);

        buildStr = strTemp.mid(idxBuild + g_buildPrefix.size());
        // 去掉构建版本
        strTemp = strTemp.left(idxBuild);
    }

    // 先行版本信息
    int idxPer = strTemp.indexOf(g_prePrefix);
    if (idxPer >= 0) {
        if (idxPer < g_verMinSize)
            return SemverVersion(ver, str);

        // 先行版本字符串
        preStr = strTemp.mid(idxPer + g_prePrefix.size());
        // 判断先行版本类型
        preType = checkPreType(preStr.toLower(), preTypeStr);
        // 去掉先行版本
        strTemp = strTemp.left(idxPer);
    } else {
        // 1.0.0.0506_beta
        idxPer = strTemp.indexOf(g_par2Prefix);
        if (idxPer >= 0) {
            if (idxPer < g_verMinSize)
                return SemverVersion(ver, str);

            verType = E_NotSemver;

            // 先行版本字符串
            preStr = strTemp.mid(idxPer + g_par2Prefix.size());
            // 判断先行版本类型
            preType = checkPreType(preStr.toLower(), preTypeStr);
            // 去掉先行版本
            strTemp = strTemp.left(idxPer);
        }
    }

    int idxFirst = strTemp.indexOf(g_par3Prefix); // 4:0.1.0
    if (idxFirst >= 0) {
        if (idxFirst == 0)
            return SemverVersion(ver, str);

        verType = E_NotSemver;
        first = strTemp.left(idxFirst).toShort();
        strTemp = strTemp.mid(idxFirst + g_par3Prefix.size());
    }

    QStringList nums = strTemp.split(g_parPrefix, QString::SkipEmptyParts);
    if (nums.size() <= 1)
        return SemverVersion(ver, str);

    auto toNum = [](const QString &str, quint16 &out)
    {
        bool bOk;
        out = str.toUShort(&bOk);
        return bOk;
    };

    QVector<QString> segments;
    for (int n = 0; n < nums.size(); ++n) {
        QString strItem = nums.at(n);
        quint16 val = 0;
        if (!toNum(strItem, val) && n < 3)
            return SemverVersion(ver);

        // segments.append(val);
        segments.append(strItem);
    }

    ver.verType = verType;
    ver.first = first;
    ver.major = segments[0].toInt();
    ver.minor = segments[1].toInt();
    ver.micro = segments.size() > 2 ? segments[2].toInt() : 0;
    ver.segments = segments;

    ver.preType = preType;   // 先行版本类型
    ver.preStr = preStr;
    ver.preTypeStr = preTypeStr;
    ver.bulidStr = buildStr;

    return SemverVersion(ver, str);
}

QString SemverVersion::compareTypeToString(EVerCompareType type)
{
    switch (type) {
    case E_VCT_Invalid: return "invalid";
    case E_VCT_LessEqual: return "<=";
    case E_VCT_GreaterEqual: return ">=";
    case E_VCT_Equal: return "=";
    case E_VCT_Less: return "<";
    case E_VCT_Greater: return ">";
    default:
        break;
    }
    return "unknown";
}

QString SemverVersion::outCompareToString(const QString &ver1, const QString &ver2)
{
    EVerCompareType type = compare(ver1, ver2);
    return ver1 + " " + compareTypeToString(type) + " " + ver2;
}

SemverVersion &SemverVersion::operator = (const SemverVersion &ver)
{
    if (&ver != this) {
        m_ver = ver.version();
        m_originalStr = ver.m_originalStr;
    }
    return *this;
}

bool SemverVersion::operator > (const SemverVersion &ver)
{
    auto comType = compare(*this, ver);
    return comType == E_VCT_Greater;
}
bool SemverVersion::operator >= (const SemverVersion &ver)
{
    auto comType = compare(*this, ver);
    return (comType == E_VCT_Greater || comType == E_VCT_Equal);
}
bool SemverVersion::operator < (const SemverVersion &ver)
{
    auto comType = compare(*this, ver);
    return comType == E_VCT_Less;
}
bool SemverVersion::operator <= (const SemverVersion &ver)
{
    auto comType = compare(*this, ver);
    return (comType == E_VCT_Less || comType == E_VCT_Equal);
}
bool SemverVersion::operator == (const SemverVersion &ver)
{
    auto comType = compare(*this, ver);
    return comType == E_VCT_Equal;
}

EPreType SemverVersion::checkPreType(const QString &str, QString &preTypeStr)
{
    auto checkIsType = [=](const QString &preStr,
                           const QString &typeStr,
                           QString &typeStrOut) -> bool
    {
        // rc == rc
        if (preStr == typeStr) {
            typeStrOut = typeStr;
            return true;
        }

        int index = preStr.indexOf(typeStr);
        if (index < 0)
            return false;

        int index2 = index + typeStr.size();
        bool bIndex2 = index2 < preStr.size();

        if (index == 0 && bIndex2 // right
            && checkIsPreTypeSegment(preStr, index2)) { // rc-1
            typeStrOut = preStr.left(preTypeStr.size() + g_prePrefix.size());
            return true;
        } else if (index > 0 && bIndex2 // cnter
                   && checkIsPreTypeSegment(preStr, index)
                   && checkIsPreTypeSegment(preStr, index2)) { // xxx-rc-xxx
            typeStrOut = preStr.mid(index - g_prePrefix.size(),
                                    preTypeStr.size() + g_prePrefix.size());
            return true;
        } else if (index > 0 && !bIndex2 // right
                   && checkIsPreTypeSegment(preStr, index)) { // xxx-rc
            typeStrOut = preStr.mid(index - g_prePrefix.size());
            return true;
        }
        return false;
    };

    EPreType preType = E_NonePre;
    if (checkIsType(str, g_strRc1, preTypeStr))
        return E_Rc;
    if (checkIsType(str, g_strBeta, preTypeStr))
        return E_Beta;
    if (checkIsType(str, g_strAlpha, preTypeStr))
        return E_Alpha;
    if (checkIsType(str, g_strRc2, preTypeStr))
        return E_Rc;
    return preType;
}
