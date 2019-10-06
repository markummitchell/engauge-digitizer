/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantRLocked.h"
#include "Logger.h"
#include <QGraphicsScene>
#include "Transformation.h"

GuidelineStateDeployedConstantRLocked::GuidelineStateDeployedConstantRLocked (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantRAbstract (context)
{
}

GuidelineStateDeployedConstantRLocked::~GuidelineStateDeployedConstantRLocked ()
{
}

void GuidelineStateDeployedConstantRLocked::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRLocked::begin";

  context().guideline().setGraphicsItemVisible (true); // Undo setVisible from GuidelineStateDeployedConstantRHide

  beginCommon (GuidelineFormat::HOVER_ON);
}

bool GuidelineStateDeployedConstantRLocked::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantRLocked::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRLocked::end";
}

void GuidelineStateDeployedConstantRLocked::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantRLocked::handleHoverEnterEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE
}

void GuidelineStateDeployedConstantRLocked::handleHoverLeaveEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE);
}

void GuidelineStateDeployedConstantRLocked::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_R_LOCKED,
                          GUIDELINE_STATE_DISCARDED);
}

void GuidelineStateDeployedConstantRLocked::handleVisibleChange (bool visible)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HIDE);
  }
}

QString GuidelineStateDeployedConstantRLocked::state () const
{
  return ("GuidelineStateDeployedConstantRLocked");
}
