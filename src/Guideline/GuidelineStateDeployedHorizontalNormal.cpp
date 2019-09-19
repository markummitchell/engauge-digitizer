/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedHorizontalNormal.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateDeployedHorizontalNormal::GuidelineStateDeployedHorizontalNormal (GuidelineStateContext &context) :
  GuidelineStateDeployedHorizontalAbstract (context)
{
}

GuidelineStateDeployedHorizontalNormal::~GuidelineStateDeployedHorizontalNormal ()
{
}

void GuidelineStateDeployedHorizontalNormal::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedHorizontalNormal::begin";

  context().guideline().setGraphicsItemVisible (true); // Undo setVisible from GuidelineStateDeployedHorizontalHide

  beginCommon (GuidelineFormat::HOVER_OFF);
}

bool GuidelineStateDeployedHorizontalNormal::doPaint () const
{
  return true;
}

void GuidelineStateDeployedHorizontalNormal::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedHorizontalNormal::end";
}

void GuidelineStateDeployedHorizontalNormal::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_HORIZONTAL_HOVER);
}

void GuidelineStateDeployedHorizontalNormal::handleHoverLeaveEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_HORIZONTAL_HOVER
}

void GuidelineStateDeployedHorizontalNormal::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_HORIZONTAL_NORMAL,
                          GUIDELINE_STATE_DISCARDED);
}

void GuidelineStateDeployedHorizontalNormal::handleShowHide (bool show)
{
  if (!show) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_HORIZONTAL_HIDE);
  }
}

QString GuidelineStateDeployedHorizontalNormal::state () const
{
  return ("GuidelineStateDeployedHorizontalNormal");
}
