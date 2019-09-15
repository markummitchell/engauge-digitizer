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
  context().guideline().setFlags (QGraphicsItem::ItemIsFocusable |
                                  QGraphicsItem::ItemIsSelectable |
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

void GuidelineStateTemplateAbstract::handleMousePressCommon (const QPointF &pos,
                                                             GuidelineState stateDeployed,
                                                             GuidelineState stateReplacement)
{
  context().setStateReplacement (stateReplacement);

  // Visible Guideline will follow this one. Its geometry will be set after every drag event
  Guideline *guidelineVisible = new Guideline (*context().guideline().scene(),
                                               stateDeployed);

  guidelineVisible->updateGeometry (pos);

  context().guideline().bindGuidelineVisible (guidelineVisible);

  context().requestStateTransition (GUIDELINE_STATE_HANDLE);
}

QLineF GuidelineStateTemplateAbstract::lineFromPoint (const QPointF &/* point */) const
{
  return QLineF (QPointF (0, 0),
                 QPointF (0, 0));
}
