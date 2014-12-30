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
  void createLine (QGraphicsItem *&item,
                   const QPointF &pointFromGraph,
                   const QPointF &pointToGraph,
                   const Transformation &transformation);
  void deleteLine (QGraphicsItem *&item);

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
