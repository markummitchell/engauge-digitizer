/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GuidelineAbstract.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateHorizontalBottomHide.h"
#include "Logger.h"
#include <QObject>
#include "Transformation.h"

GuidelineStateTemplateHorizontalBottomHide::GuidelineStateTemplateHorizontalBottomHide (GuidelineStateContext &context) :
  GuidelineStateTemplateHorizontalBottomAbstract (context)
{
}

GuidelineStateTemplateHorizontalBottomHide::~GuidelineStateTemplateHorizontalBottomHide ()
{
}

void GuidelineStateTemplateHorizontalBottomHide::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateHorizontalBottomHide::begin";

  GuidelineStateTemplateAbstract::beginCommon (templateHomeLine(sceneRect ()));

  context().guideline().setGraphicsItemVisible (false); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateTemplateHorizontalBottomHide::doPaint () const
{
  return false;
}

void GuidelineStateTemplateHorizontalBottomHide::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateHorizontalBottomHide::end";
}

void GuidelineStateTemplateHorizontalBottomHide::handleHoverEnterEvent ()
{
  // Noop
}

void GuidelineStateTemplateHorizontalBottomHide::handleHoverLeaveEvent ()
{
  // Noop
}

void GuidelineStateTemplateHorizontalBottomHide::handleMousePress (const QPointF & /* posScene */)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateHorizontalBottomHide::handleMousePress";
}

void GuidelineStateTemplateHorizontalBottomHide::handleVisibleChange (bool visible)
{
  if (visible) {
    context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_LURKING);
  }
}

QString GuidelineStateTemplateHorizontalBottomHide::state () const
{
  return ("GuidelineStateTemplateHorizontalBottomHide");
}

void GuidelineStateTemplateHorizontalBottomHide::updateWithLatestTransformation ()
{
  if (context().transformation().transformIsDefined()) {
    context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_LURKING);
  }
}
