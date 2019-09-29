/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateVerticalRightLurking.h"
#include "Logger.h"

GuidelineStateTemplateVerticalRightLurking::GuidelineStateTemplateVerticalRightLurking (GuidelineStateContext &context) :
  GuidelineStateTemplateVerticalRightAbstract (context)
{
}

GuidelineStateTemplateVerticalRightLurking::~GuidelineStateTemplateVerticalRightLurking ()
{
}

void GuidelineStateTemplateVerticalRightLurking::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateVerticalRightLurking::begin";

  GuidelineStateTemplateAbstract::beginCommon (templateHomeLine(sceneRect ()));

  context().guideline().setGraphicsItemVisible (true); // Undo setVisible(false) from Hide class

  GuidelineFormat guidelineFormat (context().color ());

  context().guideline().setGraphicsItemPen (guidelineFormat.colorHidden (),
                                            guidelineFormat.lineWidthHover ()); // Hide until hover entry
}

bool GuidelineStateTemplateVerticalRightLurking::doPaint () const
{
  return true;
}

void GuidelineStateTemplateVerticalRightLurking::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateVerticalRightLurking::end";
}

void GuidelineStateTemplateVerticalRightLurking::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_HOVER);
}

void GuidelineStateTemplateVerticalRightLurking::handleHoverLeaveEvent ()
{
   // This event would have been handled by GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_HOVER
}

void GuidelineStateTemplateVerticalRightLurking::handleMousePress (const QPointF &posScene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateVerticalRightLurking::handleMousePress";

  GuidelineState stateNew = context().cartesian() ?
    GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE :
    GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE;
  
  handleMousePressCommon (posScene,
                          stateNew,
                          GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_LURKING);
}

void GuidelineStateTemplateVerticalRightLurking::handleShowHide (bool show)
{
  if (!show) {
    context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_HIDE);
  }
}

QString GuidelineStateTemplateVerticalRightLurking::state () const
{
  return ("GuidelineStateTemplateVerticalRightLurking");
}
