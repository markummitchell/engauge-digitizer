/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantYHover.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateDeployedConstantYHover::GuidelineStateDeployedConstantYHover (GuidelineStateContext &context) :
  GuidelineStateDeployedConstantYAbstract (context)
{
}

GuidelineStateDeployedConstantYHover::~GuidelineStateDeployedConstantYHover ()
{
}

void GuidelineStateDeployedConstantYHover::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYHover::begin";

  context().guideline().setGraphicsItemVisible (true); // Undo setVisible from GuidelineStateDeployedConstantYHide

  beginCommon (GuidelineFormat::HOVER_ON);
}

bool GuidelineStateDeployedConstantYHover::doPaint () const
{
  return true;
}

void GuidelineStateDeployedConstantYHover::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateDeployedConstantYHover::end";
}

void GuidelineStateDeployedConstantYHover::handleHoverEnterEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_NORMAL
}

void GuidelineStateDeployedConstantYHover::handleHoverLeaveEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_NORMAL);
}

void GuidelineStateDeployedConstantYHover::handleMousePress (const QPointF &posScene)
{
  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_HOVER,
                          GUIDELINE_STATE_DISCARDED);
}

void GuidelineStateDeployedConstantYHover::handleShowHide (bool show)
{
  if (!show) {
    context().requestStateTransition(GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_HIDE);
  }
}

QString GuidelineStateDeployedConstantYHover::state () const
{
  return ("GuidelineStateDeployedConstantYHover");
}
