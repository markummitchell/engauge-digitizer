#ifndef GRID_LINE_H
#define GRID_LINE_H

#include <QList>

class QGraphicsItem;

/// Single grid line drawn a straight or curved line. This is expected to be composed of QGraphicsEllipseItem and 
/// QGraphicsPathItem objects
typedef QList<QGraphicsItem *> GridLine;

#endif // GRID_LINE_H
