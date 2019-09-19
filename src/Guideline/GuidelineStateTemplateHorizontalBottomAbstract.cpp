/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateHorizontalBottomAbstract.h"
#include "Logger.h"
#include <QObject>

GuidelineStateTemplateHorizontalBottomAbstract::GuidelineStateTemplateHorizontalBottomAbstract (GuidelineStateContext &context) :
  GuidelineStateTemplateAbstract (context)
{
}

GuidelineStateTemplateHorizontalBottomAbstract::~GuidelineStateTemplateHorizontalBottomAbstract ()
{
}

QLineF GuidelineStateTemplateHorizontalBottomAbstract::templateHomeLine (const QRectF &sceneRect)
{
  return QLineF (sceneRect.bottomLeft(),
                 sceneRect.bottomRight());
}
