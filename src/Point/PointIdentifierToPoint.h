#ifndef POINT_IDENTIFIER_TO_POINT_H
#define POINT_IDENTIFIER_TO_POINT_H

#include "Point.h"
#include <QMap>

/// Store points ordered by the ordinal. This is a QMap for direct access
typedef QMap<QString, Point> PointIdentifierToPoint;

#endif // POINT_IDENTIFIER_TO_POINT_H
