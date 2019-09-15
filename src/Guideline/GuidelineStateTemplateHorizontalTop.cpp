/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateHorizontalTop.h"
#include "Logger.h"

GuidelineStateTemplateHorizontalTop::GuidelineStateTemplateHorizontalTop (GuidelineStateContext &context) :
  GuidelineStateTemplateAbstract (context)
{
}

GuidelineStateTemplateHorizontalTop::~GuidelineStateTemplateHorizontalTop ()
{
}

void GuidelineStateTemplateHorizontalTop::begin ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateHorizontalTop::begin";

  GuidelineStateTemplateAbstract::beginCommon (templateHomeLine(context().guideline().lineWidthTemplate(),
                                                                sceneRect ()));
}

void GuidelineStateTemplateHorizontalTop::end ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateHorizontalTop::end";
}

void GuidelineStateTemplateHorizontalTop::handleMousePress (const QPointF &posScene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateHorizontalTop::handleMousePress";

  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_HORIZONTAL,
                          GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP);
}

void GuidelineStateTemplateHorizontalTop::handleMouseRelease ()
{
  // Not called
}

QString GuidelineStateTemplateHorizontalTop::state () const
{
  return ("GuidelineStateTemplateHorizontalTop");
}

QLineF GuidelineStateTemplateHorizontalTop::templateHomeLine (double lineWidth,
                                                              const QRectF &sceneRect)
{
  return QLineF (sceneRect.topLeft() + QPointF (0, lineWidth),
                 sceneRect.topRight() + QPointF (0, lineWidth));
}
