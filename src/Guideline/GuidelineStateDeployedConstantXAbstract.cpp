/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineProjectorConstantX.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantXAbstract.h"
#include "Logger.h"
#include <QGraphicsScene>
#include "Transformation.h"

GuidelineStateDeployedConstantXAbstract::GuidelineStateDeployedConstantXAbstract (GuidelineStateContext &context) :
  GuidelineStateDeployedAbstract (context)
{
}

GuidelineStateDeployedConstantXAbstract::~GuidelineStateDeployedConstantXAbstract ()
{
}

QRectF GuidelineStateDeployedConstantXAbstract::pointToEllipse (const QPointF & /* posScreen */) const
{
  return QRectF (0, 0, 0, 0);
}

QLineF GuidelineStateDeployedConstantXAbstract::pointToLine (const QPointF &posScreen) const
{
  GuidelineProjectorConstantX projector;

  return projector.fromPosScreen (context().transformation(),
                                  sceneRect (),
                                  posScreen);
}

void GuidelineStateDeployedConstantXAbstract::setPointGraph (const QPointF &posGraph)
{
  // First coordinate is what defines this Guideline
  setPointCoordinate (posGraph.x ());
}

void GuidelineStateDeployedConstantXAbstract::updateWithLatestTransformation ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXAbstract::updateWithLatestTransformation";
}
