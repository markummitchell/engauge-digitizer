/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateHorizontalBottom.h"
#include "Logger.h"
#include <QObject>

GuidelineStateTemplateHorizontalBottom::GuidelineStateTemplateHorizontalBottom (GuidelineStateContext &context) :
  GuidelineStateTemplateAbstract (context)
{
}

GuidelineStateTemplateHorizontalBottom::~GuidelineStateTemplateHorizontalBottom ()
{
}

void GuidelineStateTemplateHorizontalBottom::begin ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateHorizontalBottom::begin";

  GuidelineStateTemplateAbstract::beginCommon (templateHomeLine(context().guideline().lineWidthTemplate(),
                                                                diagonal (sceneRect ()),
                                                                sceneRect ()));
}

void GuidelineStateTemplateHorizontalBottom::end ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateHorizontalBottom::end";
}

void GuidelineStateTemplateHorizontalBottom::handleMousePress ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GuidelineStateTemplateHorizontalBottom::handleMousePress";

  QLineF line = templateHomeLine(context().guideline().lineWidthTemplate(),
                                 diagonal (sceneRect ()),
                                 sceneRect ());

  handleMousePressCommon (line,
                          GUIDELINE_STATE_DEPLOYED_HORIZONTAL,
                          GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM);
}

void GuidelineStateTemplateHorizontalBottom::handleMouseRelease ()
{
  // Not called
}

QString GuidelineStateTemplateHorizontalBottom::state () const
{
  return ("GuidelineStateTemplateHorizontalBottom");
}

QLineF GuidelineStateTemplateHorizontalBottom::templateHomeLine (double lineWidth,
                                                                 double diagonal,
                                                                 const QRectF &sceneRect)
{
  return QLineF (sceneRect.bottomLeft() + QPointF (-1.0 * diagonal, -0.5 * lineWidth),
                 sceneRect.bottomRight() + QPointF (diagonal, -0.5 * lineWidth));
}
