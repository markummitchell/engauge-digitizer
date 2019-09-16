/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedHorizontalAbstract.h"
#include "Logger.h"
#include <QGraphicsScene>

GuidelineStateDeployedHorizontalAbstract::GuidelineStateDeployedHorizontalAbstract (GuidelineStateContext &context) :
  GuidelineStateDeployedAbstract (context)
{
}

GuidelineStateDeployedHorizontalAbstract::~GuidelineStateDeployedHorizontalAbstract ()
{
}

QLineF GuidelineStateDeployedHorizontalAbstract::lineFromPoint (const QPointF &point) const
{
  double width = context().guideline().scene()->width();

  return QLineF (QPointF (0, point.y()),
                 QPointF (width - 1, point.y()));
}
