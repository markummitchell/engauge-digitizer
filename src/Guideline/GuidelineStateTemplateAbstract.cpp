/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GraphicsScene.h"
#include "GuidelineAbstract.h"
#include "GuidelineFormat.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateAbstract.h"
#include "Logger.h"
#include <QPen>
#include "ZValues.h"

GuidelineStateTemplateAbstract::GuidelineStateTemplateAbstract (GuidelineStateContext &context) :
  GuidelineStateAbstractBase (context)
{
}

GuidelineStateTemplateAbstract::~GuidelineStateTemplateAbstract ()
{
}

void GuidelineStateTemplateAbstract::beginCommon (const QLineF &line)
{
  GuidelineFormat guidelineFormat;

  context().guideline().setGraphicsItemZValue (Z_VALUE_GUIDELINE_TEMPLATE);
  // ItemIsSelectable is overkill, and in special cases adds ugly selected dashes
  context().guideline().setGraphicsItemFlags (QGraphicsItem::ItemIsFocusable |
                                              QGraphicsItem::ItemIsMovable);
  context().guideline().setGraphicsItemAcceptHoverEvents (true);

  context().guideline().setGraphicsItemLine (line);
}

void GuidelineStateTemplateAbstract::handleMouseRelease ()
{
}

QLineF GuidelineStateTemplateAbstract::lineFromPoint (const QPointF & /* posScreen */) const
{
  return QLineF (QPointF (0, 0),
                 QPointF (0, 0));
}

void GuidelineStateTemplateAbstract::setPointGraph (const QPointF & /* posGraph */)
{
  // Noop
}

void GuidelineStateTemplateAbstract::updateWithLatestTransformation ()
{
  // Noop
}
