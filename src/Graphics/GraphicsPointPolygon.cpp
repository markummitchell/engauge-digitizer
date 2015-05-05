#include "DataKey.h"
#include "GraphicsPoint.h"
#include "GraphicsPointPolygon.h"
#include "Logger.h"
#include <QGraphicsScene>
#include "QtToString.h"

GraphicsPointPolygon::GraphicsPointPolygon(GraphicsPoint &graphicsPoint,
                                           const QPolygonF &polygon) :
  QGraphicsPolygonItem (polygon),
  m_graphicsPoint (graphicsPoint)

{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsPointPolygon::GraphicsPointPolygon";
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

void GraphicsPointPolygon::setRadius(int radius)
{
  // Resize assuming symmetry about the origin, and an aspect ratio of 1:1 (so x and y scales are the same)
  double scale = (2 * radius) / boundingRect().width();
  setScale (scale);
}
