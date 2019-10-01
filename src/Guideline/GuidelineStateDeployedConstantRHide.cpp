/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantRHide.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateDeployedConstantRHide::GuidelineStateDeployedConstantRHide (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantRAbstract (context)
{
}

GuidelineStateDeployedConstantRHide::~GuidelineStateDeployedConstantRHide ()
{
}

void GuidelineStateDeployedConstantRHide::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRHide::begin";

  beginCommon (GuidelineFormat::HOVER_OFF);

  context().guideline().setGraphicsItemVisible (false); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedConstantRHide::doPaint () const
{
  return false;
}

void GuidelineStateDeployedConstantRHide::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRHide::end";
}

void GuidelineStateDeployedConstantRHide::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantRHide::handleHoverEnterEvent ()
{
  // Noop
}

void GuidelineStateDeployedConstantRHide::handleHoverLeaveEvent ()
{
  // Noop
}

void GuidelineStateDeployedConstantRHide::handleMousePress (const QPointF & /* posScene */)
{
}

void GuidelineStateDeployedConstantRHide::handleVisibleChange (bool visible)
{
  if (visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE);
  }
}

QString GuidelineStateDeployedConstantRHide::state () const
{
  return ("GuidelineStateDeployedConstantRHide");
}
