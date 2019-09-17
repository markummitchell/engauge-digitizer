/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Guideline.h"
#include "GuidelineFormat.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateHorizontalTopLurking.h"
#include "Logger.h"

GuidelineStateTemplateHorizontalTopLurking::GuidelineStateTemplateHorizontalTopLurking (GuidelineStateContext &context) :
  GuidelineStateTemplateHorizontalTopAbstract (context)
{
}

GuidelineStateTemplateHorizontalTopLurking::~GuidelineStateTemplateHorizontalTopLurking ()
{
}

void GuidelineStateTemplateHorizontalTopLurking::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateHorizontalTopLurking::begin";

  GuidelineStateTemplateAbstract::beginCommon (templateHomeLine(sceneRect ()));

  context().guideline().setVisible (true); // Undo setVisible(false) from Hide class

  GuidelineFormat guidelineFormat;
  context().guideline().setPenColor (guidelineFormat.colorHidden (),
                                     guidelineFormat.lineWidthHover ()); // Hide until hover entry
}

bool GuidelineStateTemplateHorizontalTopLurking::doPaint () const
{
  return true;
}

void GuidelineStateTemplateHorizontalTopLurking::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateHorizontalTopLurking::end";
}

void GuidelineStateTemplateHorizontalTopLurking::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_HOVER);
}

void GuidelineStateTemplateHorizontalTopLurking::handleHoverLeaveEvent ()
{
   // This event would have been handled by GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_HOVER
}

void GuidelineStateTemplateHorizontalTopLurking::handleMousePress (const QPointF &posScene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateHorizontalTopLurking::handleMousePress";

  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_HORIZONTAL_NORMAL,
                          GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_LURKING);
}

void GuidelineStateTemplateHorizontalTopLurking::handleShowHide (bool show)
{
  if (!show) {
    context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_HIDE);
  }
}

QString GuidelineStateTemplateHorizontalTopLurking::state () const
{
  return ("GuidelineStateTemplateHorizontalTopLurking");
}
