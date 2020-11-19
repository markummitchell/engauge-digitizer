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

QPointF CentipedeEndpointsCartesian::posScreenConstantXCommon (double radius,
                                                               CentipedeIntersectionType intersectionType) const
{
  QPointF posScreenBest;
  double yBest = (intersectionType == CENTIPEDE_INTERSECTION_HIGH ? 999.9 : -999.9);

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
          (qAbs (yGraphPrevious - yClick) < qAbs (yBest - yClick));

    } else {

      // CENTIPEDE_INTERSECTION_HIGH or CENTIPEDE_INTERSECTION_LOW
      bool transitionUp = (xGraphPrevious - epsilon <= xClick) && (xClick < xGraphNext + epsilon);
      bool transitionDown = (xGraphNext - epsilon <= xClick) && (xClick < xGraphPrevious + epsilon);

      if (transitionDown || transitionUp) {

        // Transition occurred so save if best so far
        if (isFirst ||
            (intersectionType == CENTIPEDE_INTERSECTION_HIGH && yGraphPrevious > yBest) ||
            (intersectionType == CENTIPEDE_INTERSECTION_LOW && yGraphPrevious < yBest)) {

          save = true;
        }
      }
    }

    if  (save) {

      // Best so far so save
      isFirst = false;
      posScreenBest = posScreenPrevious;
      yBest = yGraphPrevious;
    }
  }

  return posScreenBest;
}

QPointF CentipedeEndpointsCartesian::posScreenConstantXForHighY (double radius) const
{
  return posScreenConstantXCommon (radius,
                                   CENTIPEDE_INTERSECTION_HIGH);
}

QPointF CentipedeEndpointsCartesian::posScreenConstantXForLowY (double radius) const
{
  return posScreenConstantXCommon (radius,
                                   CENTIPEDE_INTERSECTION_LOW);
}

QPointF CentipedeEndpointsCartesian::posScreenConstantYCommon (double radius,
                                                               CentipedeIntersectionType intersectionType) const
{
  QPointF posScreenBest;
  double xBest = 0;

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
          (qAbs (xGraphPrevious - xClick) < qAbs (xBest - xClick));

    } else {

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

QPointF CentipedeEndpointsCartesian::posScreenConstantYForCenterX (double radius) const
{
  return posScreenConstantYCommon (radius,
                                   CENTIPEDE_INTERSECTION_CENTER);
}

QPointF CentipedeEndpointsCartesian::posScreenConstantYForHighX (double radius) const
{
  return posScreenConstantYCommon (radius,
                                    CENTIPEDE_INTERSECTION_HIGH);
}

QPointF CentipedeEndpointsCartesian::posScreenConstantYForLowX (double radius) const
{
  return posScreenConstantYCommon (radius,
                                   CENTIPEDE_INTERSECTION_LOW);
}
