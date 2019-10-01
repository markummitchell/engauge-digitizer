/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantXHover.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateDeployedConstantXHover::GuidelineStateDeployedConstantXHover (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantXAbstract (context)
{
}

GuidelineStateDeployedConstantXHover::~GuidelineStateDeployedConstantXHover ()
{
}

void GuidelineStateDeployedConstantXHover::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXHover::begin";

  context().guideline().setGraphicsItemVisible (true); // Undo setVisible from GuidelineStateDeployedConstantXHide

  beginCommon (GuidelineFormat::HOVER_ON);
}

bool GuidelineStateDeployedConstantXHover::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantXHover::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantXHover::end";
}

void GuidelineStateDeployedConstantXHover::handleActiveChange (bool /* active */)
{
}

void GuidelineStateDeployedConstantXHover::handleHoverEnterEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE
}

void GuidelineStateDeployedConstantXHover::handleHoverLeaveEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE);
}

void GuidelineStateDeployedConstantXHover::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_X_HOVER,
                          GUIDELINE_STATE_DISCARDED);
}

void GuidelineStateDeployedConstantXHover::handleVisibleChange (bool visible)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_X_HIDE);
  }
}

QString GuidelineStateDeployedConstantXHover::state () const
{
  return ("GuidelineStateDeployedConstantXHover");
}
