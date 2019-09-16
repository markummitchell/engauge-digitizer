/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GraphicsScene.h"
#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateTemplateAbstract.h"
#include "Logger.h"
#include <QPen>
#include "ZValues.h"

const Qt::GlobalColor COLOR_HIDDEN = Qt::transparent; // Hide until hover entry
const Qt::GlobalColor COLOR_VISIBLE = Qt::blue; // Show after hover entry

GuidelineStateTemplateAbstract::GuidelineStateTemplateAbstract (GuidelineStateContext &context) :
  GuidelineStateAbstractBase (context)
{
}

GuidelineStateTemplateAbstract::~GuidelineStateTemplateAbstract ()
{
}

void GuidelineStateTemplateAbstract::beginCommon (const QLineF &line)
{
  context().guideline().setZValue (Z_VALUE_GUIDELINE_TEMPLATE);
  context().guideline().setVisible (true); // True is required for hover to work
  // ItemIsSelectable is overkill, and in special cases adds ugly selected dashes
  context().guideline().setFlags (QGraphicsItem::ItemIsFocusable |
                                  QGraphicsItem::ItemIsMovable);
  context().guideline().setAcceptHoverEvents (true);
  context().guideline().setPenColor (COLOR_HIDDEN); // Hide until hover entry

  context().guideline().setLine (line);
}

bool GuidelineStateTemplateAbstract::doPaint () const
{
  return true;
}

void GuidelineStateTemplateAbstract::handleHoverEnterEvent ()
{
  context().guideline().setPenColor (COLOR_VISIBLE); // Hide until hover entry
}

void GuidelineStateTemplateAbstract::handleHoverLeaveEvent ()
{
  context().guideline().setPenColor (COLOR_HIDDEN); // Hide until hover entry
}

QLineF GuidelineStateTemplateAbstract::lineFromPoint (const QPointF &/* point */) const
{
  return QLineF (QPointF (0, 0),
                 QPointF (0, 0));
}
