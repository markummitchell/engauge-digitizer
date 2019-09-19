/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateHorizontalTopHover.h"
#include "Logger.h"

GuidelineStateTemplateHorizontalTopHover::GuidelineStateTemplateHorizontalTopHover (GuidelineStateContext &context) :
  GuidelineStateTemplateHorizontalTopAbstract (context)
{
}

GuidelineStateTemplateHorizontalTopHover::~GuidelineStateTemplateHorizontalTopHover ()
{
}

void GuidelineStateTemplateHorizontalTopHover::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateHorizontalTopHover::begin";

  GuidelineStateTemplateAbstract::beginCommon (templateHomeLine(sceneRect ()));

  context().guideline().setGraphicsItemVisible (true); // Undo setVisible(false) from Hide class

  GuidelineFormat guidelineFormat;
  context().guideline().setGraphicsItemPen (guidelineFormat.colorDeployedHover (),
                                            guidelineFormat.lineWidthHover ()); // Show
}

bool GuidelineStateTemplateHorizontalTopHover::doPaint () const
{
  return true;
}

void GuidelineStateTemplateHorizontalTopHover::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateHorizontalTopHover::end";
}

void GuidelineStateTemplateHorizontalTopHover::handleHoverEnterEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_LURKING
}

void GuidelineStateTemplateHorizontalTopHover::handleHoverLeaveEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_LURKING);
}

void GuidelineStateTemplateHorizontalTopHover::handleMousePress (const QPointF &posScene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateHorizontalTopHover::handleMousePress";

  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_HORIZONTAL_HOVER,
                          GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_LURKING);
}

void GuidelineStateTemplateHorizontalTopHover::handleShowHide (bool show)
{
  if (!show) {
    context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_HIDE);
  }
}

QString GuidelineStateTemplateHorizontalTopHover::state () const
{
  return ("GuidelineStateTemplateHorizontalTopHover");
}
