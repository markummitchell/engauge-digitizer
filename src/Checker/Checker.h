#ifndef CHECKER_H
#define CHECKER_H

#include "CheckerMode.h"
#include <QColor>
#include <QList>
#include <QPainterPath>
#include <QPolygonF>

class DocumentModelAxesChecker;
class DocumentModelCoords;
class Point;
class QGraphicsEllipseItem;
class QGraphicsItem;
class QGraphicsScene;
class QPolygonF;
class Transformation;

typedef QList<QGraphicsItem *> SideSegments;

/// Box shape that is drawn through the three axis points, to temporarily (usually) or permanently (rarely)
/// highlight the local up/down/left/right directions when all axis points have been defined. The goal of the checker
/// is to make it obvious when a mistake has happened so the screen-to-graph transformation is
/// currently wrong - since the expected up/down/left/right directions will be awry which will distort the checker
/// somehow. Unfortunately, errors in scale are not revealed by the checker.
///
/// For polar coordinates, the box will appear as an annular segment.
class Checker
{
public:
  /// Single constructor for DlgSettingsAxesChecker, which does not have an explicit transformation. The identity transformation is assumed
  Checker(QGraphicsScene &scene);

  /// Create the polygon from current information, including pixel coordinates, just prior to display. This is for DlgSettingsAxesChecker.
  /// The identity matrix is used for the transformations between screen and graph coordinates. The point radius is used to exclude
  /// the lines from  the axes points for clarity
  void prepareForDisplay (const QPolygonF &polygon,
                          int pointRadius,
                          const DocumentModelAxesChecker &modelAxesChecker,
                          const DocumentModelCoords &modelCoords);

  /// Create the polygon from current information, including pixel and graph coordinates, just prior to display. This is for
  /// TransformationStateDefined. The point radius is used to exclude the lines from the axes points for clarity
  void prepareForDisplay (const QList<Point> &Points,
                          int pointRadius,
                          const DocumentModelAxesChecker &modelAxesChecker,
                          const DocumentModelCoords &modelCoords,
                          const Transformation &transformation);

  /// Show/hide this axes checker.
  void setVisible (bool visible);

  /// Apply the new DocumentModelAxesChecker, to the points already associated with this object. This method starts the
  /// timer unless the mode is never or forever
  virtual void updateModelAxesChecker (const DocumentModelAxesChecker &modelAxesChecker);

private:
  Checker();

  // For polar coordinates, pick the smallest angle range. Note that xMax may be less than xMin, in which case
  // xMax+period should be used. Ymin is also set to zero for polar coordinates
  void adjustPolarAngleRanges (const DocumentModelCoords &modelCoords,
                               const Transformation &transformation,
                               const QList<Point> &points,
                               double &xMin,
                               double &xMax,
                               double &yMin) const;
  void bindItemToScene(QGraphicsItem *item) const;

  // Create side, either along constant X/theta or constant Y/radius side. Line goes from pointFromGraph to pointToGraph.
  // If the coordinates are polar, we go clockwise from pointFromGraph to pointToGraph (as set up by adjustPolarAngleRange).
  void createSide (int pointRadius,
                   const QList<Point> &points,
                   const DocumentModelCoords &modelCoords,
                   double xFrom,
                   double yFrom,
                   double xTo,
                   double yTo,
                   const Transformation &transformation,
                   SideSegments &sideSegments);
  void createTransformAlign (const Transformation &transformation,
                             double radiusLinearCartesian,
                             const QPointF &posOriginScreen,
                             QTransform &transformAlign,
                             double &ellipseXAxis,
                             double &ellipseYAxis) const;
  void deleteSide (SideSegments &sideSegments);
  QGraphicsItem *ellipseItem(const Transformation &transformation,
                             double radiusLinearCartesian,
                             const QPointF &posStartScreen,
                             const QPointF &posEndScreen) const;
  void finishActiveSegment (const DocumentModelCoords &modelCoords,
                            const QPointF &posStartScreen,
                            const QPointF &posEndScreen,
                            double yFrom,
                            double yTo,
                            const Transformation &transformation,
                            SideSegments &sideSegments) const;
  QGraphicsItem *lineItem (const QPointF &posStartScreen,
                           const QPointF &posEndScreen) const;
  double minScreenDistanceFromPoints (const QPointF &posScreen,
                                      const QList<Point> &points);

  // Low level routine to set line color
  void setLineColor (SideSegments &sideSegments,
                     const QPen &pen);

  void setVisibleSide (SideSegments &sideSegments,
                       bool visible);

  QGraphicsScene &m_scene;

  // These segments are QGraphicsLineItem line segments or QGraphicsEllipseItem arc segments. Together they
  // make up a box shape in cartesian coordinates.
  //
  // A major complication is that drawing the box with just four lines from corner to corner results in extremely
  // thick lines through the axes points, which obscures the axis point unacceptably. So, each side is drawn with
  // up to 3 visible lines:
  // 1) corner1 to either point1 or corner2 (whichever comes first)
  // 2) unused, or point1 to either point2 or corner2 (whichever comes first)
  // 3) unused point2 to corner2
  SideSegments m_sideLeft;
  SideSegments m_sideTop;
  SideSegments m_sideRight;
  SideSegments m_sideBottom;
};

#endif // CHECKER_H
