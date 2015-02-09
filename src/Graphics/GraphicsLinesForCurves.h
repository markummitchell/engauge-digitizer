#ifndef GRAPHICS_LINES_FOR_CURVES_H
#define GRAPHICS_LINES_FOR_CURVES_H

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

  /// Add new item. An assert happens if the item is already in the map
  void saveItem (const QString &curveName,
                 int ordinal,
                 QGraphicsItem*line);

  /// Remove stale lines and insert missing lines
  void updateLines (GraphicsScene &scene);

private:

  GraphicsLinesContainer m_graphicsLinesForCurve;
};

#endif // GRAPHICS_LINES_FOR_CURVES_H
