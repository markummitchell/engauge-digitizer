/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantTNormal.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateDeployedConstantTNormal::GuidelineStateDeployedConstantTNormal (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantTAbstract (context)
{
}

GuidelineStateDeployedConstantTNormal::~GuidelineStateDeployedConstantTNormal ()
{
}

void GuidelineStateDeployedConstantTNormal::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTNormal::begin";

  context().guideline().setGraphicsItemVisible (true); // Undo setVisible from GuidelineStateDeployedConstantTHide

  beginCommon (GuidelineFormat::HOVER_OFF);
}

bool GuidelineStateDeployedConstantTNormal::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantTNormal::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantTNormal::end";
}

void GuidelineStateDeployedConstantTNormal::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_HOVER);
}

void GuidelineStateDeployedConstantTNormal::handleHoverLeaveEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_T_HOVER
}

void GuidelineStateDeployedConstantTNormal::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_T_NORMAL,
                          GUIDELINE_STATE_DISCARDED);
}

void GuidelineStateDeployedConstantTNormal::handleShowHide (bool show)
{
  if (!show) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_T_HIDE);
  }
}

QString GuidelineStateDeployedConstantTNormal::state () const
{
  return ("GuidelineStateDeployedConstantTNormal");
}
