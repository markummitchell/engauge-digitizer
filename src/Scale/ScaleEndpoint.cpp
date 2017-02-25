/******************************************************************************************************
 * (C) 2017 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DataKey.h"
#include "EngaugeAssert.h"
#include "EnumsToQt.h"
#include "GraphicsItemType.h"
#include "Logger.h"
#include <QGraphicsSceneEvent>
#include <QPen>
#include <QPointF>
#include "ScaleBar.h"
#include "ScaleEndpoint.h"
#include "ZValues.h"

ScaleEndpoint::ScaleEndpoint(ScaleBar &scaleBar,
                             const QPointF &posScreen) :
  QGraphicsEllipseItem (&scaleBar), // This registers with the QGraphicsScene so addItem is not needed
  m_scaleBar (scaleBar)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "ScaleEndpoint::ScaleEndpoint";

  setData (DATA_KEY_GRAPHICS_ITEM_TYPE, QVariant (GRAPHICS_ITEM_TYPE_SCALE_ENDPOINT));

  // Make this transparent now, but always visible so hover events work
  setPen (QPen (Qt::black));
  setZValue (Z_VALUE_CURVE_ENDPOINT);
  setVisible (true);
  setAcceptHoverEvents (true);
  setFlags (QGraphicsItem::ItemIsFocusable |
            QGraphicsItem::ItemIsSelectable |
            QGraphicsItem::ItemIsMovable);
  setPos (posScreen);
}

ScaleEndpoint::~ScaleEndpoint ()
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "ScaleEndpoint::~ScaleEndpoint";
}

void ScaleEndpoint::mouseMoveEvent (QGraphicsSceneMouseEvent * /* event */)
{
  // Forward to the scale bar
  m_scaleBar.handleEndpointMove ();
}
