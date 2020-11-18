/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedeEndpointsPolar.h"
#include "mmsubs.h"
#include <qdebug.h>
#include <qmath.h>
#include <QPointF>
#include "Transformation.h"

const int NUM_CIRCLE_POINTS = 400; // Use many points so complicated (linear, log, high dynamic range) interpolation is not needed

CentipedeEndpointsPolar::CentipedeEndpointsPolar(const DocumentModelGuideline &modelGuideline,
                                                 const Transformation &transformation,
                                                 const QPointF &posClickScreen) :
  CentipedeEndpointsAbstract (modelGuideline,
                              transformation,
                              posClickScreen)
{
}

CentipedeEndpointsPolar::~CentipedeEndpointsPolar ()
{
}

double CentipedeEndpointsPolar::angleScreenConstantYRCenterAngle (double radiusAboutClick) const
{
  QPointF posScreenBest;
  double xTBest = 0;

  // Click point
  QPointF posClickGraph;
  transformation().transformScreenToRawGraph (posClickScreen(),
                                              posClickGraph);
  double xClick = posClickGraph.x();

  // Iterate points around the circle starting at an arbitrary point
  bool isFirst = true;
  for (int i = 0; i < NUM_CIRCLE_POINTS; i++) {
    QPointF posGraphPrevious, posGraphNext, posScreenPrevious;
    generatePreviousAndNextPoints (radiusAboutClick,
                                   i,
                                   posGraphPrevious,
                                   posGraphNext,
                                   posScreenPrevious);

    double xGraphPrevious = posGraphPrevious.x();

    if (isFirst ||
        (qAbs (xGraphPrevious - xClick) < qAbs (xTBest - xClick))) {

      // Best so far so save
      isFirst = false;
      posScreenBest = posScreenPrevious;
      xTBest = xGraphPrevious;
    }
  }

  return qDegreesToRadians (xTBest);
}

void CentipedeEndpointsPolar::angleScreenConstantYRHighLowAngles (double radiusAboutClick,
                                                                   double angleCenter,
                                                                   double &angleLow,
                                                                   double &angleHigh) const
{
  // Click point
  QPointF posClickGraph;
  transformation().transformScreenToRawGraph (posClickScreen(),
                                              posClickGraph);
  double yClick = posClickGraph.y();

  // Iterate points around the circle starting at angleCenter, and going in two different
  // directions (clockwise for angleHigh and counterclockwise for angleLow)
  bool isFirstLow = true, isFirstHigh = true;
  for (int i = 0; i < NUM_CIRCLE_POINTS; i++) {
    QPointF posGraphPreviousLow, posGraphNextLow, posScreenPreviousLow;
    QPointF posGraphPreviousHigh, posGraphNextHigh, posScreenPreviousHigh;
    generatePreviousAndNextPoints (radiusAboutClick,
                                   i,
                                   posGraphPreviousLow,
                                   posGraphNextLow,
                                   posScreenPreviousLow,
                                   angleCenter);
    generatePreviousAndNextPoints (radiusAboutClick,
                                   - i,
                                   posGraphPreviousHigh,
                                   posGraphNextHigh,
                                   posScreenPreviousHigh,
                                   angleCenter);

    double epsilon = qAbs (posGraphPreviousLow.y() - posGraphNextLow.y()) / 10.0; // Allow for roundoff

    bool transitionUpLow = (posGraphPreviousLow.y() - epsilon <= yClick) && (yClick < posGraphNextLow.y() + epsilon);
    bool transitionDownLow = (posGraphNextLow.y() - epsilon <= yClick) && (yClick < posGraphPreviousLow.y() + epsilon);
    bool transitionUpHigh = (posGraphPreviousHigh.y() - epsilon <= yClick) && (yClick < posGraphNextHigh.y() + epsilon);
    bool transitionDownHigh = (posGraphNextHigh.y() - epsilon <= yClick) && (yClick < posGraphPreviousHigh.y() + epsilon);

    if (isFirstLow  && (transitionDownLow || transitionUpLow)) {
      // Found the first (=best) low value
      isFirstLow = false;
      angleLow = qDegreesToRadians ((posGraphPreviousLow.x() + posGraphNextLow.x()) / 2.0); // Average
      if (!isFirstHigh) {
        break; // Done
      }
    }

    if (isFirstHigh && (transitionDownHigh || transitionUpHigh)) {
      // Found the first (=best) high value
      isFirstHigh = false;
      angleHigh = qDegreesToRadians ((posGraphPreviousHigh.x() + posGraphNextHigh.x()) / 2.0); // Average
      if (!isFirstLow) {
        break; // Done
      }
    }
  }

  // Fix quadrant/cycle transition issues
  angleLow = closestAngleToCentralAngle (angleCenter, angleLow);
  angleHigh = closestAngleToCentralAngle (angleCenter, angleHigh);
  while (angleHigh < angleLow) {
    // Cycle issues have been addressed so remaining issue is just reordering
    double temp = angleLow;
    angleLow = angleHigh;
    angleHigh = temp;
  }
}

double CentipedeEndpointsPolar::closestAngleToCentralAngle (double angleCenter,
                                                            double angleOld) const
{
  // Loop to find closest angle to angleCenter
  bool isFirst = true;
  double angleNew = angleOld;
  for (int delta = -360; delta <= 360; delta += 360) {
    double angleNext = angleOld + qDegreesToRadians ((double) delta);
    if (isFirst || (qAbs (angleNext - angleCenter) < qAbs (angleNew - angleCenter))) {
      isFirst = false;
      angleNew = angleNext;
    }
  }

  return angleNew;
}
