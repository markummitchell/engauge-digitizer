/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantYNormal.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateDeployedConstantYNormal::GuidelineStateDeployedConstantYNormal (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantYAbstract (context)
{
}

GuidelineStateDeployedConstantYNormal::~GuidelineStateDeployedConstantYNormal ()
{
}

void GuidelineStateDeployedConstantYNormal::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYNormal::begin";

  context().guideline().setGraphicsItemVisible (true); // Undo setVisible from GuidelineStateDeployedConstantYHide

  beginCommon (GuidelineFormat::HOVER_OFF);
}

bool GuidelineStateDeployedConstantYNormal::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantYNormal::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYNormal::end";
}

void GuidelineStateDeployedConstantYNormal::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_HOVER);
}

void GuidelineStateDeployedConstantYNormal::handleHoverLeaveEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_HOVER
}

void GuidelineStateDeployedConstantYNormal::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_NORMAL,
                          GUIDELINE_STATE_DISCARDED);
}

void GuidelineStateDeployedConstantYNormal::handleShowHide (bool show)
{
  if (!show) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_HIDE);
  }
}

QString GuidelineStateDeployedConstantYNormal::state () const
{
  return ("GuidelineStateDeployedConstantYNormal");
}
