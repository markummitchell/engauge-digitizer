/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineLine.h"
#include "GuidelineProjectorConstantT.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantTAbstract.h"
#include "Logger.h"
#include <QGraphicsScene>
#include <qmath.h>
#include "Transformation.h"

GuidelineStateDeployedConstantTAbstract::GuidelineStateDeployedConstantTAbstract (GuidelineStateContext &context) :
  GuidelineStateDeployedAbstract (context)
{
}

GuidelineStateDeployedConstantTAbstract::~GuidelineStateDeployedConstantTAbstract ()
{
}

EllipseParameters GuidelineStateDeployedConstantTAbstract::pointToEllipse (const QPointF & /* posScreen */) const
{
  return EllipseParameters();
}

QLineF GuidelineStateDeployedConstantTAbstract::pointToLine (const QPointF &posScreen) const
{
  GuidelineProjectorConstantT projector;

  return projector.fromPosScreen (context().transformation(),
                                  sceneRect (),
                                  posScreen);
}

void GuidelineStateDeployedConstantTAbstract::updateWithLatestTransformation ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTAbstract::updateWithLatestTransformation";

  GuidelineProjectorConstantT projector;

  double tGraph = qAtan2 (context().posCursorGraph().y (),
                          context().posCursorGraph().x ());

  GuidelineLine *line = dynamic_cast<GuidelineLine*> (&context().guideline());
  line->setLine (projector.fromCoordinateT (context().transformation(),
                                            sceneRect (),
                                            tGraph));
}
