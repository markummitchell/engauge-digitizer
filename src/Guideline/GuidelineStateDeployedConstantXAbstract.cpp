/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineLine.h"
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

EllipseParameters GuidelineStateDeployedConstantXAbstract::pointToEllipse (const QPointF & /* posScreen */) const
{
  return EllipseParameters();
}

QLineF GuidelineStateDeployedConstantXAbstract::pointToLine (const QPointF &posScreen) const
{
  GuidelineProjectorConstantX projector;

  return projector.fromPosScreen (context().transformation(),
                                  sceneRect (),
                                  posScreen);
}
void GuidelineStateDeployedConstantXAbstract::updateWithLatestTransformation ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXAbstract::updateWithLatestTransformation";

  GuidelineProjectorConstantX projector;

  GuidelineLine *line = dynamic_cast<GuidelineLine*> (&context().guideline());
  line->setLine (projector.fromCoordinateX (context().transformation(),
                                            sceneRect (),
                                            context().posCursorGraph ().x()));
}
