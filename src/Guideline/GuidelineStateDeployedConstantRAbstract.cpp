/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineEllipse.h"
#include "GuidelineProjectorConstantR.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantRAbstract.h"
#include "Logger.h"
#include <qmath.h>
#include "Transformation.h"

GuidelineStateDeployedConstantRAbstract::GuidelineStateDeployedConstantRAbstract (GuidelineStateContext &context) :
  GuidelineStateDeployedAbstract (context)
{
}

GuidelineStateDeployedConstantRAbstract::~GuidelineStateDeployedConstantRAbstract ()
{
}

QPointF GuidelineStateDeployedConstantRAbstract::convertGraphCoordinateToScreenPoint (double valueGraph) const
{
  const double ARBITRARY_THETA = 0; // Value that is legal in all cases
  QPointF posScreen;
  context().transformation().transformRawGraphToScreen (QPointF (ARBITRARY_THETA,
                                                                 valueGraph),
                                                        posScreen);

  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateDeployedConstantRAbstract::convertGraphCoordinateToScreenPoint"
                               << " pos=(" << posScreen.x() << ", " << posScreen.y() << ")";

  return posScreen;
}

double GuidelineStateDeployedConstantRAbstract::convertScreenPointToGraphCoordinate (const QPointF &posScreen) const
{
  QPointF posGraph;
  context().transformation().transformScreenToRawGraph (posScreen,
                                                        posGraph);

  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateDeployedConstantRAbstract::convertScreenPointToGraphCoordinate"
                               << " pos=(" << posGraph.x() << ", " << posGraph.y() << ")";

  return posGraph.y();
}

EllipseParameters GuidelineStateDeployedConstantRAbstract::pointToEllipse (const QPointF &posScreen) const
{
  GuidelineProjectorConstantR projector;

  return projector.fromPosScreen (context().transformation(),
                                  sceneRect (),
                                  posScreen);
}

QLineF GuidelineStateDeployedConstantRAbstract::pointToLine (const QPointF & /* posScreen */) const
{
  // pointToEllipse applies in this state
  return QLineF (0, 0, 0, 0);
}

void GuidelineStateDeployedConstantRAbstract::updateWithLatestTransformation ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRAbstract::updateWithLatestTransformation";

  if (!context().transformation().transformIsDefined()) {
    // Discard this Guideline immediately if the transformation transitions to undefined
    context().requestStateTransition(GUIDELINE_STATE_DISCARDED);
  } else {

    QPointF posScreen;
    context().transformation().transformRawGraphToScreen (context().posCursorGraph(),
                                                          posScreen);

    GuidelineEllipse *ellipse = dynamic_cast<GuidelineEllipse*> (&context().guideline());
    ellipse->updateGeometry (posScreen);
  }
}
