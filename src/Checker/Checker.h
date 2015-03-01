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

const int MAX_LINES_PER_SIDE = 3;
const int NUM_AXES_POINTS = 3;

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

  void bindItemToScene(QGraphicsItem *item);
  void createSide (int pointRadius,
                   const QList<Point> &points,
                   const DocumentModelCoords &modelCoords,
                   const QPointF &pointFromGraph,
                   const QPointF &pointToGraph,
                   const Transformation &transformation,
                   QGraphicsItem *items [MAX_LINES_PER_SIDE]);
  void createTransformAlign (const Transformation &transformation,
                             double radius,
                             const QPointF &posOriginScreen,
                             QTransform &transformAlign,
                             double &ellipseXAxis,
                             double &ellipseYAxis) const;
  void deleteSide (QGraphicsItem *items [MAX_LINES_PER_SIDE]);
  QGraphicsItem *ellipseItem(const Transformation &transformation,
                             double radius,
                             const QPointF &posStartScreen,
                             const QPointF &posEndScreen) const;

  // Intercept circle around point with line. Intersection point count is either 0 or 2. For simplicity,
  // if point just touches line then the point count is handled as two points at the same position
  void interceptPointCircleWithLine (int pointIntercept,
                                     QList<double> &sInterceptPoints,
                                     const Point &point,
                                     const QPointF &pointFromScreen,
                                     const QPointF &pointToScreen);

  // Distance to nearest point in points list
  double minScreenDistanceFromPoints (const QPointF &posScreen,
                                      const QList<Point> &points);

  // Low level routine to set line color
  void setLineColor (QGraphicsItem *item [MAX_LINES_PER_SIDE], const QPen &pen);

  void setVisibleSide (QGraphicsItem *item [MAX_LINES_PER_SIDE],
                       bool visible);

  QGraphicsScene &m_scene;

  // These segments are QGraphicsLineItem line segments or QGraphicsEllipseItem arc segments. Together they
  // make up a box shape in cartesian coordinates.
  //
  // A major complication is that drawing the box with just four lines from corner to corner results in extremely
  // thick lines through the axes points, which obscures the axis point unacceptably. So, each side is drawn with
  // 3 visible lines:
  // 1) corner1 to either point1 or corner2 (whichever comes first)
  // 2) unused, or point1 to either point2 or corner2 (whichever comes first)
  // 3) unused point2 to corner2
  QGraphicsItem *m_sideLeft [MAX_LINES_PER_SIDE];
  QGraphicsItem *m_sideTop [MAX_LINES_PER_SIDE];
  QGraphicsItem *m_sideRight [MAX_LINES_PER_SIDE];
  QGraphicsItem *m_sideBottom [MAX_LINES_PER_SIDE];
};

#endif // CHECKER_H
