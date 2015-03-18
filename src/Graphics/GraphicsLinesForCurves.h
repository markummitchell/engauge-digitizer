#ifndef GRAPHICS_LINES_FOR_CURVES_H
#define GRAPHICS_LINES_FOR_CURVES_H

#include <QHash>

class CurveStyles;
class GraphicsLinesForCurve;
class GraphicsPoint;
class GraphicsScene;
class QGraphicsItem;
class QPointF;

typedef QHash<QString, GraphicsLinesForCurve*> GraphicsLinesContainer;

/// This class stores the GraphicsLinesForCurves objects, one per Curve
class GraphicsLinesForCurves
{
public:
  /// Single constructor
  GraphicsLinesForCurves();

  /// Move position of one point, so lines can be moved correspondingly
  void moveLinesWithDraggedPoint (const QString &pointIdentifier,
                                  int ordinal,
                                  const QPointF &scenePos);

  /// Calls to moveLinesWithDraggedPoint have finished so update the lines correspondingly
  void moveLinesWithDraggedPoints (const CurveStyles &curveStyles);

  /// Add new point
  void savePoint (GraphicsScene &scene,
                  const QString &curveName,
                  const QString &pointIdentifier,
                  double ordinal,
                  GraphicsPoint &point);

  /// Mark the end of savePoint calls. Remove stale lines, insert missing lines, and draw the graphics lines
  void updateFinish (const CurveStyles &curveStyles);

  /// Mark the start of savePoint calls. Afterwards, updateFinish gets called
  void updateStart ();

private:

  GraphicsLinesContainer m_graphicsLinesForCurve;
};

#endif // GRAPHICS_LINES_FOR_CURVES_H
