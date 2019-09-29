/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantTHide.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateDeployedConstantTHide::GuidelineStateDeployedConstantTHide (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantTAbstract (context)
{
}

GuidelineStateDeployedConstantTHide::~GuidelineStateDeployedConstantTHide ()
{
}

void GuidelineStateDeployedConstantTHide::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTHide::begin";

  beginCommon (GuidelineFormat::HOVER_OFF);

  context().guideline().setGraphicsItemVisible (false); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedConstantTHide::doPaint () const
{
  return false;
}

void GuidelineStateDeployedConstantTHide::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTHide::end";
}

void GuidelineStateDeployedConstantTHide::handleHoverEnterEvent ()
{
  // Noop
}

void GuidelineStateDeployedConstantTHide::handleHoverLeaveEvent ()
{
  // Noop
}

void GuidelineStateDeployedConstantTHide::handleMousePress (const QPointF & /* posScene */)
{
}

void GuidelineStateDeployedConstantTHide::handleShowHide (bool show)
{
  if (show) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE);
  }
}

QString GuidelineStateDeployedConstantTHide::state () const
{
  return ("GuidelineStateDeployedConstantTHide");
}
