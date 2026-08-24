#ifndef QHMATHUTIL_H
#define QHMATHUTIL_H

#include "QH_global.h"

class QTHANDY_EXPORT QhMathUtil
{
public:
    /// @brief 三角形相关
    class Triangle
    {
    public:
        /// @brief 根据斜边长度以及斜边夹角求对边长度
        static qreal calcOppositeBy_H_O_Angle(qreal hypotenuse, qreal obliqueAngle);

        /// @brief 根据斜边长度以及斜边夹角求临边长度
        static qreal calcAdjacentBy_H_O_Angle(qreal hypotenuse, qreal obliqueAngle);
    };
};

#endif // QHMATHUTIL_H
