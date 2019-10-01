/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateVerticalLeftLurking.h"
#include "Logger.h"

GuidelineStateTemplateVerticalLeftLurking::GuidelineStateTemplateVerticalLeftLurking (GuidelineStateContext &context) :
  GuidelineStateTemplateVerticalLeftAbstract (context)
{
}

GuidelineStateTemplateVerticalLeftLurking::~GuidelineStateTemplateVerticalLeftLurking ()
{
}

void GuidelineStateTemplateVerticalLeftLurking::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateVerticalLeftLurking::begin";

  GuidelineStateTemplateAbstract::beginCommon (templateHomeLine(sceneRect ()));

  context().guideline().setGraphicsItemVisible (true); // Undo setVisible(false) from Hide class

  GuidelineFormat guidelineFormat (context().color());

  context().guideline().setGraphicsItemPen (guidelineFormat.colorHidden (),
                                            guidelineFormat.lineWidthHover ()); // Hide until hover entry
}

bool GuidelineStateTemplateVerticalLeftLurking::doPaint () const
{
  return true;
}

void GuidelineStateTemplateVerticalLeftLurking::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateVerticalLeftLurking::end";
}

void GuidelineStateTemplateVerticalLeftLurking::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_HOVER);
}

void GuidelineStateTemplateVerticalLeftLurking::handleHoverLeaveEvent ()
{
   // This event would have been handled by GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_HOVER
}

void GuidelineStateTemplateVerticalLeftLurking::handleMousePress (const QPointF &posScene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateVerticalLeftLurking::handleMousePress";

  GuidelineState stateNew = context().cartesian() ?
    GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE :
    GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE;
  
  handleMousePressCommon (posScene,
                          stateNew,
                          GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_LURKING);
}

void GuidelineStateTemplateVerticalLeftLurking::handleVisibleChange (bool visible)
{
  if (!visible) {
    context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_HIDE);
  }
}

QString GuidelineStateTemplateVerticalLeftLurking::state () const
{
  return ("GuidelineStateTemplateVerticalLeftLurking");
}
