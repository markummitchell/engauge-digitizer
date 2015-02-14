#ifndef GRAPHICS_LINES_FOR_CURVES_H
#define GRAPHICS_LINES_FOR_CURVES_H

#include "LineStyle.h"
#include "LineStyles.h"
#include <QHash>

class GraphicsLinesForCurve;
class GraphicsPoint;
class GraphicsScene;
class QGraphicsItem;

typedef QHash<QString, GraphicsLinesForCurve*> GraphicsLinesContainer;

/// This class stores the GraphicsLinesForCurves objects, one per Curve
class GraphicsLinesForCurves
{
public:
  /// Single constructor
  GraphicsLinesForCurves();

  /// Clear out existing point just prior to storing new set of points
  void resetPoints ();

  /// Add new item. If the item is already in the map then it is just updated. The line is associated with the lower ordinal value, and
  /// the upper ordinal value is not involved. The ordinalOther value is only for debugging
  ///
  /// The GraphicsPoint arguments are not const since this line binds to the points, so dragging points also drags the lines
  void saveLine (GraphicsScene &scene,
                 const QString &curveName,
                 double ordinalAssociated,
                 double ordinalOther,
                 GraphicsPoint &pointStart,
                 GraphicsPoint &pointEnd,
                 const LineStyle &lineStyle);

  /// Remove stale lines and insert missing lines
  void updateLines (GraphicsScene &scene);

private:

  GraphicsLinesContainer m_graphicsLinesForCurve;
};

#endif // GRAPHICS_LINES_FOR_CURVES_H
