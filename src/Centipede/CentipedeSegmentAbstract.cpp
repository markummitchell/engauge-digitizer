/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedeSegmentAbstract.h"
#include <qmath.h>
#include <QPointF>
#include "Transformation.h"

const int NUM_CIRCLE_POINTS = 2000; // Use many points so complicated (linear, log, high dynamic range) interpolation is not needed
const double PI = 3.1415926535;

CentipedeSegmentAbstract::CentipedeSegmentAbstract(const DocumentModelGuideline &modelGuideline,
                                                   const Transformation &transformation,
                                                   const QPointF &posCenterScreen) :
  m_modelGuideline (modelGuideline),
  m_transformation (transformation),
  m_posCenterScreen (posCenterScreen)
{
}

CentipedeSegmentAbstract::~CentipedeSegmentAbstract ()
{
}

void CentipedeSegmentAbstract::generatePreviousAndNextPoints (double radius,
                                                              int i,
                                                              QPointF &posGraphPrevious,
                                                              QPointF &posGraphNext,
                                                              QPointF &posScreenPrevious) const
{
  double angleBefore = 2.0 * PI * (double) i / (double) NUM_CIRCLE_POINTS;
  double angleAfter = 2.0 * PI * (double) (i + 1) / (double) NUM_CIRCLE_POINTS;
  posScreenPrevious = m_posCenterScreen + QPointF (radius * cos (angleBefore),
                                                   radius * sin (angleBefore));
  QPointF posScreenNext = m_posCenterScreen + QPointF (radius * cos (angleAfter),
                                                       radius * sin (angleAfter));

  m_transformation.transformScreenToRawGraph (posScreenPrevious,
                                              posGraphPrevious);
  m_transformation.transformScreenToRawGraph (posScreenNext,
                                              posGraphNext);
}

const DocumentModelGuideline &CentipedeSegmentAbstract::modelGuideline () const
{
  return m_modelGuideline;
}

QPointF CentipedeSegmentAbstract::posCenterScreen () const
{
  return m_posCenterScreen;
}

QPointF CentipedeSegmentAbstract::posScreenConstantXTHighYR (double radius) const
{
  return posScreenConstantXTForHighLowYR (radius,
                                         true);
}

QPointF CentipedeSegmentAbstract::posScreenConstantXTLowYR (double radius) const
{
  return posScreenConstantXTForHighLowYR (radius,
                                         false);
}

QPointF CentipedeSegmentAbstract::posScreenConstantXTForHighLowYR (double radius,
                                                                   bool wantHigh) const
{
  QPointF posScreenBest;
  double yRBest = 0;

  QPointF posCenterGraph;
  m_transformation.transformScreenToRawGraph (m_posCenterScreen,
                                              posCenterGraph);
  double xCenter = posCenterGraph.x();

  bool isFirst = true;
  for (int i = 0; i < NUM_CIRCLE_POINTS; i++) {
    QPointF posGraphPrevious, posGraphNext, posScreenPrevious;
    generatePreviousAndNextPoints (radius,
                                   i,
                                   posGraphPrevious,
                                   posGraphNext,
                                   posScreenPrevious);

    double xGraphPrevious = posGraphPrevious.x();
    double xGraphNext = posGraphNext.x();
    double epsilon = qAbs (xGraphPrevious - xGraphNext) / 10.0; // Allow for roundoff

    bool transitionUp = (xGraphPrevious - epsilon <= xCenter) && (xCenter < xGraphNext + epsilon);
    bool transitionDown = (xGraphNext - epsilon <= xCenter) && (xCenter < xGraphPrevious + epsilon);

    if (transitionDown || transitionUp) {

      // Transition occurred so save if best so far
      double y = posGraphPrevious.y();
      if (isFirst ||
          (wantHigh && y > yRBest) ||
          (!wantHigh && y < yRBest)) {

        // Best so far so save
        isFirst = false;
        posScreenBest = posScreenPrevious;
        yRBest = y;
      }
    }
  }

  return posScreenBest;
}

QPointF CentipedeSegmentAbstract::posScreenConstantYRHighXT (double radius) const
{
  return posScreenConstantYRForHighLowXT (radius,
                                         true);
}

QPointF CentipedeSegmentAbstract::posScreenConstantYRLowXT (double radius) const
{
  return posScreenConstantYRForHighLowXT (radius,
                                         false);
}

QPointF CentipedeSegmentAbstract::posScreenConstantYRForHighLowXT (double radius,
                                                                   bool wantHigh) const
{
  QPointF posScreenBest;
  double xTBest = 0;

  QPointF posCenterGraph;
  m_transformation.transformScreenToRawGraph (m_posCenterScreen,
                                              posCenterGraph);
  double yCenter = posCenterGraph.y();

  bool isFirst = true;
  for (int i = 0; i < NUM_CIRCLE_POINTS; i++) {
    QPointF posGraphPrevious, posGraphNext, posScreenPrevious;
    generatePreviousAndNextPoints (radius,
                                   i,
                                   posGraphPrevious,
                                   posGraphNext,
                                   posScreenPrevious);

    double yGraphPrevious = posGraphPrevious.y();
    double yGraphNext = posGraphNext.y();
    double epsilon = qAbs (yGraphPrevious - yGraphNext) / 10.0; // Allow for roundoff

    bool transitionUp = (yGraphPrevious - epsilon <= yCenter) && (yCenter < yGraphNext + epsilon);
    bool transitionDown = (yGraphNext - epsilon <= yCenter) && (yCenter < yGraphPrevious + epsilon);

    if (transitionDown || transitionUp) {

      // Transition occurred so save if best so far
      double x = posGraphPrevious.x();
      if (isFirst ||
          (wantHigh && x > xTBest) ||
          (!wantHigh && x < xTBest)) {

        // Best so far so save
        isFirst = false;
        posScreenBest = posScreenPrevious;
        xTBest = x;
      }
    }
  }

  return posScreenBest;
}

Transformation CentipedeSegmentAbstract::transformation () const
{
  return m_transformation;
}
