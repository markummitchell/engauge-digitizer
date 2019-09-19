/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedVerticalHover.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateDeployedVerticalHover::GuidelineStateDeployedVerticalHover (GuidelineStateContext &context) :
  GuidelineStateDeployedVerticalAbstract (context)
{
}

GuidelineStateDeployedVerticalHover::~GuidelineStateDeployedVerticalHover ()
{
}

void GuidelineStateDeployedVerticalHover::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedVerticalHover::begin";

  context().guideline().setGraphicsItemVisible (true); // Undo setVisible from GuidelineStateDeployedVerticalHide

  beginCommon (GuidelineFormat::HOVER_ON);
}

bool GuidelineStateDeployedVerticalHover::doPaint () const
{
  return true;
}

void GuidelineStateDeployedVerticalHover::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedVerticalHover::end";
}

void GuidelineStateDeployedVerticalHover::handleHoverEnterEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_VERTICAL_NORMAL
}

void GuidelineStateDeployedVerticalHover::handleHoverLeaveEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_VERTICAL_NORMAL);
}

void GuidelineStateDeployedVerticalHover::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_VERTICAL_HOVER,
                          GUIDELINE_STATE_DISCARDED);
}

void GuidelineStateDeployedVerticalHover::handleShowHide (bool show)
{
  if (!show) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_VERTICAL_HIDE);
  }
}

QString GuidelineStateDeployedVerticalHover::state () const
{
  return ("GuidelineStateDeployedVerticalHover");
}
