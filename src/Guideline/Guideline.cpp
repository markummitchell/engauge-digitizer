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
#include <QGraphicsSceneMouseEvent>
#include <QLineF>
#include <QPen>
#include "ZValues.h"

// Template guidelines are thicker so they can be easily clicked on for dragging
const double GUIDELINE_LINEWIDTH_TEMPLATE = 2;

// Cloned guidelines are as thin as possible so their measurements are as precise as possible
//const double GUIDELINE_LINEWIDTH_CLONE = -1;

Guideline::Guideline(QGraphicsScene  &scene,
                     GuidelineState guidelineStateInitial)
{
  setData (DATA_KEY_GRAPHICS_ITEM_TYPE, QVariant (GRAPHICS_ITEM_TYPE_GUIDELINE));

  // Make this transparent now, but always visible so hover events work
  scene.addItem (this);
  setPen (QPen (QBrush (Qt::transparent),
                GUIDELINE_LINEWIDTH_TEMPLATE));
  setZValue (Z_VALUE_CURVE);
  setVisible (true);
  setFlags (QGraphicsItem::ItemIsFocusable |
            QGraphicsItem::ItemIsSelectable |
            QGraphicsItem::ItemIsMovable);

  // Create context after registering with the scene. The transition
  // into the initial state will position the line if it is a template guideline
  m_context = new GuidelineStateContext (*this,
                                         guidelineStateInitial);

  // Final step is to enable/disable hover events
  setAcceptHoverEvents (m_context->initialHoverEventsEnable ());
  setHover (false); // Initially the cursor is not hovering over this object. Later a hover event will change this state
}

Guideline::~Guideline ()
{
  delete m_context;
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
  // Handle the event
  QGraphicsLineItem::mouseReleaseEvent (event);

  m_context->cloneDraggedGuideline ();
}

void Guideline::setHover (bool hover)
{
  if (hover || m_context->alwaysVisible ()) {

    QColor color (Qt::blue);

    setPen (QPen (QBrush (color),
                  GUIDELINE_LINEWIDTH_TEMPLATE));

  } else {

    setPen (QPen (QBrush (Qt::transparent),
                  GUIDELINE_LINEWIDTH_TEMPLATE));

  }
}
