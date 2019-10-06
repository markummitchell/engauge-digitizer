/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GuidelineAbstract.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateVerticalLeftHide.h"
#include "Logger.h"
#include "Transformation.h"

GuidelineStateTemplateVerticalLeftHide::GuidelineStateTemplateVerticalLeftHide (GuidelineStateContext &context) :
  GuidelineStateTemplateVerticalLeftAbstract (context)
{
}

GuidelineStateTemplateVerticalLeftHide::~GuidelineStateTemplateVerticalLeftHide ()
{
}

void GuidelineStateTemplateVerticalLeftHide::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateVerticalLeftHide::begin";

  GuidelineStateTemplateAbstract::beginCommon (templateHomeLine(sceneRect ()));

  context().guideline().setGraphicsItemVisible (false); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateTemplateVerticalLeftHide::doPaint () const
{
  return false;
}

void GuidelineStateTemplateVerticalLeftHide::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateVerticalLeftHide::end";
}

void GuidelineStateTemplateVerticalLeftHide::handleHoverEnterEvent ()
{
  // Noop
}

void GuidelineStateTemplateVerticalLeftHide::handleHoverLeaveEvent ()
{
  // Noop
}

void GuidelineStateTemplateVerticalLeftHide::handleMousePress (const QPointF & /* posScene */)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateVerticalLeftHide::handleMousePress";
}

void GuidelineStateTemplateVerticalLeftHide::handleVisibleChange (bool visible)
{
  if (visible) {
    context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_LURKING);
  }
}

QString GuidelineStateTemplateVerticalLeftHide::state () const
{
  return ("GuidelineStateTemplateVerticalLeftHide");
}

void GuidelineStateTemplateVerticalLeftHide::updateWithLatestTransformation ()
{
  if (context().transformation().transformIsDefined()) {
    context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_LURKING);
  }
}
