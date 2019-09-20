/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantRHover.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateDeployedConstantRHover::GuidelineStateDeployedConstantRHover (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantRAbstract (context)
{
}

GuidelineStateDeployedConstantRHover::~GuidelineStateDeployedConstantRHover ()
{
}

void GuidelineStateDeployedConstantRHover::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRHover::begin";

  context().guideline().setGraphicsItemVisible (true); // Undo setVisible from GuidelineStateDeployedConstantRHide

  beginCommon (GuidelineFormat::HOVER_ON);
}

bool GuidelineStateDeployedConstantRHover::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantRHover::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRHover::end";
}

void GuidelineStateDeployedConstantRHover::handleHoverEnterEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_R_NORMAL
}

void GuidelineStateDeployedConstantRHover::handleHoverLeaveEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_NORMAL);
}

void GuidelineStateDeployedConstantRHover::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HOVER,
                          GUIDELINE_STATE_DISCARDED);
}

void GuidelineStateDeployedConstantRHover::handleShowHide (bool show)
{
  if (!show) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HIDE);
  }
}

QString GuidelineStateDeployedConstantRHover::state () const
{
  return ("GuidelineStateDeployedConstantRHover");
}
