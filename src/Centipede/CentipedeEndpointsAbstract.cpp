/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CentipedeEndpointsAbstract.h"
#include "mmsubs.h"
#include <qdebug.h>
#include <qmath.h>
#include <QPointF>
#include "Transformation.h"

const int NUM_CIRCLE_POINTS = 400; // Use many points so complicated (linear, log, high dynamic range) interpolation is not needed

CentipedeEndpointsAbstract::CentipedeEndpointsAbstract(const DocumentModelGuideline &modelGuideline,
                                                       const Transformation &transformation,
                                                       const QPointF &posClickScreen) :
  m_modelGuideline (modelGuideline),
  m_transformation (transformation),
  m_posClickScreen (posClickScreen)
{
}

CentipedeEndpointsAbstract::~CentipedeEndpointsAbstract ()
{
}

void CentipedeEndpointsAbstract::generatePreviousAndNextPoints (double radiusAboutClick,
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

const DocumentModelGuideline &CentipedeEndpointsAbstract::modelGuideline () const
{
  return m_modelGuideline;
}

QPointF CentipedeEndpointsAbstract::posClickScreen () const
{
  return m_posClickScreen;
}

const Transformation &CentipedeEndpointsAbstract::transformation () const
{
  return m_transformation;
}
