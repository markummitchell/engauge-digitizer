/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Checker.h"
#include "DocumentModelCoords.h"
#include "EngaugeAssert.h"
#include "EnumsToQt.h"
#include "GridLineFactory.h"
#include "Logger.h"
#include "mmsubs.h"
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <qmath.h>
#include <QPen>
#include <QTextStream>
#include "QtToString.h"
#include "Transformation.h"

const int NUM_AXES_POINTS_3 = 3;
const int NUM_AXES_POINTS_4 = 4;

extern const QString DUMMY_CURVE_NAME;

// One-pixel wide line (produced by setting width=0) is too small. 5 is big enough to be always noticeable,
// but such a thick line obscures the axes points. To keep the axes points visible, we remove portions of 
// the line nearer to an axes point than the point radius.
const int CHECKER_POINTS_WIDTH = 5;

Checker::Checker(QGraphicsScene &scene) :
  m_scene (scene)
{
}

void Checker::adjustPolarAngleRanges (const DocumentModelCoords &modelCoords,
                                      const Transformation &transformation,
                                      const QList<Point> &points,
                                      double &xMin,
                                      double &xMax,
                                      double &yMin) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Checker::adjustPolarAngleRanges transformation=" << transformation;

  const double UNIT_LENGTH = 1.0;

  QString path; // For logging
  if (modelCoords.coordsType() == COORDS_TYPE_POLAR) {

    // Range minimum is at origin
    yMin = modelCoords.originRadius();

    path = QString ("yMin=%1 ").arg (yMin); // For logging

    // Perform special processing to account for periodicity of polar coordinates. Start with unit vectors
    // in the directions of the three axis points
    double angle0 = points.at(0).posGraph().x();
    double angle1 = points.at(1).posGraph().x();
    double angle2 = points.at(2).posGraph().x();
    QPointF pos0 = transformation.cartesianFromCartesianOrPolar(modelCoords,
                                                                QPointF (angle0, UNIT_LENGTH));
    QPointF pos1 = transformation.cartesianFromCartesianOrPolar(modelCoords,
                                                                QPointF (angle1, UNIT_LENGTH));
    QPointF pos2 = transformation.cartesianFromCartesianOrPolar(modelCoords,
                                                                QPointF (angle2, UNIT_LENGTH));

    // Identify the axis point that is more in the center of the other two axis points. The arc is then drawn
    // from one of the other two points to the other. Center point has smaller angles with the other points
    double sumAngle0 = angleBetweenVectors(pos0, pos1) + angleBetweenVectors(pos0, pos2);
    double sumAngle1 = angleBetweenVectors(pos1, pos0) + angleBetweenVectors(pos1, pos2);
    double sumAngle2 = angleBetweenVectors(pos2, pos0) + angleBetweenVectors(pos2, pos1);
    if ((sumAngle0 <= sumAngle1) && (sumAngle0 <= sumAngle2)) {

      // Point 0 is in the middle. Either or neither of points 1 and 2 may be along point 0
      if ((angleFromVectorToVector (pos0, pos1) < 0) ||
          (angleFromVectorToVector (pos0, pos2) > 0)) {
        path += QString ("from 1=%1 through 0 to 2=%2").arg (angle1).arg (angle2);
        xMin = angle1;
        xMax = angle2;
      } else {
        path += QString ("from 2=%1 through 0 to 1=%2").arg (angle2).arg (angle1);
        xMin = angle2;
        xMax = angle1;
      }
    } else if ((sumAngle1 <= sumAngle0) && (sumAngle1 <= sumAngle2)) {

      // Point 1 is in the middle. Either or neither of points 0 and 2 may be along point 1
      if ((angleFromVectorToVector (pos1, pos0) < 0) ||
          (angleFromVectorToVector (pos1, pos2) > 0)) {
        path += QString ("from 0=%1 through 1 to 2=%2").arg (angle0).arg (angle2);
        xMin = angle0;
        xMax = angle2;
      } else {
        path += QString ("from 2=%1 through 1 to 0=%2").arg (angle2).arg (angle0);
        xMin = angle2;
        xMax = angle0;
      }
    } else {

      // Point 2 is in the middle. Either or neither of points 0 and 1 may be along point 2
      if ((angleFromVectorToVector (pos2, pos0) < 0) ||
          (angleFromVectorToVector (pos2, pos1) > 0)) {
        path += QString ("from 0=%1 through 2 to 1=%2").arg (angle0).arg (angle1);
        xMin = angle0;
        xMax = angle1;
      } else {
        path += QString ("from 1=%1 through 2 to 0=%2").arg (angle1).arg (angle0);
        xMin = angle1;
        xMax = angle0;
      }
    }

    // Make sure theta is increasing
    while (xMax < xMin) {

      double thetaPeriod = modelCoords.thetaPeriod();

      path += QString (" xMax+=%1").arg (thetaPeriod);
      xMax += thetaPeriod;

    }
  }

  LOG4CPP_INFO_S ((*mainCat)) << "Checker::adjustPolarAngleRanges path=(" << path.toLatin1().data() << ")";
}

void Checker::prepareForDisplay (const QPolygonF &polygon,
                                 int pointRadius,
                                 const DocumentModelAxesChecker &modelAxesChecker,
                                 const DocumentModelCoords &modelCoords,
                                 DocumentAxesPointsRequired documentAxesPointsRequired)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Checker::prepareForDisplay";

  ENGAUGE_ASSERT ((polygon.count () == NUM_AXES_POINTS_3) ||
                  (polygon.count () == NUM_AXES_POINTS_4));

  // Convert pixel coordinates in QPointF to screen and graph coordinates in Point using
  // identity transformation, so this routine can reuse computations provided by Transformation
  QList<Point> points;
  QPolygonF::const_iterator itr;
  for (itr = polygon.begin (); itr != polygon.end (); itr++) {

    const QPointF &pF = *itr;

    Point p (DUMMY_CURVE_NAME,
             pF,
             pF,
             false);
    points.push_back (p);
  }

  // Screen and graph coordinates are treated as the same, so identity transform is used
  Transformation transformIdentity;
  transformIdentity.identity();
  prepareForDisplay (points,
                     pointRadius,
                     modelAxesChecker,
                     modelCoords,
                     transformIdentity,
                     documentAxesPointsRequired);
}

void Checker::prepareForDisplay (const QList<Point> &points,
                                 int pointRadius,
                                 const DocumentModelAxesChecker &modelAxesChecker,
                                 const DocumentModelCoords &modelCoords,
                                 const Transformation &transformation,
                                 DocumentAxesPointsRequired documentAxesPointsRequired)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Checker::prepareForDisplay "
                              << " transformation=" << transformation;

  ENGAUGE_ASSERT ((points.count () == NUM_AXES_POINTS_3) ||
                  (points.count () == NUM_AXES_POINTS_4));

  // Remove previous lines
  m_gridLines.clear ();

  bool fourPoints = (documentAxesPointsRequired == DOCUMENT_AXES_POINTS_REQUIRED_4);

  // Get the min and max of x and y. We initialize yTo to prevent compiler warning
  double xFrom = 0, xTo = 0, yFrom = 0, yTo = 0;
  int i;
  bool firstX = true;
  bool firstY = true;
  for (i = 0; i < points.count(); i++) {
    if (!fourPoints || (points.at(i).isXOnly() && fourPoints)) {

      // X coordinate is defined
      if (firstX) {
        xFrom = points.at(i).posGraph().x();
        xTo   = points.at(i).posGraph().x();
        firstX = false;
      } else {
        xFrom = qMin (xFrom, points.at(i).posGraph().x());
        xTo   = qMax (xTo  , points.at(i).posGraph().x());
      }
    }

    if (!fourPoints || (!points.at(i).isXOnly() && fourPoints)) {

      // Y coordinate is defined
      if (firstY) {
        yFrom = points.at(i).posGraph().y();
        yTo   = points.at(i).posGraph().y();
        firstY = false;
      } else {
        yFrom = qMin (yFrom, points.at(i).posGraph().y());
        yTo   = qMax (yTo  , points.at(i).posGraph().y());
      }
    }
  }

  // Min and max of angles needs special processing since periodicity introduces some ambiguity. This is a noop for rectangular coordinates
  // and for polar coordinates when periodicity is not an issue
  adjustPolarAngleRanges (modelCoords,
                          transformation,
                          points,
                          xFrom,
                          xTo,
                          yFrom);

  // Draw the bounding box as four sides. In polar plots the bottom side is zero-length, with pie shape resulting
  GridLineFactory factory (m_scene,
                           pointRadius,
                           points,
                           modelCoords);
  m_gridLines.add (factory.createGridLine (xFrom, yFrom, xFrom, yTo  , transformation));
  m_gridLines.add (factory.createGridLine (xFrom, yTo  , xTo  , yTo  , transformation));
  m_gridLines.add (factory.createGridLine (xTo  , yTo  , xTo  , yFrom, transformation));
  m_gridLines.add (factory.createGridLine (xTo  , yFrom, xFrom, yFrom, transformation));

  updateModelAxesChecker (modelAxesChecker);
}

void Checker::setVisible (bool visible)
{
  m_gridLines.setVisible (visible);
}

void Checker::updateModelAxesChecker (const DocumentModelAxesChecker &modelAxesChecker)
{
  QColor color = ColorPaletteToQColor (modelAxesChecker.lineColor());
  QPen pen (QBrush (color), CHECKER_POINTS_WIDTH);

  m_gridLines.setPen (pen);
}
