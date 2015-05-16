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
class QTestStream;
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

  /// Add new line.
  ///
  /// The GraphicsPoint arguments are not const since this line binds to the points, so dragging points also drags the lines
  void addPoint (const QString &pointIdentifier,
                 double ordinal,
                 GraphicsPoint &point);

  /// Mark the end of addPoint calls. Remove stale lines, insert missing lines, and draw the graphics lines
  void lineMembershipPurge (const LineStyle &lineStyle);

  /// Mark points as unwanted. Afterwards, lineMembershipPurge gets called
  void lineMembershipReset ();

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  /// Remove the specified point. The act of deleting it will automatically remove it from the GraphicsScene
  void removePoint (const QString &identifier);

  /// Update the GraphicsScene with the specified Point from the Document. If it does not exist yet in the scene, we add it
  void updateAfterCommand (GraphicsScene &scene,
                           const PointStyle &pointStyle,
                           const Point &point);

  /// Calls to moveLinesWithDraggedPoint have finished so update the lines correspondingly
  void updateGraphicsLinesToMatchGraphicsPoints (const LineStyle &lineStyle);

  /// See GraphicsScene::updateOrdinalsAfterDrag. Pretty much the same steps as Curve::updatePointOrdinals
  void updatePointOrdinalsAfterDrag (const LineStyle &lineStyle,
                                     const Transformation &transformation);

private:

  QPainterPath drawLinesSmooth (const OrdinalToPointIdentifier &ordinalToPointIdentifier);
  QPainterPath drawLinesStraight (const OrdinalToPointIdentifier &ordinalToPointIdentifier);

  const QString m_curveName;
  PointIdentifierToGraphicsPoint m_graphicsPoints;
};

#endif // GRAPHICS_LINES_FOR_CURVE_H
