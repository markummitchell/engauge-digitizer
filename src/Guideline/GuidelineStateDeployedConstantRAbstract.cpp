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
#include <QGraphicsScene>
#include <qmath.h>
#include "Transformation.h"

GuidelineStateDeployedConstantRAbstract::GuidelineStateDeployedConstantRAbstract (GuidelineStateContext &context) :
  GuidelineStateDeployedAbstract (context)
{
}

GuidelineStateDeployedConstantRAbstract::~GuidelineStateDeployedConstantRAbstract ()
{
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
