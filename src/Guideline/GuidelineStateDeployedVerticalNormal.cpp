/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "Guideline.h"
#include "GuidelineFormat.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedVerticalNormal.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateDeployedVerticalNormal::GuidelineStateDeployedVerticalNormal (GuidelineStateContext &context) :
  GuidelineStateDeployedVerticalAbstract (context)
{
}

GuidelineStateDeployedVerticalNormal::~GuidelineStateDeployedVerticalNormal ()
{
}

void GuidelineStateDeployedVerticalNormal::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedVerticalNormal::begin";

  context().guideline().setVisible (true); // Undo setVisible from GuidelineStateDeployedVerticalHide

  beginCommon (GuidelineFormat::HOVER_OFF);
}

bool GuidelineStateDeployedVerticalNormal::doPaint () const
{
  return true;
}

void GuidelineStateDeployedVerticalNormal::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedVerticalNormal::end";
}

void GuidelineStateDeployedVerticalNormal::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_VERTICAL_HOVER);
}

void GuidelineStateDeployedVerticalNormal::handleHoverLeaveEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_VERTICAL_HOVER
}

void GuidelineStateDeployedVerticalNormal::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_VERTICAL_NORMAL,
                          GUIDELINE_STATE_DISCARDED);
}

void GuidelineStateDeployedVerticalNormal::handleShowHide (bool show)
{
  if (!show) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_VERTICAL_HIDE);
  }
}

QString GuidelineStateDeployedVerticalNormal::state () const
{
  return ("GuidelineStateDeployedVerticalNormal");
}
