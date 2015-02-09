#ifndef GRAPHICS_LINES_FOR_CURVE_H
#define GRAPHICS_LINES_FOR_CURVE_H

#include <QMap>

class GraphicsLine;
class GraphicsScene;
class QGraphicsItem;

typedef QMap<int, QGraphicsItem*> GraphicsLineContainer;

/// This class stores the GraphicsLine objects for one Curve. The container is a QMap since that container
/// maintains order by key
class GraphicsLinesForCurve
{
public:
  /// Single constructor
  GraphicsLinesForCurve();

  /// Add new item. An assert happens if the item is already in the map
  void saveItem (int ordinal,
                 QGraphicsItem *line);

  /// Remove stale lines and insert missing lines
  void updateLines (GraphicsScene &scene);

private:

  GraphicsLineContainer m_graphicsLines;
};

#endif // GRAPHICS_LINES_FOR_CURVE_H
