/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineProjectorConstantT.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantTAbstract.h"
#include "Logger.h"
#include <QGraphicsScene>
#include "Transformation.h"

GuidelineStateDeployedConstantTAbstract::GuidelineStateDeployedConstantTAbstract (GuidelineStateContext &context) :
  GuidelineStateDeployedAbstract (context)
{
}

GuidelineStateDeployedConstantTAbstract::~GuidelineStateDeployedConstantTAbstract ()
{
}

QRectF GuidelineStateDeployedConstantTAbstract::pointToEllipse (const QPointF & /* posScreen */) const
{
  return QRectF (0, 0, 0, 0);
}

QLineF GuidelineStateDeployedConstantTAbstract::pointToLine (const QPointF &posScreen) const
{
  GuidelineProjectorConstantT projector;

  return projector.fromPosScreen (context().transformation(),
                                  sceneRect (),
                                  posScreen);
}

void GuidelineStateDeployedConstantTAbstract::setPointGraph (const QPointF &posGraph)
{
  // First coordinate is what defines this Guideline
  setPointCoordinate (posGraph.x ());
}

void GuidelineStateDeployedConstantTAbstract::updateWithLatestTransformation ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTAbstract::updateWithLatestTransformation";
}
