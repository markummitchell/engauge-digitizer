#ifndef CHECKER_H
#define CHECKER_H

#include "CheckerMode.h"
#include <QColor>
#include <QList>
#include <QPolygonF>

class DocumentModelAxesChecker;
class DocumentModelCoords;
class Point;
class QGraphicsItem;
class QGraphicsScene;
class QPolygonF;
class Transformation;

const int NUM_AXES_POINTS = 3;
enum Side {
  SIDE_BOTTOM,
  SIDE_LEFT,
  SIDE_TOP,
  SIDE_RIGHT,
  NUM_SIDES
};

// States that describe how an axes point and side are related. Each axes point gets
// assigned to one side even if it lies along two sides. Assigned points are still relevant
// since the greedy algorithm will prefer to use a side that goes through one unassigned and
// one assigned point over a side that simply goes through an assigned point. This strategy
// prevents, for example, one side at xMin and one side at xMax for points at bottom-left,
// top-left, and bottom-right
enum Connectivity {
  CONNECTIVITY_NOT_ALONG_SIDE,
  CONNECTIVITY_ALONG_SIDE_UNASSIGNED,
  CONNECTIVITY_ALONG_SIDE_ASSIGNED
};

/// U-shape that is drawn through the three axis points, to temporarily (usually) or permanently (rarely)
/// highlight the local up/down/left/right directions when all axis points have been defined. The goal of the checker
/// is to make it obvious when a mistake has happened so the screen-to-graph transformation is
/// currently wrong - since the expected up/down/left/right directions will be awry which will distort the checker
/// somehow. Unfortunately, errors in scale are not revealed by the checker.
///
/// If two of the three axes points are on the same axes, the U-shape simplifies to an L-shape.
///
/// For polar coordinates, the box will appear as an annular segment.
///
/// Alternatives to U-shape:
/// -# L-shape which assumes 2 of the 3 axes points are on the same axes. This fails if points are on 3 different axes
/// -# Rectangle which fits the 3 axes points. This may produce 1 or 2 axes that are not in the original image,
///    causing confusion
class Checker
{
public:
  /// Single constructor for DlgSettingsAxesChecker, which does not have an explicit transformation. The identity transformation is assumed
  Checker(QGraphicsScene &scene);

  /// Create the polygon from current information, including pixel coordinates, just prior to display. This is for DlgSettingsAxesChecker.
  /// The identity matrix is used for the transformations between screen and graph coordinates
  void prepareForDisplay (const QPolygonF &polygon,
                          const DocumentModelAxesChecker &modelAxesChecker,
                          const DocumentModelCoords &modelCoords);

  /// Create the polygon from current information, including pixel and graph coordinates, just prior to display. This is for TransformationStateDefined
  void prepareForDisplay (const QList<Point> &Points,
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
  QString connectivityString (Connectivity connectivity);
  void createLine (QGraphicsItem *&item,
                   const QPointF &pointFromGraph,
                   const QPointF &pointToGraph,
                   const Transformation &transformation);
  void deleteLine (QGraphicsItem *&item);
  void loadAxesPointToSideConnectivity (const QList<Point> points,
                                        double xMin,
                                        double xMax,
                                        double yMin,
                                        double yMax,
                                        Connectivity axesPointToSideConnectivity [NUM_AXES_POINTS] [NUM_SIDES]);
  void markSideAsAssigned (Side side,
                           Connectivity axesPointToSideConnectivity [NUM_AXES_POINTS] [NUM_SIDES]);
  int nextSide (const Connectivity axesPointToSideConnectivity [NUM_AXES_POINTS] [NUM_SIDES],
                bool isBottom,
                bool isLeft,
                bool isTop,
                bool isRight);

  // Low level routine to set line color
  void setLineColor (QGraphicsItem *item, const QPen &pen);

  QGraphicsScene &m_scene;

  // These segments are QGraphicsLineItem line segments or QGraphicsEllipseItem arc segments. Together they
  // make up a u shape in cartesian coordinates, or a u shapes topological equivalent in polar coordinates
  QGraphicsItem *m_side0;
  QGraphicsItem *m_side1;
  QGraphicsItem *m_side2;
  QGraphicsItem *m_side3;
};

#endif // CHECKER_H
