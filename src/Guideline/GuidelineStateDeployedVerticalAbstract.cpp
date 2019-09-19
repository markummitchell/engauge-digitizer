/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineProjectorVertical.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedVerticalAbstract.h"
#include "Logger.h"
#include <QGraphicsScene>
#include "Transformation.h"

GuidelineStateDeployedVerticalAbstract::GuidelineStateDeployedVerticalAbstract (GuidelineStateContext &context) :
  GuidelineStateDeployedAbstract (context)
{
}

GuidelineStateDeployedVerticalAbstract::~GuidelineStateDeployedVerticalAbstract ()
{
}

QLineF GuidelineStateDeployedVerticalAbstract::lineFromPoint (const QPointF &posScreen) const
{
  Transformation transformation = context().transformation();

  GuidelineProjectorVertical projector (transformation,
                                        posScreen,
                                        sceneRect ());
  QPointF posScreen1 = projector.pos1 ();
  QPointF posScreen2 = projector.pos2 ();

  return QLineF (posScreen1,
                 posScreen2);
}
