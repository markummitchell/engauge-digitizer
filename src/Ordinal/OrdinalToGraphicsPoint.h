#ifndef ORDINAL_TO_GRAPHICS_POINT_H
#define ORDINAL_TO_GRAPHICS_POINT_H

#include <QMap>

class GraphicsPoint;

// Use QMap, which keeps the keys sorted, to map ordinal to GraphicsPoint
typedef QMap<double, GraphicsPoint*> OrdinalToGraphicsPoint;

#endif // ORDINAL_TO_GRAPHICS_POINT_H
