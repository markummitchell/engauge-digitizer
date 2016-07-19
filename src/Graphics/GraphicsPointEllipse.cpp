/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DataKey.h"
#include "GraphicsPoint.h"
#include "GraphicsPointEllipse.h"
#include "Logger.h"
#include <QColor>
#include <QGraphicsScene>
#include "QtToString.h"

GraphicsPointEllipse::GraphicsPointEllipse(GraphicsPoint &graphicsPoint,
                                           const QRect &rect) :
  QGraphicsEllipseItem (rect),
  m_graphicsPoint (graphicsPoint),
  m_shadow (0)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsPointEllipse::GraphicsPointEllipse";
}

QVariant GraphicsPointEllipse::itemChange(GraphicsItemChange change,
                                          const QVariant &value)
{
  if (change == QGraphicsItem::ItemPositionHasChanged) {

    LOG4CPP_DEBUG_S ((*mainCat)) << "GraphicsPointEllipse::itemChange"
                                 << " identifier=" << data (DATA_KEY_IDENTIFIER).toString().toLatin1().data()
                                 << " positionHasChanged";

    setData (DATA_KEY_POSITION_HAS_CHANGED, QVariant (true));
  }

  return QGraphicsEllipseItem::itemChange(change,
                                          value);
}

void GraphicsPointEllipse::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
  // Highlighted
  setOpacityForSubtree (m_graphicsPoint.highlightOpacity());

  emit signalPointHoverEnter (data (DATA_KEY_IDENTIFIER).toString ());

  QGraphicsEllipseItem::hoverEnterEvent (event);
}

void GraphicsPointEllipse::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
  // Unhighlighted
  setOpacityForSubtree (MAX_OPACITY);

  emit signalPointHoverLeave (data (DATA_KEY_IDENTIFIER).toString ());

  QGraphicsEllipseItem::hoverLeaveEvent (event);
}

void GraphicsPointEllipse::setOpacityForSubtree (double opacity)
{
  // Set this item
  setOpacity (opacity);

  if (m_shadow != 0) {

    // Set the child item. Opacity < MAX_OPACITY is too dark so child is set to totally transparent
    m_shadow->setOpacity (opacity < MAX_OPACITY ? 0.0 : opacity);
  }
}

void GraphicsPointEllipse::setRadius(int radius)
{
  // Resize assuming symmetry about the origin, and an aspect ratio of 1:1 (so x and y scales are the same)
  double scale = (2 * radius) / boundingRect().width();
  setScale (scale);
}

void GraphicsPointEllipse::setShadow (GraphicsPointEllipse *shadow)
{
  m_shadow = shadow;
}
