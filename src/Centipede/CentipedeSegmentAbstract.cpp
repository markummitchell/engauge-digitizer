/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedeSegmentAbstract.h"
#include "mmsubs.h"
#include <qmath.h>
#include <qdebug.h>
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

double CentipedeSegmentAbstract::angleScreenConstantYRCommon (double radiusAboutClick,
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
    generatePreviousAndNextPoints (radiusAboutClick,
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

  return qDegreesToRadians (xTBest);
}

double CentipedeSegmentAbstract::angleScreenConstantYRCenterAngle (double radiusAboutClick) const
{
  return angleScreenConstantYRCommon (radiusAboutClick,
                                      INTERSECTION_CENTER);
}

double CentipedeSegmentAbstract::angleScreenConstantYRHighAngle (double radiusAboutClick) const
{
  return angleScreenConstantYRCommon (radiusAboutClick,
                                      INTERSECTION_HIGH);
}

double CentipedeSegmentAbstract::angleScreenConstantYRLowAngle (double radius) const
{
  return angleScreenConstantYRCommon (radius,
                                      INTERSECTION_LOW);
}

double angleScreenConstantYRLowAngle (double radius);


void CentipedeSegmentAbstract::generatePreviousAndNextPoints (double radiusAboutClick,
                                                              int i,
                                                              QPointF &posGraphPrevious,
                                                              QPointF &posGraphNext,
                                                              QPointF &posScreenPrevious) const
{
  double angleBefore = 2.0 * M_PI * (double) i / (double) NUM_CIRCLE_POINTS;
  double angleAfter = 2.0 * M_PI * (double) (i + 1) / (double) NUM_CIRCLE_POINTS;
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
  double yRBest = 0;

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
