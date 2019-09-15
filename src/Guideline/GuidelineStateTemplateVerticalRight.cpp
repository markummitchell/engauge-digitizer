/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateVerticalRight.h"
#include "Logger.h"

GuidelineStateTemplateVerticalRight::GuidelineStateTemplateVerticalRight (GuidelineStateContext &context) :
  GuidelineStateTemplateAbstract (context)
{
}

GuidelineStateTemplateVerticalRight::~GuidelineStateTemplateVerticalRight ()
{
}

void GuidelineStateTemplateVerticalRight::begin ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateVerticalRight::begin";

  GuidelineStateTemplateAbstract::beginCommon (templateHomeLine(context().guideline().lineWidthTemplate(),
                                                                sceneRect ()));
}

void GuidelineStateTemplateVerticalRight::end ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateVerticalRight::end";
}

void GuidelineStateTemplateVerticalRight::handleMousePress (const QPointF &posScene)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateVerticalRight::handleMousePress";

  handleMousePressCommon (posScene,
                          GUIDELINE_STATE_DEPLOYED_VERTICAL,
                          GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT);
}

void GuidelineStateTemplateVerticalRight::handleMouseRelease ()
{
  // Not called
}

QString GuidelineStateTemplateVerticalRight::state () const
{
  return ("GuidelineStateTemplateVerticalRight");
}

QLineF GuidelineStateTemplateVerticalRight::templateHomeLine (double lineWidth,
                                                              const QRectF &sceneRect)
{
  return QLineF (sceneRect.bottomRight() - QPointF (lineWidth, 0),
                 sceneRect.topRight() - QPointF (lineWidth, 0));
}
