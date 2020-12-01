/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedeEndpointsPolar.h"
#include "CentipedeDebugPolar.h"
#include "CoordsType.h"
#include "Logger.h"
#include "mmsubs.h"
#include <qdebug.h>
#include <qmath.h>
#include <QPointF>
#include "QtToString.h"
#include "Shear.h"
#include "Transformation.h"

const int NUM_CIRCLE_POINTS = 400; // Use many points so complicated (linear, log, high dynamic range) interpolation is not needed
const int NUM_LINE_POINTS = 400; // Use many points so complicated (linear, log, high dynamic range) interpolation is not needed

CentipedeEndpointsPolar::CentipedeEndpointsPolar(const DocumentModelCoords &modelCoords,
                                                 const DocumentModelGuideline &modelGuideline,
                                                 const Transformation &transformation,
                                                 const QPointF &posClickScreen) :
  CentipedeEndpointsAbstract (modelGuideline,
                              transformation,
                              posClickScreen),
  m_modelCoords (modelCoords)
{
}

CentipedeEndpointsPolar::~CentipedeEndpointsPolar ()
{
}

void CentipedeEndpointsPolar::posScreenConstantRHighLow (double radiusAboutClick,
                                                         const QPointF &posOriginScreen,
                                                         const QPointF &posScreen0,
                                                         const QPointF &posScreen90,
                                                         QPointF &posLow,
                                                         QPointF &posHigh) const
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
                                   posScreenPreviousLow);
    generatePreviousAndNextPoints (radiusAboutClick,
                                   - i,
                                   posGraphPreviousHigh,
                                   posGraphNextHigh,
                                   posScreenPreviousHigh);

    double epsilon = qAbs (posGraphPreviousLow.y() - posGraphNextLow.y()) / 10.0; // Allow for roundoff

    bool transitionUpLow = (posGraphPreviousLow.y() - epsilon <= yClick) && (yClick < posGraphNextLow.y() + epsilon);
    bool transitionDownLow = (posGraphNextLow.y() - epsilon <= yClick) && (yClick < posGraphPreviousLow.y() + epsilon);
    bool transitionUpHigh = (posGraphPreviousHigh.y() - epsilon <= yClick) && (yClick < posGraphNextHigh.y() + epsilon);
    bool transitionDownHigh = (posGraphNextHigh.y() - epsilon <= yClick) && (yClick < posGraphPreviousHigh.y() + epsilon);

    if (isFirstLow  && (transitionDownLow || transitionUpLow)) {
      // Found the first (=best) low value
      isFirstLow = false;
      posLow = (posGraphPreviousLow + posGraphNextLow) / 2.0; // Average
      if (!isFirstHigh) {
        break; // Done
      }
    }

    if (isFirstHigh && (transitionDownHigh || transitionUpHigh)) {
      // Found the first (=best) high value
      isFirstHigh = false;
      posHigh = (posGraphPreviousHigh + posGraphNextHigh) / 2.0;
      if (!isFirstLow) {
        break; // Done
      }
    }
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

void CentipedeEndpointsPolar::ellipseScreenConstantRForTHighLowAngles (const Transformation &transformation,
                                                                       const QPointF &posClickScreen,
                                                                       double &angleRotation,
                                                                       QRectF &rectBounding,
                                                                       CentipedeDebugPolar &debugPolar)
{
  //  LOG4CPP is below

  QPointF posClickGraph;
  transformation.transformScreenToRawGraph (posClickScreen,
                                            posClickGraph);
  double rGraph = posClickGraph.y();

  // Points at origin, then 0  degrees at range rGraph
  QPointF posScreenOrigin, posScreen0, posScreen90, posScreen180;
  transformation.transformRawGraphToScreen (QPointF (tAtOrigin (), rAtOrigin ()),
                                            posScreenOrigin);
  transformation.transformRawGraphToScreen (QPointF (0, rGraph),
                                            posScreen0);
  transformation.transformRawGraphToScreen (QPointF (90.0, rGraph),
                                            posScreen90);
  transformation.transformRawGraphToScreen (QPointF (180.0, rGraph),
                                            posScreen180);

  QPointF centerTo90 = posScreen90 - posScreenOrigin;

  // Corners of parallelogram circumscribing the ellipse
  QPointF posScreenTL = posScreen180 + centerTo90;
  QPointF posScreenTR = posScreen0 + centerTo90;
  QPointF posScreenBL = posScreen180 - centerTo90;
  QPointF posScreenBR = posScreen0 - centerTo90;

  double aAligned = 0, bAligned = 0;
  ellipseFromParallelogram (posScreenTL.x() - posScreenOrigin.x(),
                            posScreenTL.y() - posScreenOrigin.y(),
                            posScreenTR.x() - posScreenOrigin.x(),
                            posScreenTR.y() - posScreenOrigin.y(),
                            posScreenBR.x() - posScreenOrigin.x(),
                            posScreenBR.y() - posScreenOrigin.y(),
                            angleRotation,
                            aAligned,
                            bAligned);

  double angleGraphAxisFromScreenAxis = qAtan2 (posScreen0.y() - posScreenOrigin.y(),
                                                posScreen0.x() - posScreenOrigin.x());

  debugPolar = CentipedeDebugPolar (posScreenTL,
                                    posScreenTR,
                                    posScreenBL,
                                    posScreenBR,
                                    angleGraphAxisFromScreenAxis,
                                    angleRotation,
                                    aAligned,
                                    bAligned,
                                    rGraph);

  // Bounding rectangle before rotation. We make sure the rectangle is normalized which at one point
  // seemed to prevent drawing artifacts
  rectBounding = QRectF (-1.0 * aAligned,
                         -1.0 * bAligned,
                         2.0 * aAligned,
                         2.0 * bAligned);

  LOG4CPP_INFO_S ((*mainCat)) << "CentipedeEndpointsPolar::ellipseScreenConstantRForTHighLowAngles angleRotation="
                              << qRadiansToDegrees (angleRotation) << " posScreen0=" << QPointFToString (posScreen0).toLatin1().data()
                              << " posScreen90=" << QPointFToString (posScreen90).toLatin1().data()
                              << " a=" << aAligned
                              << " b=" << bAligned;
}

QPointF CentipedeEndpointsPolar::posScreenConstantRCommon (double radius,
                                                           CentipedeIntersectionType intersectionType) const
{
  QPointF posScreenBest;
  double xBest = 0;

  // Click point
  QPointF posClickGraph;
  transformation().transformScreenToRawGraph (posClickScreen (),
                                              posClickGraph);
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

    // CENTIPEDE_INTERSECTION_HIGH or CENTIPEDE_INTERSECTION_LOW
    bool transitionUp = (yGraphPrevious - epsilon <= yClick) && (yClick < yGraphNext + epsilon);
    bool transitionDown = (yGraphNext - epsilon <= yClick) && (yClick < yGraphPrevious + epsilon);

    if (transitionDown || transitionUp) {

      // Transition occurred so save if best so far
      if (isFirst ||
          (intersectionType == CENTIPEDE_INTERSECTION_HIGH && xGraphPrevious > xBest) ||
          (intersectionType == CENTIPEDE_INTERSECTION_LOW && xGraphPrevious < xBest)) {

        save = true;
      }
    }

    if (save) {

      // Best so far so save
      isFirst = false;
      posScreenBest = posScreenPrevious;
      xBest = xGraphPrevious;
    }
  }

  return posScreenBest;
}

QPointF CentipedeEndpointsPolar::posScreenConstantRForHighT (double radius) const
{
  return posScreenConstantRCommon (radius,
                                    CENTIPEDE_INTERSECTION_HIGH);
}

QPointF CentipedeEndpointsPolar::posScreenConstantRForLowT (double radius) const
{
  return posScreenConstantRCommon (radius,
                                   CENTIPEDE_INTERSECTION_LOW);
}

void CentipedeEndpointsPolar::posScreenConstantTForRHighLow (double radius,
                                                             QPointF &posLow,
                                                             QPointF &posHigh) const
{
  // This replaces CentipedeSegmentAbstract::posScreenConstantXTCommon since the polar coordinate radial vector
  // can be on the other side of the origin if the ellipse center is within radius of the origin. This routine
  // uses a different strategy of iterating on a line rather than a circle (since circle has tough issues with quadrants
  // and 360 rollover)

  // Origin and screen vector to center
  QPointF posOriginScreen;
  transformation().transformRawGraphToScreen (QPointF (tAtOrigin (), rAtOrigin ()),
                                              posOriginScreen);
  QPointF vecCenter = posClickScreen() - posOriginScreen;

  // Number of solutions found
  int numberFound = 0;

  // Iterate points along the line from -2*vecCenterMagnitude to +2*vecCenterMagnitude
  const double DOUBLE_PLUS_EXTRA = 2.1;
  double maxRadius = DOUBLE_PLUS_EXTRA * (magnitude (vecCenter) + radius);
  QPointF posStart = posOriginScreen - 2 * maxRadius * normalize (vecCenter);
  QPointF posStop = posOriginScreen + 2 * maxRadius * normalize (vecCenter);
  for (int i = 0; i < NUM_LINE_POINTS; i++) {
    double sPrevious = (double) i / (double) NUM_LINE_POINTS;
    double sNext = (double) (i + 1) / (double) NUM_LINE_POINTS;

    QPointF posPrevious = (1.0 - sPrevious) * posStart + sPrevious * posStop;
    QPointF posNext = (1.0 - sNext) * posStart + sNext * posStop;

    double distancePrevious = magnitude (posPrevious - posClickScreen());
    double distanceNext = magnitude (posNext - posClickScreen());

    if ((distancePrevious < radius && radius <= distanceNext) ||
        (distancePrevious > radius && radius >= distanceNext)) {

      if (numberFound == 0) {
        posLow = (posPrevious + posNext) / 2.0; // Average for accuracy
      } else if (numberFound == 1) {
        posHigh = (posPrevious + posNext) / 2.0; // Average for accuracy
        break; // Done
      }

      ++numberFound;
    }
  }
}

double CentipedeEndpointsPolar::posScreenToEllipseAngle (const QPointF &posScreen,
                                                         const QPointF &posScreenOrigin,
                                                         const QPointF &posScreen0,
                                                         const QPointF &posScreen90) const
{
  Shear shear;

  QPointF posProjected = shear.projectOntoBasisVectors (posScreen0 - posScreenOrigin,
                                                        posScreen90 - posScreenOrigin,
                                                        posScreen - posScreenOrigin);

  return qAtan2 (posProjected.y(),
                 posProjected.x());
}

double CentipedeEndpointsPolar::rAtOrigin () const
{
  // Values that work for both linear and log
  if (m_modelCoords.coordScaleYRadius() == COORD_SCALE_LOG) {
    return m_modelCoords.originRadius();
  } else {
    return 0;
  }
}

double CentipedeEndpointsPolar::tAtOrigin () const
{
  // Value that works for all units (radians, degrees, gradians)
  return 0.0;
}
