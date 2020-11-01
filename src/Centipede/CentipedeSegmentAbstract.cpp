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
                                                              QPointF &posScreenPrevious,
                                                              QPointF &posScreenNext) const
{
  double angleBefore = 2.0 * PI * (double) i / (double) NUM_CIRCLE_POINTS;
  double angleAfter = 2.0 * PI * (double) (i + 1) / (double) NUM_CIRCLE_POINTS;
  posScreenPrevious = m_posCenterScreen + QPointF (radius * cos (angleBefore),
                                                   radius * sin (angleBefore));
  posScreenNext = m_posCenterScreen + QPointF (radius * cos (angleAfter),
                                               radius * sin (angleAfter));

  m_transformation.transformScreenToRawGraph (posScreenPrevious,
                                              posGraphPrevious);
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
  return posScreenConstantXTForScaledYR (radius,
                                         1.0);
}

QPointF CentipedeSegmentAbstract::posScreenConstantXTLowYR (double radius) const
{
  return posScreenConstantXTForScaledYR (radius,
                                         -1.0);
}

QPointF CentipedeSegmentAbstract::posScreenConstantXTForScaledYR (double radius,
                                                                  double scale) const
{
  QPointF posScreenBest;
  double yTBest = 0;

  double xCenter = m_posCenterScreen.x();

  bool isFirst = true;
  for (int i = 0; i < NUM_CIRCLE_POINTS; i++) {
    QPointF posGraphPrevious, posScreenPrevious, posScreenNext;
    generatePreviousAndNextPoints (radius,
                                   i,
                                   posGraphPrevious,
                                   posScreenPrevious,
                                   posScreenNext);

    bool transitionUp = (posScreenPrevious.x() <= xCenter) && (xCenter < posScreenNext.x());
    bool transitionDown = (posScreenNext.x() <= xCenter) && (xCenter < posScreenPrevious.x());

    if (transitionDown || transitionUp) {
      // Transition occurred so save if best so far
      double y = scale * posGraphPrevious.y();
      if (isFirst || (y > yTBest)) {
        // Best so far so save
        isFirst = false;
        posScreenBest = posScreenNext;
        yTBest = y;
      }
    }
  }

  return posScreenBest;
}

QPointF CentipedeSegmentAbstract::posScreenConstantYRHighXT (double radius) const
{
  return posScreenConstantYRForScaledXT (radius,
                                         1.0);
}

QPointF CentipedeSegmentAbstract::posScreenConstantYRLowXT (double radius) const
{
  return posScreenConstantYRForScaledXT (radius,
                                         -1.0);
}

QPointF CentipedeSegmentAbstract::posScreenConstantYRForScaledXT (double radius,
                                                                  double scale) const
{
  QPointF posScreenBest;
  double xTBest = 0;

  double yCenter = m_posCenterScreen.y();

  bool isFirst = true;
  for (int i = 0; i < NUM_CIRCLE_POINTS; i++) {
    QPointF posGraphPrevious, posScreenPrevious, posScreenNext;
    generatePreviousAndNextPoints (radius,
                                   i,
                                   posGraphPrevious,
                                   posScreenPrevious,
                                   posScreenNext);

    bool transitionUp = (posScreenPrevious.y() <= yCenter) && (yCenter < posScreenNext.y());
    bool transitionDown = (posScreenNext.y() <= yCenter) && (yCenter < posScreenPrevious.y());

    if (transitionDown || transitionUp) {
      // Transition occurred so save if best so far
      double x = scale * posGraphPrevious.x();
      if (isFirst || (x > xTBest)) {
        // Best so far so save
        isFirst = false;
        posScreenBest = posScreenNext;
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
