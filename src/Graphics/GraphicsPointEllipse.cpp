/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DataKey.h"
#include "GraphicsPoint.h"
#include "GraphicsPointEllipse.h"
#include "Logger.h"
#include <QGraphicsScene>
#include "QtToString.h"

GraphicsPointEllipse::GraphicsPointEllipse(GraphicsPoint &graphicsPoint,
                                           const QRect &rect) :
  QGraphicsEllipseItem (rect),
  m_graphicsPoint (graphicsPoint)
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

void GraphicsPointEllipse::setRadius(int radius)
{
  // Resize assuming symmetry about the origin, and an aspect ratio of 1:1 (so x and y scales are the same)
  double scale = (2 * radius) / boundingRect().width();
  setScale (scale);
}
