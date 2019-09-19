/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GuidelineAbstract.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateVerticalRightHide.h"
#include "Logger.h"

GuidelineStateTemplateVerticalRightHide::GuidelineStateTemplateVerticalRightHide (GuidelineStateContext &context) :
  GuidelineStateTemplateVerticalRightAbstract (context)
{
}

GuidelineStateTemplateVerticalRightHide::~GuidelineStateTemplateVerticalRightHide ()
{
}

void GuidelineStateTemplateVerticalRightHide::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateVerticalRightHide::begin";

  GuidelineStateTemplateAbstract::beginCommon (templateHomeLine(sceneRect ()));

  context().guideline().setGraphicsItemVisible (false); // Stop hover and painting (doPoint only stops painting)
}

bool GuidelineStateTemplateVerticalRightHide::doPaint () const
{
  return false;
}

void GuidelineStateTemplateVerticalRightHide::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GuidelineStateTemplateVerticalRightHide::end";
}

void GuidelineStateTemplateVerticalRightHide::handleHoverEnterEvent ()
{
  // Noop
}

void GuidelineStateTemplateVerticalRightHide::handleHoverLeaveEvent ()
{
  // Noop
}

void GuidelineStateTemplateVerticalRightHide::handleMousePress (const QPointF & /* posScene */)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateVerticalRightHide::handleMousePress";
}

void GuidelineStateTemplateVerticalRightHide::handleShowHide (bool show)
{
  if (show) {
    context().requestStateTransition(GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_LURKING);
  }
}

QString GuidelineStateTemplateVerticalRightHide::state () const
{
  return ("GuidelineStateTemplateVerticalRightHide");
}
