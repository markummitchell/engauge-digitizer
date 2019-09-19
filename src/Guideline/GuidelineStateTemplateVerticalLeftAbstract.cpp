/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateVerticalLeftAbstract.h"
#include "Logger.h"

GuidelineStateTemplateVerticalLeftAbstract::GuidelineStateTemplateVerticalLeftAbstract (GuidelineStateContext &context) :
  GuidelineStateTemplateAbstract (context)
{
}

GuidelineStateTemplateVerticalLeftAbstract::~GuidelineStateTemplateVerticalLeftAbstract ()
{
}

QLineF GuidelineStateTemplateVerticalLeftAbstract::templateHomeLine (const QRectF &sceneRect)
{
  return QLineF (sceneRect.bottomLeft(),
                 sceneRect.topLeft());
}
