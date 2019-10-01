/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantTLocked.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateDeployedConstantTLocked::GuidelineStateDeployedConstantTLocked (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantTAbstract (context)
{
}

GuidelineStateDeployedConstantTLocked::~GuidelineStateDeployedConstantTLocked ()
{
}

void GuidelineStateDeployedConstantTLocked::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTLocked::begin";

  context().guideline().setGraphicsItemVisible (true); // Undo setVisible from GuidelineStateDeployedConstantTHide

  beginCommon (GuidelineFormat::HOVER_ON);
}

bool GuidelineStateDeployedConstantTLocked::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantTLocked::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTLocked::end";
}

void GuidelineStateDeployedConstantTLocked::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantTLocked::handleHoverEnterEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE
}

void GuidelineStateDeployedConstantTLocked::handleHoverLeaveEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE);
}

void GuidelineStateDeployedConstantTLocked::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_T_LOCKED,
                          GUIDELINE_STATE_DISCARDED);
}

void GuidelineStateDeployedConstantTLocked::handleVisibleChange (bool visible)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_HIDE);
  }
}

QString GuidelineStateDeployedConstantTLocked::state () const
{
  return ("GuidelineStateDeployedConstantTLocked");
}
