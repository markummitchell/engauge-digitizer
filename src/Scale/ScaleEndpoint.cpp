/******************************************************************************************************
 * (C) 2017 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DataKey.h"
#include "EnumsToQt.h"
#include "GraphicsItemType.h"
#include "Logger.h"
#include <QGraphicsScene>
#include <QPointF>
#include "ScaleEndpoint.h"
#include "ZValues.h"

ScaleEndpoint::ScaleEndpoint(QGraphicsScene  &scene,
                             QGraphicsItem *parent,
                             const QPointF &posScreen) :
  QGraphicsEllipseItem (parent)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "ScaleEndpoint::ScaleEndpoint";

  setData (DATA_KEY_GRAPHICS_ITEM_TYPE, QVariant (GRAPHICS_ITEM_TYPE_SCALE_ENDPOINT));

  // Make this transparent now, but always visible so hover events work
  scene.addItem (this);
  setPen (QPen (Qt::transparent));
  setZValue (Z_VALUE_CURVE_ENDPOINT);
  setVisible (true);
  setAcceptHoverEvents (true);
  setFlags (QGraphicsItem::ItemIsFocusable);
  setPos (posScreen);
}

ScaleEndpoint::~ScaleEndpoint ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "ScaleEndpoint::~ScaleEndpoint";
}
