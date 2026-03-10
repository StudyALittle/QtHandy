#ifndef SEMVERTOOL_H
#define SEMVERTOOL_H

/*! *******************************************************
 * @File       : semvertool.h
 * @Author     : wmz
 * @Date       : 2024-05-23  13:25
 * @Version    : 0.1.0
 * @Copyright  : Copyright By Wmz, All Rights Reserved
 * @Brief      : Semantic version format tool(语义化版本格式工具)
 * @Description: [detailed description]
 ************** Semantic version format reference website：https://semver.org/lang/zh-CN
 ************** >>> Format:
 ************** 1）主版本号：当你做了不兼容的 API 修改；
 ************** 2）次版本号：当你做了向下兼容的功能性新增；
 ************** 3）修订号：当你做了向下兼容的问题修正；
 ************** 4）先行版本号（以'-'开始），一般组成规则如下：
 **************    （1）先行版本类型（优先级从低到高）：
 **************     -- alpha：内测版
 **************     -- beta：公测版
 **************     -- rc（release）：发布版本
 **************     -- （无先行版本类型）
 **************     （2）构建号：递增的数值
 ************** 5）版本编译信息(不做版本大小比较，以'+'开始)
 **************
 ************** >>> 语义化版本示例：
 **************     -- 1.0.0-alpha.1+exp.sha.5114f85
 **************     -- 1.0.0-1kylin1k6.beta
 **************
 ************** >>> 可能存在的特殊版本格式（非语义化版本格式）：
 **************     示例：
 **************     -- 1.0.0.0506_beta
 **************     -- 4:1.0.2.0506
 **********************************************************/

#include <QString>
#include <QVector>
#include <QRegularExpression>
#include "QH_global.h"

#define SEMVER_NUM_COMPER(key) \
    if (ver1.key > ver2.key)  \
        return E_VCT_Greater;  \
    else if (ver1.key < ver2.key)  \
        return E_VCT_Less;

namespace semvertool {

static const QString g_prePrefix      = "-";  // 先行版本前缀
static const QString g_buildPrefix    = "+";  // 编译版本前缀
static const QString g_parPrefix      = ".";  // 分隔符号
static const QString g_par2Prefix     = "_";  // 分割符号（不属于语义化版本格式）
static const QString g_par3Prefix     = ":";  // 分割符号（不属于语义化版本格式）
static const short g_verMinSize = 3;          // 0.0，版本最小字符串长度

static const QString g_strAlpha = "alpha";
static const QString g_strBeta  = "beta";
static const QString g_strRc1   = "rc";
static const QString g_strRc2   = "release";

static const QString g_strRegularPar   = "[\\-\\._]";

/// 版本类型（语义化版本格式，非语义化版本格式，无效版本）
enum EVersionType { E_Semver = 0, E_NotSemver = 1, E_InvalidVer };

/// 先行版本类型
enum EPreType { E_Alpha = 0, E_Beta = 1, E_Rc = 2, E_NonePre = 3 };

/// 版本比较类型
enum EVerCompareType
{
    E_VCT_Invalid = 0,  // invalid(One version is invalid during version comparison)
    E_VCT_LessEqual,    // <=
    E_VCT_GreaterEqual, // >=
    E_VCT_Equal,        // =
    E_VCT_Less,         // <
    E_VCT_Greater       // >
};

/// 版本信息
class Version
{
public:
    EVersionType verType = E_InvalidVer;
    quint16 first = 0; // 例如：4:1.0.2.0506 （第一个数值）
    quint16 major = 0;
    quint16 minor = 1;
    quint16 micro = 0;
    QVector<QString> segments; // major、minor、micro、other

    bool isValid() const { return verType != E_InvalidVer; }

protected:
    EPreType preType = E_NonePre;   // 先行版本类型
    QString preStr;                 // 先行版本完整字符串(需要比较大小)
    QString preTypeStr;
    QString bulidStr;
    bool bSigPreType = true;        // 1.0.0-alpha.beta

    friend class SemverVersion;
};

class QTHANDY_EXPORT SemverVersion
{
public:
    SemverVersion();
    SemverVersion(const QString &str);
    SemverVersion(const Version &ver);
    SemverVersion(const Version &ver, const QString &originalStr);

    /// @brief Version Information
    Version version() const;

    /// @brief Version comparison
    static EVerCompareType compare(const SemverVersion &sver1, const SemverVersion &sver2);
    static EVerCompareType compare(const Version &ver1, const Version &ver2);
    static EVerCompareType compare(const QString &ver1, const QString &ver2);

    /// <valid semver> ::= <version core>
    ///                    | <version core> "-" <pre-release>
    ///                    | <version core> "+" <build>
    ///                    | <version core> "-" <pre-release> "+" <build>
    static SemverVersion fromString(const QString &str);

    static QString compareTypeToString(EVerCompareType type);
    static QString outCompareToString(const QString &ver1, const QString &ver2);

    SemverVersion &operator = (const SemverVersion &ver);
    bool operator > (const SemverVersion &ver);
    bool operator >= (const SemverVersion &ver);
    bool operator < (const SemverVersion &ver);
    bool operator <= (const SemverVersion &ver);
    bool operator == (const SemverVersion &ver);

protected:
    static inline bool checkIsPreTypeSegment(const QString &str, int pos)
    {
        auto c = str.at(pos);
        return (c == g_prePrefix || c == g_parPrefix || c == g_par2Prefix);
    }

    static EPreType checkPreType(const QString &str, QString &preTypeStr);

protected:
    Version m_ver;
    QString m_originalStr;
};

} // end namespace

#endif // SEMVERTOOL_H
