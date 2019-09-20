/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantRNormal.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateDeployedConstantRNormal::GuidelineStateDeployedConstantRNormal (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantRAbstract (context)
{
}

GuidelineStateDeployedConstantRNormal::~GuidelineStateDeployedConstantRNormal ()
{
}

void GuidelineStateDeployedConstantRNormal::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRNormal::begin";

  context().guideline().setGraphicsItemVisible (true); // Undo setVisible from GuidelineStateDeployedConstantRHide

  beginCommon (GuidelineFormat::HOVER_OFF);
}

bool GuidelineStateDeployedConstantRNormal::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantRNormal::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantRNormal::end";
}

void GuidelineStateDeployedConstantRNormal::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HOVER);
}

void GuidelineStateDeployedConstantRNormal::handleHoverLeaveEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HOVER
}

void GuidelineStateDeployedConstantRNormal::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_R_NORMAL,
                          GUIDELINE_STATE_DISCARDED);
}

void GuidelineStateDeployedConstantRNormal::handleShowHide (bool show)
{
  if (!show) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HIDE);
  }
}

QString GuidelineStateDeployedConstantRNormal::state () const
{
  return ("GuidelineStateDeployedConstantRNormal");
}
