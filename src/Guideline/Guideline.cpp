/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DataKey.h"
#include "EnumsToQt.h"
#include "GraphicsItemType.h"
#include "Guideline.h"
#include "Logger.h"
#include <QGraphicsScene>
#include <QPen>
#include "ZValues.h"

// Presupplied guidelines are thicker so they can be easily clicked on for dragging
const double GUIDELINE_LINEWIDTH_PRESUPPLIED = 6;

// Cloned guidelines are as thin as possible so their measurements are as precise as possible
const double GUIDELINE_LINEWIDTH_CLONE = -1;

Guideline::Guideline(QGraphicsScene  &scene)
{
  setData (DATA_KEY_GRAPHICS_ITEM_TYPE, QVariant (GRAPHICS_ITEM_TYPE_GUIDELINE));

  // Make this transparent now, but always visible so hover events work
  scene.addItem (this);
  setPen (QPen (QBrush (Qt::transparent),
                GUIDELINE_LINEWIDTH_PRESUPPLIED));
  setZValue (Z_VALUE_CURVE);
  setVisible (true);
  setAcceptHoverEvents (true);
  setHover (false); // Initially the cursor is not hovering over this object. Later a hover event will change this state

  // ItemIsMovable requires ItemIsSelectable
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

double Guideline::linewidthPresupplied ()
{
  return GUIDELINE_LINEWIDTH_PRESUPPLIED;
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
