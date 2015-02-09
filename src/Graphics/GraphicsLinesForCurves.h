#ifndef GRAPHICS_LINES_FOR_CURVES_H
#define GRAPHICS_LINES_FOR_CURVES_H

#include "LineStyle.h"
#include "LineStyles.h"
#include <QHash>

class GraphicsLinesForCurve;
class GraphicsScene;
class QGraphicsItem;

typedef QHash<QString, GraphicsLinesForCurve*> GraphicsLinesContainer;

/// This class stores the GraphicsLinesForCurves objects, one per Curve
class GraphicsLinesForCurves
{
public:
  /// Single constructor
  GraphicsLinesForCurves();

  /// Add new item. If the item is already in the map then it is just updated
  void saveItem (const QString &curveName,
                 const LineStyle &lineStyle,
                 int ordinal,
                 QGraphicsItem*line);

  /// Remove stale lines and insert missing lines
  void updateLines (GraphicsScene &scene,
                    const LineStyles &lineStyles);

private:

  GraphicsLinesContainer m_graphicsLinesForCurve;
};

#endif // GRAPHICS_LINES_FOR_CURVES_H
