#include "DataKey.h"
#include "GraphicsPoint.h"
#include "GraphicsPointPolygon.h"
#include "Logger.h"
#include <QGraphicsScene>

GraphicsPointPolygon::GraphicsPointPolygon(const QPolygonF &polygon) :
  QGraphicsPolygonItem (polygon)
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

//    m_graphicsPoint.moveAttachedLines(pos());
  }

  return QGraphicsPolygonItem::itemChange(change,
                                          value);
}
