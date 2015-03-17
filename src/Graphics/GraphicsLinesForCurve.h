#ifndef GRAPHICS_LINES_FOR_CURVE_H
#define GRAPHICS_LINES_FOR_CURVE_H

#include "MapOrdinalToPoint.h"
#include "Point.h"
#include <QGraphicsPathItem>
#include <QMap>

class GraphicsPoint;
class GraphicsScene;
class LineStyle;

/// This class stores the GraphicsLine objects for one Curve. The container is a QMap since that container
/// maintains order by key
class GraphicsLinesForCurve : public QGraphicsPathItem
{
public:
  /// Single constructor
  GraphicsLinesForCurve(const QString &curveName);

  /// Move position of one point, so lines can be moved correspondingly
  void moveLinesWithDraggedPoint (const QString &pointIdentifier,
                                  int ordinal,
                                  const QPointF &scenePos);

  /// Calls to moveLinesWithDraggedPoint have finished so update the lines correspondingly
  void moveLinesWithDraggedPoints (const LineStyle &lineStyle);

  /// Add new line.
  ///
  /// The GraphicsPoint arguments are not const since this line binds to the points, so dragging points also drags the lines
  void savePoint (double ordinal,
                  GraphicsPoint &point);

  /// Mark the end of savePoint calls. Remove stale lines, insert missing lines, and draw the graphics lines
  void updateFinish (const LineStyle &lineStyle);

  /// Mark the start of savePoint calls. Afterwards, updateFinish gets called
  void updateStart ();

private:

  QPainterPath drawLinesSmooth ();
  QPainterPath drawLinesStraight ();

  const QString m_curveName;
  MapOrdinalToPoint m_graphicsPoints;
};

#endif // GRAPHICS_LINES_FOR_CURVE_H
