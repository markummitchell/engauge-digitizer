/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DataKey.h"
#include "EngaugeAssert.h"
#include "EnumsToQt.h"
#include "GraphicsItemType.h"
#include "Guideline.h"
#include "GuidelineStateContext.h"
#include "Logger.h"
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QLineF>
#include <QPen>
#include "ZValues.h"

// Template guidelines are thicker so they can be easily clicked on for dragging
const double GUIDELINE_LINEWIDTH_TEMPLATE = 10;

// Cloned guidelines are as thin as possible so their measurements are as precise as possible
//const double GUIDELINE_LINEWIDTH_CLONE = -1;

Guideline::Guideline(QGraphicsScene  &scene,
                     GuidelineState guidelineStateInitial) :
  m_context (*this,
             guidelineStateInitial)
{
  setData (DATA_KEY_GRAPHICS_ITEM_TYPE, QVariant (GRAPHICS_ITEM_TYPE_GUIDELINE));

  // Make this transparent now, but always visible so hover events work
  scene.addItem (this);
  setPen (QPen (QBrush (Qt::transparent),
                GUIDELINE_LINEWIDTH_TEMPLATE));
  setZValue (Z_VALUE_CURVE);
  setVisible (true);
  setAcceptHoverEvents (true);
  setHover (false); // Initially the cursor is not hovering over this object. Later a hover event will change this state

  setFlags (QGraphicsItem::ItemIsFocusable |
            QGraphicsItem::ItemIsSelectable |
            QGraphicsItem::ItemIsMovable);
}

Guideline::~Guideline ()
{
}

void Guideline::hoverEnterEvent(QGraphicsSceneHoverEvent * /* event */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Guideline::hoverEnterEvent";

  setHover (true);
}

void Guideline::hoverLeaveEvent(QGraphicsSceneHoverEvent * /* event */)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Guideline::hoverLeaveEvent";

  setHover (false);
}

double Guideline::lineWidthTemplate () const
{
  return GUIDELINE_LINEWIDTH_TEMPLATE;
}

void Guideline::mouseReleaseEvent (QGraphicsSceneMouseEvent *event)
{
  ENGAUGE_ASSERT (m_context.isTemplate ());

  // Clone this Guideline and put the clone at the current position
  QLineF newLine = line ();
  Guideline *newGuideline = new Guideline (*(scene ()),
                                           m_context.cloneState ());
  newGuideline->setLine (newLine);

  // Move this template Guideline back to its original border spot
  QLineF homeLine = m_context.templateHomeLine ();
  setLine (homeLine);

  // Handle the event
  QGraphicsLineItem::mouseReleaseEvent (event);
}

void Guideline::setHover (bool hover)
{
  if (hover) {

    QColor color (Qt::gray);

    setPen (QPen (color));

  } else {

    setPen (QPen (Qt::transparent));

  }
}
