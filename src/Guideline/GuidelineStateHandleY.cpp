/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GraphicsScene.h"
#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineProjectorConstantY.h"
#include "GuidelineState.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateHandleY.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateHandleY::GuidelineStateHandleY (GuidelineStateContext &context) :
  GuidelineStateHandleAbstract (context)
{
}

GuidelineStateHandleY::~GuidelineStateHandleY ()
{
}

void GuidelineStateHandleY::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateHandleY::begin"
                              << " identifier=" << context().guideline().identifier().toLatin1().data();

  beginCommon ();
}

QPointF GuidelineStateHandleY::convertGraphCoordinateToScreenPoint (double valueGraph) const
{
  const double ARBITRARY_X = 1; // Value that is legal in all cases including log
  QPointF posScreen;
  context().transformation().transformRawGraphToScreen (QPointF (ARBITRARY_X,
                                                                 valueGraph),
                                                        posScreen);

  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandleY::convertGraphCoordinateToScreenPoint"
                               << " pos=(" << posScreen.x() << ", " << posScreen.y() << ")";

  return posScreen;
}

double GuidelineStateHandleY::convertScreenPointToGraphCoordinate(const QPointF &posScreen) const
{
  QPointF posGraph;
  context().transformation().transformScreenToRawGraph (posScreen,
                                                        posGraph);

  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandleY::convertScreenPointToGraphCoordinate"
                               << " pos=(" << posGraph.x() << ", " << posGraph.y() << ")";

  return posGraph.y();
}

void GuidelineStateHandleY::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateHandleY::end";
}

void GuidelineStateHandleY::handleMouseRelease (const QPointF &posScene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateHandleY::handleMouseRelease";

  context().guideline().sacrificeHandleAndVisibleGuidelines(posScene,
                                                            GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE);
  context().requestStateTransition (GUIDELINE_STATE_DISCARDED);
}

EllipseParameters GuidelineStateHandleY::pointToEllipse (const QPointF & /* posScreen */) const
{
  // pointToLine applies in this state
  return EllipseParameters();
}

QLineF GuidelineStateHandleY::pointToLine (const QPointF &posScreen) const
{
  GuidelineProjectorConstantY projector;

  return projector.fromPosScreen (context().transformation(),
                                  sceneRect (),
                                  posScreen);
}

QString GuidelineStateHandleY::stateName () const
{
  return guidelineStateAsString (GUIDELINE_STATE_HANDLE_Y);
}
