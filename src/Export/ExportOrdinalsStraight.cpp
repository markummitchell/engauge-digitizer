/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ExportOrdinalsStraight.h"
#include "Logger.h"
#include <qdebug.h>
#include <qmath.h>
#include <QPointF>
#include "Transformation.h"

using namespace std;

ExportOrdinalsStraight::ExportOrdinalsStraight ()
{
}

ExportValuesOrdinal ExportOrdinalsStraight::ordinalsAtIntervalsGraphWithoutTransformation (const Points &points,
                                                                                           double pointsInterval) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportOrdinalsStraight::ordinalsAtIntervalsGraph";

  // Results
  ExportValuesOrdinal ordinals;

  // Integrate the distances for the subintervals
  double distanceAlongSegment = 0;
  QPointF posLast (points [0].posScreen().x(),
                   points [0].posScreen().y());
  double ordinalLast = 0;

  // Simplest method to find the intervals is to break up the curve into many smaller intervals, and then aggregate them
  // into intervals that, as much as possible, have the desired length. Simplicity wins out over accuracy in this
  // approach - accuracy is sacrificed to achieve simplicity
  for (int iP = 0; iP < points.count(); iP++) {

    const Point &pointNew = points.at (iP);
    QPointF posNew = pointNew.posScreen();
    
    QPointF posDelta = posNew - posLast;
    double segmentLength = qSqrt (posDelta.x() * posDelta.x() + posDelta.y() * posDelta.y());

    while (distanceAlongSegment < segmentLength) {

      double sLocal = distanceAlongSegment / segmentLength;

      ordinals.push_back (ordinalLast + sLocal);

      distanceAlongSegment += pointsInterval;
    }

    distanceAlongSegment -= segmentLength;
    ordinalLast = pointNew.ordinal();
    posLast = posNew;
  }

  return ordinals;
}

ExportValuesOrdinal ExportOrdinalsStraight::ordinalsAtIntervalsGraphWithTransformation (const Points &points,
                                                                                        const Transformation &transformation,
                                                                                        double pointsInterval) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportOrdinalsStraight::ordinalsAtIntervalsGraph";

  // Results
  ExportValuesOrdinal ordinals;

  // Integrate the distances for the subintervals
  double distanceAlongSegment = 0;
  QPointF posLast;
  transformation.transformScreenToRawGraph (points [0].posScreen(),
                                            posLast);
  double ordinalLast = 0;

  // Simplest method to find the intervals is to break up the curve into many smaller intervals, and then aggregate them
  // into intervals that, as much as possible, have the desired length. Simplicity wins out over accuracy in this
  // approach - accuracy is sacrificed to achieve simplicity
  for (int iP = 0; iP < points.count(); iP++) {

    const Point &pointNew = points.at (iP);
    QPointF posNew;
    transformation.transformScreenToRawGraph (pointNew.posScreen(),
                                              posNew);

    QPointF posDelta = posNew - posLast;
    double segmentLength = qSqrt (posDelta.x() * posDelta.x() + posDelta.y() * posDelta.y());

    while (distanceAlongSegment < segmentLength) {

      double sLocal = distanceAlongSegment / segmentLength;

      ordinals.push_back (ordinalLast + sLocal);

      distanceAlongSegment += pointsInterval;
    }

    ordinalLast = pointNew.ordinal();
    posLast = posNew;
  }

  return ordinals;
}
