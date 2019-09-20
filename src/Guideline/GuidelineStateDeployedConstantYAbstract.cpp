/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineProjectorConstantY.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantYAbstract.h"
#include "Logger.h"
#include <QGraphicsScene>
#include "Transformation.h"

GuidelineStateDeployedConstantYAbstract::GuidelineStateDeployedConstantYAbstract (GuidelineStateContext &context) :
  GuidelineStateDeployedAbstract (context)
{
}

GuidelineStateDeployedConstantYAbstract::~GuidelineStateDeployedConstantYAbstract ()
{
}

QLineF GuidelineStateDeployedConstantYAbstract::lineFromPoint (const QPointF &posScreen) const
{
  Transformation transformation = context().transformation();

  GuidelineProjectorConstantY projector (transformation,
                                         posScreen,
                                         sceneRect ());
  QPointF posScreen1 = projector.pos1 ();
  QPointF posScreen2 = projector.pos2 ();

  return QLineF (posScreen1,
                 posScreen2);
}
