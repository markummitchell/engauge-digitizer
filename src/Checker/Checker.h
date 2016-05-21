/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CHECKER_H
#define CHECKER_H

#include "CheckerMode.h"
#include "DocumentAxesPointsRequired.h"
#include "GridLine.h"
#include "GridLines.h"
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

/// Box shape that is drawn through the three axis points, to temporarily (usually) or permanently (rarely)
/// highlight the local up/down/left/right directions when all axis points have been defined. The goal of the checker
/// is to make it obvious when a mistake has happened so the screen-to-graph transformation is
/// currently wrong - since the expected up/down/left/right directions will be awry which will distort the checker
/// somehow. Unfortunately, errors in scale are not revealed by the checker.
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
                          const DocumentModelCoords &modelCoords,
                          DocumentAxesPointsRequired documentAxesPointsRequired);

  /// Create the polygon from current information, including pixel and graph coordinates, just prior to display. This is for
  /// TransformationStateDefined. The point radius is used to exclude the lines from the axes points for clarity
  void prepareForDisplay (const QList<Point> &Points,
                          int pointRadius,
                          const DocumentModelAxesChecker &modelAxesChecker,
                          const DocumentModelCoords &modelCoords,
                          const Transformation &transformation,
                          DocumentAxesPointsRequired documentAxesPointsRequired);

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

  // Low level routine to set line color
  void setLineColor (GridLine &gridLine,
                     const QPen &pen);

  QGraphicsScene &m_scene;

  // These grid lines are QGraphicsLineItem line segments or QGraphicsEllipseItem arc segments. Together they
  // make up a box (cartesian) or annular (polar) shape in cartesian coordinates.
  //
  // A major complication is that drawing the box with just four lines from corner to corner results in extremely
  // thick lines through the axes points, which obscures the axis point unacceptably. So, each side is drawn with
  // up to 3 visible lines:
  // 1) corner1 to either point1 or corner2 (whichever comes first)
  // 2) unused, or point1 to either point2 or corner2 (whichever comes first)
  // 3) unused point2 to corner2
  GridLines m_gridLines;
};

#endif // CHECKER_H
