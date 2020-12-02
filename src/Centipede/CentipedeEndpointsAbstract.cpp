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
