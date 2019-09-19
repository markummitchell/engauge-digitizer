/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateHorizontalBottomHover.h"
#include "Logger.h"
#include <QObject>

GuidelineStateTemplateHorizontalBottomHover::GuidelineStateTemplateHorizontalBottomHover (GuidelineStateContext &context) :
  GuidelineStateTemplateHorizontalBottomAbstract (context)
{
}

GuidelineStateTemplateHorizontalBottomHover::~GuidelineStateTemplateHorizontalBottomHover ()
{
}

void GuidelineStateTemplateHorizontalBottomHover::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateHorizontalBottomHover::begin";

  GuidelineStateTemplateAbstract::beginCommon (templateHomeLine(sceneRect ()));

  context().guideline().setGraphicsItemVisible (true); // Undo setVisible(false) from Hide class

  GuidelineFormat guidelineFormat;
  context().guideline().setGraphicsItemPen (guidelineFormat.colorDeployedHover (),
                                            guidelineFormat.lineWidthHover ()); // Show
}

bool GuidelineStateTemplateHorizontalBottomHover::doPaint () const
{
  return true;
}

void GuidelineStateTemplateHorizontalBottomHover::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateHorizontalBottomHover::end";
}

void GuidelineStateTemplateHorizontalBottomHover::handleHoverEnterEvent ()
{
  // This event would have been handled by GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_LURKING
}

void GuidelineStateTemplateHorizontalBottomHover::handleHoverLeaveEvent ()
{
  context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_LURKING);
}

void GuidelineStateTemplateHorizontalBottomHover::handleMousePress (const QPointF &posScene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateHorizontalBottomHover::handleMousePress";

  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_HORIZONTAL_HOVER,
                          GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_LURKING);
}

void GuidelineStateTemplateHorizontalBottomHover::handleShowHide (bool show)
{
  if (!show) {
    context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_HIDE);
  }
}

QString GuidelineStateTemplateHorizontalBottomHover::state () const
{
  return ("GuidelineStateTemplateHorizontalBottomHover");
}

