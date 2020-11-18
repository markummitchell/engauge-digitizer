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

double CentipedeSegmentAbstract::closestAngleToCentralAngle (double angleCenter,
                                                             double angleOld) const
{
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

const DocumentModelGuideline &CentipedeSegmentAbstract::modelGuideline () const
{
  return m_modelGuideline;
}

QPointF CentipedeSegmentAbstract::posClickScreen () const
{
  return m_posClickScreen;
}

Transformation CentipedeSegmentAbstract::transformation() const
{
  return m_transformation;
}
