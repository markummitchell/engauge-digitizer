#ifndef GRAPHICS_LINES_FOR_CURVE_H
#define GRAPHICS_LINES_FOR_CURVE_H

#include "PointIdentifierToGraphicsPoint.h"
#include "Point.h"
#include <QGraphicsPathItem>
#include <QMap>

class GraphicsPoint;
class GraphicsScene;
class LineStyle;
class PointStyle;
class Transformation;

/// Order-preserving map from ordinal to pointIdentifier of Point
typedef QMap<double, QString> OrdinalToPointIdentifier;

/// This class stores the GraphicsLine objects for one Curve. The container is a QMap since that container
/// maintains order by key
class GraphicsLinesForCurve : public QGraphicsPathItem
{
public:
  /// Single constructor
  GraphicsLinesForCurve(const QString &curveName);

  /// Remove the specified point. The act of deleting it will automatically remove it from the GraphicsScene
  void removePoint (const QString &identifier);

  /// Add new line.
  ///
  /// The GraphicsPoint arguments are not const since this line binds to the points, so dragging points also drags the lines
  void savePoint (const QString &pointIdentifier,
                  double ordinal,
                  GraphicsPoint &point);

  /// Update the GraphicsScene with the specified Point from the Document. If it does not exist yet in the scene, we add it
  void updateAfterCommand (GraphicsScene &scene,
                           const PointStyle &pointStyle,
                           const Point &point);

  /// Mark the end of savePoint calls. Remove stale lines, insert missing lines, and draw the graphics lines
  void updateFinish (const LineStyle &lineStyle);

  /// Calls to moveLinesWithDraggedPoint have finished so update the lines correspondingly
  void updateGraphicsLinesToMatchGraphicsPoints (const LineStyle &lineStyle);

  /// See GraphicsScene::updateOrdinalsAfterDrag. Pretty much the same steps as Curve::updatePointOrdinals
  void updatePointOrdinalsAfterDrag (const LineStyle &lineStyle,
                                     const Transformation &transformation);

  /// Mark the start of savePoint calls. Afterwards, updateFinish gets called
  void updateStart ();

private:

  QPainterPath drawLinesSmooth (const OrdinalToPointIdentifier &ordinalToPointIdentifier);
  QPainterPath drawLinesStraight (const OrdinalToPointIdentifier &ordinalToPointIdentifier);

  const QString m_curveName;
  PointIdentifierToGraphicsPoint m_graphicsPoints;
};

#endif // GRAPHICS_LINES_FOR_CURVE_H
