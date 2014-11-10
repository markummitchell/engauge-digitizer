#include "DataKey.h"
#include "GraphicsItemType.h"
#include "GraphicsPointPolygon.h"
#include "Logger.h"
#include <QGraphicsSceneContextMenuEvent>
#include <QPen>
#include "QtToString.h"

GraphicsPointPolygon::GraphicsPointPolygon(const QString &identifier,
                                           const QPointF &posScreen,
                                           const QColor &color,
                                           const QPolygonF &polygon) :
  GraphicsPointAbstractBase (),
  QGraphicsPolygonItem (polygon)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsPointPolygon::GraphicsPointPolygon identifier=" << identifier.toLatin1 ().data ();

  setData (DATA_KEY_IDENTIFIER, identifier);
  setData (DATA_KEY_GRAPHICS_ITEM_TYPE, GRAPHICS_ITEM_TYPE_POINT);
  setPos (posScreen.x (),
          posScreen.y ());
  setPen (QPen (color));
  setEnabled (true);
  setFlags (QGraphicsItem::ItemIsSelectable |
            QGraphicsItem::ItemIsMovable |
            QGraphicsItem::ItemSendsGeometryChanges);
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

  return QGraphicsItem::itemChange(change,
                                   value);
}
