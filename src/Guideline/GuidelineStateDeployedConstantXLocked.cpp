/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantXLocked.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateDeployedConstantXLocked::GuidelineStateDeployedConstantXLocked (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantXAbstract (context)
{
}

GuidelineStateDeployedConstantXLocked::~GuidelineStateDeployedConstantXLocked ()
{
}

void GuidelineStateDeployedConstantXLocked::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXLocked::begin";

  context().guideline().setGraphicsItemVisible (true); // Undo setVisible from GuidelineStateDeployedConstantXHide

  beginCommon (GuidelineFormat::HOVER_ON);
}

bool GuidelineStateDeployedConstantXLocked::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantXLocked::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXLocked::end";
}

void GuidelineStateDeployedConstantXLocked::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantXLocked::handleHoverEnterEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE
}

void GuidelineStateDeployedConstantXLocked::handleHoverLeaveEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE);
}

void GuidelineStateDeployedConstantXLocked::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_X_LOCKED,
                          GUIDELINE_STATE_DISCARDED);
}

void GuidelineStateDeployedConstantXLocked::handleVisibleChange (bool visible)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_HIDE);
  }
}

QString GuidelineStateDeployedConstantXLocked::state () const
{
  return ("GuidelineStateDeployedConstantXLocked");
}
