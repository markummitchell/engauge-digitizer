/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DataKey.h"
#include "GraphicsPoint.h"
#include "GraphicsPointPolygon.h"
#include "Logger.h"
#include <QGraphicsScene>
#include "QtToString.h"

GraphicsPointPolygon::GraphicsPointPolygon(GraphicsPoint &graphicsPoint,
                                           const QPolygonF &polygon) :
  QGraphicsPolygonItem (polygon),
  m_graphicsPoint (graphicsPoint),
  m_shadow (nullptr)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsPointPolygon::GraphicsPointPolygon";
}

void GraphicsPointPolygon::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
  // Highlighted
  setOpacityForSubtree (m_graphicsPoint.highlightOpacity ());

  emit signalPointHoverEnter (data (DATA_KEY_IDENTIFIER).toString ());

  QGraphicsPolygonItem::hoverEnterEvent (event);
}

void GraphicsPointPolygon::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
  // Unhighlighted
  setOpacityForSubtree (MAX_OPACITY);

  emit signalPointHoverLeave (data (DATA_KEY_IDENTIFIER).toString ());

  QGraphicsPolygonItem::hoverLeaveEvent (event);
}

QVariant GraphicsPointPolygon::itemChange(GraphicsItemChange change,
                                          const QVariant &value)
{
  if (change == QGraphicsItem::ItemPositionHasChanged) {

    LOG4CPP_DEBUG_S ((*mainCat)) << "GraphicsPointPolygon::itemChange"
                                 << " identifier=" << data (DATA_KEY_IDENTIFIER).toString().toLatin1().data()
                                 << " positionHasChanged";

    setData (DATA_KEY_POSITION_HAS_CHANGED, QVariant (true));
  }

  return QGraphicsPolygonItem::itemChange(change,
                                          value);
}

void GraphicsPointPolygon::setOpacityForSubtree (double opacity)
{
  // Set this item
  setOpacity (opacity);

  if (m_shadow != nullptr) {

    // Set the child item. Opacity < MAX_OPACITY is too dark so child is set to totally transparent
    m_shadow->setOpacity (opacity < MAX_OPACITY ? 0.0 : opacity);
  }
}

void GraphicsPointPolygon::setRadius(int radius)
{
  // Resize assuming symmetry about the origin, and an aspect ratio of 1:1 (so x and y scales are the same)
  if (boundingRect().width() > 0) {
    double scale = (2 * radius) / boundingRect().width();
    setScale (scale);
  }
}

void GraphicsPointPolygon::setShadow (GraphicsPointPolygon *shadow)
{
  m_shadow = shadow;
}
