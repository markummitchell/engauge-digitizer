/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateVerticalLeftHover.h"
#include "Logger.h"

GuidelineStateTemplateVerticalLeftHover::GuidelineStateTemplateVerticalLeftHover (GuidelineStateContext &context) :
  GuidelineStateTemplateVerticalLeftAbstract (context)
{
}

GuidelineStateTemplateVerticalLeftHover::~GuidelineStateTemplateVerticalLeftHover ()
{
}

void GuidelineStateTemplateVerticalLeftHover::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateVerticalLeftHover::begin";

  GuidelineStateTemplateAbstract::beginCommon (templateHomeLine(sceneRect ()));

  context().guideline().setGraphicsItemVisible (true); // Undo setVisible(false) from Hide class

  GuidelineFormat guidelineFormat;
  context().guideline().setGraphicsItemPen (guidelineFormat.colorDeployedHover (),
                                            guidelineFormat.lineWidthHover ()); // Show
}

bool GuidelineStateTemplateVerticalLeftHover::doPaint () const
{
  return true;
}

void GuidelineStateTemplateVerticalLeftHover::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateVerticalLeftHover::end";
}

void GuidelineStateTemplateVerticalLeftHover::handleHoverEnterEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_LURKING
}

void GuidelineStateTemplateVerticalLeftHover::handleHoverLeaveEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_LURKING);
}

void GuidelineStateTemplateVerticalLeftHover::handleMousePress (const QPointF &posScene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateVerticalLeftHover::handleMousePress";

  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_VERTICAL_HOVER,
                          GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_LURKING);
}

void GuidelineStateTemplateVerticalLeftHover::handleShowHide (bool show)
{
  if (!show) {
    context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_HIDE);
  }
}

QString GuidelineStateTemplateVerticalLeftHover::state () const
{
  return ("GuidelineStateTemplateVerticalLeftHover");
}
