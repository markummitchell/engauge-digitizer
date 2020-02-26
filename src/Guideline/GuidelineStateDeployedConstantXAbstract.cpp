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
#include "Transformation.h"

GuidelineStateDeployedConstantXAbstract::GuidelineStateDeployedConstantXAbstract (GuidelineStateContext &context) :
  GuidelineStateDeployedAbstract (context)
{
}

GuidelineStateDeployedConstantXAbstract::~GuidelineStateDeployedConstantXAbstract ()
{
}

QPointF GuidelineStateDeployedConstantXAbstract::convertGraphCoordinateToScreenPoint (double valueGraph) const
{
  const double ARBITRARY_Y = 1.0; // Value that is legal in all cases, including log scaling
  QPointF posScreen;
  context().transformation().transformRawGraphToScreen (QPointF (valueGraph,
                                                                 ARBITRARY_Y),
                                                        posScreen);

  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateDeployedConstantXAbstract::convertGraphCoordinateToScreenPoint"
                               << " pos=(" << posScreen.x() << ", " << posScreen.y() << ")";

  return posScreen;
}

double GuidelineStateDeployedConstantXAbstract::convertScreenPointToGraphCoordinate (const QPointF &posScreen) const
{
  QPointF posGraph;
  context().transformation().transformScreenToRawGraph (posScreen,
                                                        posGraph);

  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateDeployedConstantXAbstract::convertScreenPointToGraphCoordinate"
                               << " pos=(" << posGraph.x() << ", " << posGraph.y() << ")";

  return posGraph.x();
}

EllipseParameters GuidelineStateDeployedConstantXAbstract::pointToEllipse (const QPointF & /* posScreen */) const
{
  // pointToLine applies in this state
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

  if (!context().transformation().transformIsDefined()) {
    // Discard this Guideline immediately if the transformation transitions to undefined
    context().requestStateTransition(GUIDELINE_STATE_DISCARDED);
  } else {

    GuidelineProjectorConstantX projector;

    GuidelineLine *line = dynamic_cast<GuidelineLine*> (&context().guideline());
    line->setLine (projector.fromCoordinateX (context().transformation(),
                                              sceneRect (),
                                              context().posCursorGraph ().x()));
  }
}
