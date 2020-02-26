/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineLine.h"
#include "GuidelineProjectorConstantY.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantYAbstract.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateDeployedConstantYAbstract::GuidelineStateDeployedConstantYAbstract (GuidelineStateContext &context) :
  GuidelineStateDeployedAbstract (context)
{
}

GuidelineStateDeployedConstantYAbstract::~GuidelineStateDeployedConstantYAbstract ()
{
}

QPointF GuidelineStateDeployedConstantYAbstract::convertGraphCoordinateToScreenPoint (double valueGraph) const
{
  const double ARBITRARY_X = 1.0; // Value that is legal in all cases, including log scaling
  QPointF posScreen;
  context().transformation().transformRawGraphToScreen (QPointF (ARBITRARY_X,
                                                                 valueGraph),
                                                        posScreen);

  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateDeployedConstantYAbstract::convertGraphCoordinateToScreenPoint"
                               << " pos=(" << posScreen.x() << ", " << posScreen.y() << ")";

  return posScreen;
}

double GuidelineStateDeployedConstantYAbstract::convertScreenPointToGraphCoordinate (const QPointF &posScreen) const
{
  QPointF posGraph;
  context().transformation().transformScreenToRawGraph (posScreen,
                                                        posGraph);

  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateDeployedConstantYAbstract::convertScreenPointToGraphCoordinate"
                               << " pos=(" << posGraph.x() << ", " << posGraph.y() << ")";

  return posGraph.y();
}

EllipseParameters GuidelineStateDeployedConstantYAbstract::pointToEllipse (const QPointF & /* posScreen */) const
{
  // pointToLine applies in this state
  return EllipseParameters();
}

QLineF GuidelineStateDeployedConstantYAbstract::pointToLine (const QPointF &posScreen) const
{
  GuidelineProjectorConstantY projector;

  return projector.fromPosScreen (context().transformation(),
                                  sceneRect (),
                                  posScreen);
}

void GuidelineStateDeployedConstantYAbstract::updateWithLatestTransformation ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYAbstract::updateWithLatestTransformation";

  if (!context().transformation().transformIsDefined()) {
    // Discard this Guideline immediately if the transformation transitions to undefined
    context().requestStateTransition(GUIDELINE_STATE_DISCARDED);
  } else {

    GuidelineProjectorConstantY projector;

    GuidelineLine *line = dynamic_cast<GuidelineLine*> (&context().guideline());
    line->setLine (projector.fromCoordinateY (context().transformation(),
                                              sceneRect (),
                                              context().posCursorGraph ().y()));
  }
}
