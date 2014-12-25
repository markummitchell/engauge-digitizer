#ifndef CHECKER_H
#define CHECKER_H

#include "CheckerMode.h"
#include <QColor>
#include <QGraphicsPolygonItem>
#include <QList>
#include <QPolygonF>

class DocumentModelAxesChecker;
class Point;
class QGraphicsScene;
class QPolygonF;
class Transformation;

/// L-shaped polygon that is drawn through the three axis points, to temporarily (usually) or permanently (rarely)
/// highlight the local up/down/left/right directions when all axis points have been defined. These checker are 
/// meant to make it apparent when a mistake has happened so the screen-to-graph transformation is 
/// currently wrong - since the expected up/down/left/right directions will be awry
class Checker : public QGraphicsPolygonItem
{
public:
  /// Single constructor for DlgSettingsAxesChecker, which does not have an explicit transformation. The identity transformation is assumed
  Checker(QGraphicsScene &scene);

  /// Create the polygon from current information, including pixel coordinates, just prior to display. This is for DlgSettingsAxesChecker.
  /// The identity matrix is used for the transformations between screen and graph coordinates
  void prepareForDisplay (const QPolygonF &polygon,
                          const DocumentModelAxesChecker &modelAxesChecker);

  /// Create the polygon from current information, including pixel and graph coordinates, just prior to display. This is for TransformationStateDefined
  void prepareForDisplay (const QList<Point> &Points,
                          const DocumentModelAxesChecker &modelAxesChecker,
                          const Transformation &transformation);

  /// Apply the new DocumentModelAxesChecker, to the points already associated with this object. This method starts the
  /// timer unless the mode is never or forever
  virtual void updateModelAxesChecker (const DocumentModelAxesChecker &modelAxesChecker);

private:
  Checker();

  void setLineColor(const DocumentModelAxesChecker &modelAxesChecker);

  // Compute fourth point so each axis has two points along it, which gives three line segments (all from the intersection point).
  // We need three lines since resulting polygon must be closed (first and last points are the same or else there will be an
  // unwanted final line)
  QPolygonF threeLinesFromThreePoints (const Point &pointAxis0a,
                                       const Point &pointAxis0b,
                                       const Point &pointAxis1,
                                       const Transformation &transformation);
};

#endif // CHECKER_H
