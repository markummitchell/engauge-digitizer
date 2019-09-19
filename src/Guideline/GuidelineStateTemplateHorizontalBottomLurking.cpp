/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateHorizontalBottomLurking.h"
#include "Logger.h"
#include <QObject>

GuidelineStateTemplateHorizontalBottomLurking::GuidelineStateTemplateHorizontalBottomLurking (GuidelineStateContext &context) :
  GuidelineStateTemplateHorizontalBottomAbstract (context)
{
}

GuidelineStateTemplateHorizontalBottomLurking::~GuidelineStateTemplateHorizontalBottomLurking ()
{
}

void GuidelineStateTemplateHorizontalBottomLurking::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateHorizontalBottomLurking::begin";

  GuidelineStateTemplateAbstract::beginCommon (templateHomeLine(sceneRect ()));

  context().guideline().setGraphicsItemVisible (true); // Undo setVisible(false) from Hide class

  GuidelineFormat guidelineFormat;
  context().guideline().setGraphicsItemPen (guidelineFormat.colorHidden (),
                                            guidelineFormat.lineWidthHover ()); // Hide until hover entry
}

bool GuidelineStateTemplateHorizontalBottomLurking::doPaint () const
{
  return true;
}

void GuidelineStateTemplateHorizontalBottomLurking::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateHorizontalBottomLurking::end";
}

void GuidelineStateTemplateHorizontalBottomLurking::handleHoverEnterEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_HOVER);
}

void GuidelineStateTemplateHorizontalBottomLurking::handleHoverLeaveEvent ()
{
   // This event would have been handled by GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_HOVER
}

void GuidelineStateTemplateHorizontalBottomLurking::handleMousePress (const QPointF &posScene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateHorizontalBottomLurking::handleMousePress";

  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_HORIZONTAL_NORMAL,
                          GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_LURKING);
}

void GuidelineStateTemplateHorizontalBottomLurking::handleShowHide (bool show)
{
  if (!show) {
    context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_HIDE);
  }
}

QString GuidelineStateTemplateHorizontalBottomLurking::state () const
{
  return ("GuidelineStateTemplateHorizontalBottomLurking");
}

