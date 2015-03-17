#ifndef MAP_ORDINAL_TO_POINT_H
#define MAP_ORDINAL_TO_POINT_H

#include "Point.h"
#include <QMap>

/// Store points ordered by the ordinal. Container type is QMap since that maintains order by key
typedef QMap<double, Point> MapOrdinalToPoint;

#endif // MAP_ORDINAL_TO_POINT_H
