/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineProjectorHorizontal.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedHorizontalAbstract.h"
#include "Logger.h"
#include <QGraphicsScene>
#include "Transformation.h"

GuidelineStateDeployedHorizontalAbstract::GuidelineStateDeployedHorizontalAbstract (GuidelineStateContext &context) :
  GuidelineStateDeployedAbstract (context)
{
}

GuidelineStateDeployedHorizontalAbstract::~GuidelineStateDeployedHorizontalAbstract ()
{
}

QLineF GuidelineStateDeployedHorizontalAbstract::lineFromPoint (const QPointF &posScreen) const
{
  Transformation transformation = context().transformation();

  GuidelineProjectorHorizontal projector (transformation,
                                          posScreen,
                                          sceneRect ());
  QPointF posScreen1 = projector.pos1 ();
  QPointF posScreen2 = projector.pos2 ();

  return QLineF (posScreen1,
                 posScreen2);
}
