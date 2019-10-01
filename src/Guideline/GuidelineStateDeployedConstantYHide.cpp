/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantYHide.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateDeployedConstantYHide::GuidelineStateDeployedConstantYHide (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantYAbstract (context)
{
}

GuidelineStateDeployedConstantYHide::~GuidelineStateDeployedConstantYHide ()
{
}

void GuidelineStateDeployedConstantYHide::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYHide::begin";

  beginCommon (GuidelineFormat::HOVER_OFF);

  context().guideline().setGraphicsItemVisible (false); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateDeployedConstantYHide::doPaint () const
{
  return false;
}

void GuidelineStateDeployedConstantYHide::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYHide::end";
}

void GuidelineStateDeployedConstantYHide::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantYHide::handleHoverEnterEvent ()
{
  // Noop
}

void GuidelineStateDeployedConstantYHide::handleHoverLeaveEvent ()
{
  // Noop
}

void GuidelineStateDeployedConstantYHide::handleMousePress (const QPointF & /* posScene */)
{
}

void GuidelineStateDeployedConstantYHide::handleVisibleChange (bool visible)
{
  if (visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE);
  }
}

QString GuidelineStateDeployedConstantYHide::state () const
{
  return ("GuidelineStateDeployedConstantYHide");
}
