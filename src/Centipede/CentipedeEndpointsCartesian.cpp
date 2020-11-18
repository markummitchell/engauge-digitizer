/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedeEndpointsCartesian.h"
#include "mmsubs.h"
#include <qdebug.h>
#include <qmath.h>
#include <QPointF>
#include "Transformation.h"

const int NUM_CIRCLE_POINTS = 400; // Use many points so complicated (linear, log, high dynamic range) interpolation is not needed

CentipedeEndpointsCartesian::CentipedeEndpointsCartesian(const DocumentModelGuideline &modelGuideline,
                                                         const Transformation &transformation,
                                                         const QPointF &posClickScreen) :
  CentipedeEndpointsAbstract (modelGuideline,
                              transformation,
                              posClickScreen)
{
}

CentipedeEndpointsCartesian::~CentipedeEndpointsCartesian ()
{
}

QPointF CentipedeEndpointsCartesian::posScreenConstantXTCommon (double radius,
                                                                CentipedeIntersectionType intersectionType) const
{
  QPointF posScreenBest;
  double yRBest = (intersectionType == CENTIPEDE_INTERSECTION_HIGH ? 999.9 : -999.9);

  // Click point
  QPointF posClickGraph;
  transformation().transformScreenToRawGraph (posClickScreen (),
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
    if (intersectionType == CENTIPEDE_INTERSECTION_CENTER) {

      // CENTIPEDE_INTERSECTION_CENTER
      save = isFirst ||
          (qAbs (yGraphPrevious - yClick) < qAbs (yRBest - yClick));

    } else {

      // CENTIPEDE_INTERSECTION_HIGH or CENTIPEDE_INTERSECTION_LOW
      bool transitionUp = (xGraphPrevious - epsilon <= xClick) && (xClick < xGraphNext + epsilon);
      bool transitionDown = (xGraphNext - epsilon <= xClick) && (xClick < xGraphPrevious + epsilon);

      if (transitionDown || transitionUp) {

        // Transition occurred so save if best so far
        if (isFirst ||
            (intersectionType == CENTIPEDE_INTERSECTION_HIGH && yGraphPrevious > yRBest) ||
            (intersectionType == CENTIPEDE_INTERSECTION_LOW && yGraphPrevious < yRBest)) {

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

QPointF CentipedeEndpointsCartesian::posScreenConstantXTForHighYR (double radius) const
{
  return posScreenConstantXTCommon (radius,
                                    CENTIPEDE_INTERSECTION_HIGH);
}

QPointF CentipedeEndpointsCartesian::posScreenConstantXTForLowYR (double radius) const
{
  return posScreenConstantXTCommon (radius,
                                    CENTIPEDE_INTERSECTION_LOW);
}

QPointF CentipedeEndpointsCartesian::posScreenConstantYRCommon (double radius,
                                                                CentipedeIntersectionType intersectionType) const
{
  QPointF posScreenBest;
  double xTBest = 0;

  // Click point
  QPointF posClickGraph;
  transformation().transformScreenToRawGraph (posClickScreen (),
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
    if (intersectionType == CENTIPEDE_INTERSECTION_CENTER) {

      // CENTIPEDE_INTERSECTION_CENTER
      save = isFirst ||
          (qAbs (xGraphPrevious - xClick) < qAbs (xTBest - xClick));

    } else {

      // CENTIPEDE_INTERSECTION_HIGH or CENTIPEDE_INTERSECTION_LOW
      bool transitionUp = (yGraphPrevious - epsilon <= yClick) && (yClick < yGraphNext + epsilon);
      bool transitionDown = (yGraphNext - epsilon <= yClick) && (yClick < yGraphPrevious + epsilon);

      if (transitionDown || transitionUp) {

        // Transition occurred so save if best so far
        if (isFirst ||
            (intersectionType == CENTIPEDE_INTERSECTION_HIGH && xGraphPrevious > xTBest) ||
            (intersectionType == CENTIPEDE_INTERSECTION_LOW && xGraphPrevious < xTBest)) {

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

QPointF CentipedeEndpointsCartesian::posScreenConstantYRForCenterXT (double radius) const
{
  return posScreenConstantYRCommon (radius,
                                    CENTIPEDE_INTERSECTION_CENTER);
}

QPointF CentipedeEndpointsCartesian::posScreenConstantYRForHighXT (double radius) const
{
  return posScreenConstantYRCommon (radius,
                                    CENTIPEDE_INTERSECTION_HIGH);
}

QPointF CentipedeEndpointsCartesian::posScreenConstantYRForLowXT (double radius) const
{
  return posScreenConstantYRCommon (radius,
                                    CENTIPEDE_INTERSECTION_LOW);
}
