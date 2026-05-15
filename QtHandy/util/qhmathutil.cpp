#include "qhmathutil.h"
#include <QtMath>

qreal QhMathUtil::Triangle::calcOppositeBy_H_O_Angle(qreal hypotenuse, qreal obliqueAngle)
{
    double rad = qDegreesToRadians(obliqueAngle);
    return hypotenuse * qSin(rad);
}

qreal QhMathUtil::Triangle::calcAdjacentBy_H_O_Angle(qreal hypotenuse, qreal obliqueAngle)
{
    double rad = qDegreesToRadians(obliqueAngle);
    return hypotenuse * qCos(rad);
}
