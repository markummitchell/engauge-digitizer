/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedHorizontalHover.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateDeployedHorizontalHover::GuidelineStateDeployedHorizontalHover (GuidelineStateContext &context) :
  GuidelineStateDeployedHorizontalAbstract (context)
{
}

GuidelineStateDeployedHorizontalHover::~GuidelineStateDeployedHorizontalHover ()
{
}

void GuidelineStateDeployedHorizontalHover::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedHorizontalHover::begin";

  context().guideline().setVisible (true); // Undo setVisible from GuidelineStateDeployedHorizontalHide

  beginCommon (GuidelineFormat::HOVER_ON);
}

bool GuidelineStateDeployedHorizontalHover::doPaint () const
{
  return true;
}

void GuidelineStateDeployedHorizontalHover::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedHorizontalHover::end";
}

void GuidelineStateDeployedHorizontalHover::handleHoverEnterEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_HORIZONTAL_NORMAL
}

void GuidelineStateDeployedHorizontalHover::handleHoverLeaveEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_HORIZONTAL_NORMAL);
}

void GuidelineStateDeployedHorizontalHover::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_HORIZONTAL_HOVER,
                          GUIDELINE_STATE_NULL);
}

void GuidelineStateDeployedHorizontalHover::handleShowHide (bool show)
{
  if (!show) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_HORIZONTAL_HIDE);
  }
}

QString GuidelineStateDeployedHorizontalHover::state () const
{
  return ("GuidelineStateDeployedHorizontalHover");
}
