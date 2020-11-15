/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedeSegmentAbstract.h"
#include "mmsubs.h"
#include <qdebug.h>
#include <qmath.h>
#include <QPointF>
#include "Transformation.h"

const int NUM_CIRCLE_POINTS = 400; // Use many points so complicated (linear, log, high dynamic range) interpolation is not needed

CentipedeSegmentAbstract::CentipedeSegmentAbstract(const DocumentModelGuideline &modelGuideline,
                                                   const Transformation &transformation,
                                                   const QPointF &posClickScreen) :
  m_modelGuideline (modelGuideline),
  m_transformation (transformation),
  m_posClickScreen (posClickScreen)
{
}

CentipedeSegmentAbstract::~CentipedeSegmentAbstract ()
{
}

double CentipedeSegmentAbstract::angleScreenConstantYRCenterAngle (double radiusAboutClick) const
{
  QPointF posScreenBest;
  double xTBest = 0;

  // Click point
  QPointF posClickGraph;
  m_transformation.transformScreenToRawGraph (m_posClickScreen,
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

void CentipedeSegmentAbstract::angleScreenConstantYRHighLowAngles (double radiusAboutClick,
                                                                   double angleCenter,
                                                                   double &angleLow,
                                                                   double &angleHigh) const
{
  // Click point
  QPointF posClickGraph;
  m_transformation.transformScreenToRawGraph (m_posClickScreen,
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

double CentipedeSegmentAbstract::closestAngleToCentralAngle (double angleCenter,
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

void CentipedeSegmentAbstract::generatePreviousAndNextPoints (double radiusAboutClick,
                                                              int i,
                                                              QPointF &posGraphPrevious,
                                                              QPointF &posGraphNext,
                                                              QPointF &posScreenPrevious,
                                                              double angleOffset) const
{
  double angleBefore = angleOffset + 2.0 * M_PI * (double) i / (double) NUM_CIRCLE_POINTS;
  double angleAfter = angleOffset + 2.0 * M_PI * (double) (i + 1) / (double) NUM_CIRCLE_POINTS;
  posScreenPrevious = m_posClickScreen + QPointF (radiusAboutClick * cos (angleBefore),
                                                  radiusAboutClick * sin (angleBefore));
  QPointF posScreenNext = m_posClickScreen + QPointF (radiusAboutClick * cos (angleAfter),
                                                      radiusAboutClick * sin (angleAfter));

  m_transformation.transformScreenToRawGraph (posScreenPrevious,
                                              posGraphPrevious);
  m_transformation.transformScreenToRawGraph (posScreenNext,
                                              posGraphNext);
}

const DocumentModelGuideline &CentipedeSegmentAbstract::modelGuideline () const
{
  return m_modelGuideline;
}

QPointF CentipedeSegmentAbstract::posClickScreen () const
{
  return m_posClickScreen;
}

QPointF CentipedeSegmentAbstract::posScreenConstantXTCommon (double radius,
                                                             IntersectionType intersectionType) const
{
  QPointF posScreenBest;
  double yRBest = (intersectionType == INTERSECTION_HIGH ? 999.9 : -999.9);

  // Click point
  QPointF posClickGraph;
  m_transformation.transformScreenToRawGraph (m_posClickScreen,
                                              posClickGraph);
  double xClick = posClickGraph.x();
  double yClick = posClickGraph.y();

  // Iterate points around the circle
  bool isFirst = true;
  for (int i = 0; i < NUM_CIRCLE_POINTS; i++) {
    QPointF posGraphPrevious, posGraphNext, posScreenPrevious;
    generatePreviousAndNextPoints (radius,
                                   i,
                                   posGraphPrevious,
                                   posGraphNext,
                                   posScreenPrevious);

    double xGraphPrevious = posGraphPrevious.x();
    double yGraphPrevious = posGraphPrevious.y();
    double xGraphNext = posGraphNext.x();
    double epsilon = qAbs (xGraphPrevious - xGraphNext) / 10.0; // Allow for roundoff

    bool save = false;
    if (intersectionType == INTERSECTION_CENTER) {

      // INTERSECTION_CENTER
      save = isFirst ||
          (qAbs (yGraphPrevious - yClick) < qAbs (yRBest - yClick));

    } else {

      // INTERSECTION_HIGH or INTERSECTION_LOW
      bool transitionUp = (xGraphPrevious - epsilon <= xClick) && (xClick < xGraphNext + epsilon);
      bool transitionDown = (xGraphNext - epsilon <= xClick) && (xClick < xGraphPrevious + epsilon);

      if (transitionDown || transitionUp) {

        // Transition occurred so save if best so far
        if (isFirst ||
            (intersectionType == INTERSECTION_HIGH && yGraphPrevious > yRBest) ||
            (intersectionType == INTERSECTION_LOW && yGraphPrevious < yRBest)) {

          save = true;
        }
      }
    }

    if  (save) {

      // Best so far so save
      isFirst = false;
      posScreenBest = posScreenPrevious;
      yRBest = yGraphPrevious;
    }
  }

  return posScreenBest;
}

QPointF CentipedeSegmentAbstract::posScreenConstantXTForHighYR (double radius) const
{
  return posScreenConstantXTCommon (radius,
                                    INTERSECTION_HIGH);
}

QPointF CentipedeSegmentAbstract::posScreenConstantXTForLowYR (double radius) const
{
  return posScreenConstantXTCommon (radius,
                                    INTERSECTION_LOW);
}

QPointF CentipedeSegmentAbstract::posScreenConstantYRCommon (double radius,
                                                             IntersectionType intersectionType) const
{
  QPointF posScreenBest;
  double xTBest = 0;

  // Click point
  QPointF posClickGraph;
  m_transformation.transformScreenToRawGraph (m_posClickScreen,
                                              posClickGraph);
  double xClick = posClickGraph.x();
  double yClick = posClickGraph.y();

  // Iterate points around the circle
  bool isFirst = true;
  for (int i = 0; i < NUM_CIRCLE_POINTS; i++) {
    QPointF posGraphPrevious, posGraphNext, posScreenPrevious;
    generatePreviousAndNextPoints (radius,
                                   i,
                                   posGraphPrevious,
                                   posGraphNext,
                                   posScreenPrevious);

    double xGraphPrevious = posGraphPrevious.x();
    double yGraphPrevious = posGraphPrevious.y();
    double yGraphNext = posGraphNext.y();
    double epsilon = qAbs (yGraphPrevious - yGraphNext) / 10.0; // Allow for roundoff

    bool save = false;
    if (intersectionType == INTERSECTION_CENTER) {

      // INTERSECTION_CENTER
      save = isFirst ||
          (qAbs (xGraphPrevious - xClick) < qAbs (xTBest - xClick));

    } else {

      // INTERSECTION_HIGH or INTERSECTION_LOW
      bool transitionUp = (yGraphPrevious - epsilon <= yClick) && (yClick < yGraphNext + epsilon);
      bool transitionDown = (yGraphNext - epsilon <= yClick) && (yClick < yGraphPrevious + epsilon);

      if (transitionDown || transitionUp) {

        // Transition occurred so save if best so far
        if (isFirst ||
            (intersectionType == INTERSECTION_HIGH && xGraphPrevious > xTBest) ||
            (intersectionType == INTERSECTION_LOW && xGraphPrevious < xTBest)) {

          save = true;
        }
      }
    }

    if (save) {

      // Best so far so save
      isFirst = false;
      posScreenBest = posScreenPrevious;
      xTBest = xGraphPrevious;
    }
  }

  return posScreenBest;
}

QPointF CentipedeSegmentAbstract::posScreenConstantYRForCenterXT (double radius) const
{
  return posScreenConstantYRCommon (radius,
                                    INTERSECTION_CENTER);
}

QPointF CentipedeSegmentAbstract::posScreenConstantYRForHighXT (double radius) const
{
  return posScreenConstantYRCommon (radius,
                                    INTERSECTION_HIGH);
}

QPointF CentipedeSegmentAbstract::posScreenConstantYRForLowXT (double radius) const
{
  return posScreenConstantYRCommon (radius,
                                    INTERSECTION_LOW);
}

Transformation CentipedeSegmentAbstract::transformation () const
{
  return m_transformation;
}
