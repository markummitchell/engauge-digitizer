/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateVerticalRightHover.h"
#include "Logger.h"

GuidelineStateTemplateVerticalRightHover::GuidelineStateTemplateVerticalRightHover (GuidelineStateContext &context) :
  GuidelineStateTemplateVerticalRightAbstract (context)
{
}

GuidelineStateTemplateVerticalRightHover::~GuidelineStateTemplateVerticalRightHover ()
{
}

void GuidelineStateTemplateVerticalRightHover::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateVerticalRightHover::begin";

  GuidelineStateTemplateAbstract::beginCommon (templateHomeLine(sceneRect ()));

  context().guideline().setGraphicsItemVisible (true); // Undo setVisible(false) from Hide class

  GuidelineFormat guidelineFormat;
  context().guideline().setGraphicsItemPen (guidelineFormat.colorDeployedHover (),
                                            guidelineFormat.lineWidthHover ()); // Show
}

bool GuidelineStateTemplateVerticalRightHover::doPaint () const
{
  return true;
}

void GuidelineStateTemplateVerticalRightHover::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateVerticalRightHover::end";
}

void GuidelineStateTemplateVerticalRightHover::handleHoverEnterEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_LURKING
}

void GuidelineStateTemplateVerticalRightHover::handleHoverLeaveEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_LURKING);
}

void GuidelineStateTemplateVerticalRightHover::handleMousePress (const QPointF &posScene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateVerticalRightHover::handleMousePress";

  GuidelineState stateNew = context().cartesian() ?
    GUIDELINE_STATE_DEPLOYED_CONSTANT_X_HOVER :
    GUIDELINE_STATE_DEPLOYED_CONSTANT_T_HOVER;
    
  handleMousePressCommon (posScene,
                          stateNew,
                          GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_LURKING);
}

void GuidelineStateTemplateVerticalRightHover::handleShowHide (bool show)
{
  if (!show) {
    context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_HIDE);
  }
}

QString GuidelineStateTemplateVerticalRightHover::state () const
{
  return ("GuidelineStateTemplateVerticalRightHover");
}
