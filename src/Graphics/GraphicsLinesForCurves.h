#ifndef GRAPHICS_LINES_FOR_CURVES_H
#define GRAPHICS_LINES_FOR_CURVES_H

#include "LineStyle.h"
#include "LineStyles.h"
#include <QHash>

class GraphicsLinesForCurve;
class GraphicsPointAbstractBase;
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

  /// Add new item. If the item is already in the map then it is just updated. The item/point pointers both point to the same object
  void savePoint (const QString &curveName,
                  int ordinal,
                  QGraphicsItem *item,
                  GraphicsPointAbstractBase *point);

  /// Remove stale lines and insert missing lines
  void updateLines (GraphicsScene &scene,
                    const LineStyles &lineStyles);

private:

  GraphicsLinesContainer m_graphicsLinesForCurve;
};

#endif // GRAPHICS_LINES_FOR_CURVES_H
