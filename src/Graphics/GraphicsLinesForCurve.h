#ifndef GRAPHICS_LINES_FOR_CURVE_H
#define GRAPHICS_LINES_FOR_CURVE_H

#include <QMap>

class GraphicsLine;
class GraphicsPoint;
class GraphicsScene;
class LineStyle;
class QGraphicsItem;

typedef QMap<double, GraphicsLine*> GraphicsLineContainer;

/// This class stores the GraphicsLine objects for one Curve. The container is a QMap since that container
/// maintains order by key
class GraphicsLinesForCurve
{
public:
  /// Single constructor
  GraphicsLinesForCurve();

  /// Clear out existing point just prior to storing new set of points
  void resetPoints ();

  /// Add new line. If the item is already in the map then it is just updated. The line is associated with the lower ordinal value, and
  /// the upper ordinal value is not involved. The ordinalOther value is only for debugging
  void saveLine (GraphicsScene &scene,
                 double ordinalAssociated,
                 double ordinalOther,
                 const GraphicsPoint &pointLow,
                 const GraphicsPoint &pointHigh,
                 const LineStyle &lineStyle);

  /// Remove stale lines and insert missing lines
  void updateLines (GraphicsScene &scene);

private:

  GraphicsLineContainer m_graphicsLines;
};

#endif // GRAPHICS_LINES_FOR_CURVE_H
