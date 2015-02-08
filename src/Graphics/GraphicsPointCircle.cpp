#include "DataKey.h"
#include "GraphicsItemType.h"
#include "GraphicsPointCircle.h"
#include "Logger.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QPen>
#include "QtToString.h"

GraphicsPointCircle::GraphicsPointCircle(const QString &identifier,
                                         const QPointF &posScreen,
                                         const QColor &color,
                                         unsigned int radius,
                                         double lineWidth,
                                         int ordinal) :
  GraphicsPointAbstractBase (),
  QGraphicsEllipseItem (QRect (posScreen.x () - radius,
                               posScreen.y () - radius,
                               2 * radius + 1,
                               2 * radius + 1))
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsPointCircle::GraphicsPointCircle identifier=" << identifier.toLatin1 ().data ();

  const double ZERO_WIDTH = 0.0;

  setData (DATA_KEY_IDENTIFIER, identifier);
  setData (DATA_KEY_GRAPHICS_ITEM_TYPE, GRAPHICS_ITEM_TYPE_POINT);
  setData (DATA_KEY_ORDINAL, ordinal);
  setPos (posScreen.x (),
          posScreen.y ());
  setPen (QPen (QBrush (color), lineWidth));
  setEnabled (true);
  setFlags (QGraphicsItem::ItemIsSelectable |
            QGraphicsItem::ItemIsMovable |
            QGraphicsItem::ItemSendsGeometryChanges);

  // Shadow item is not selectable so it needs no stored data
  m_shadowZeroWidth = new QGraphicsEllipseItem (this->rect(),
                                                 this);
  m_shadowZeroWidth->setPen (QPen (QBrush (color), ZERO_WIDTH));
  m_shadowZeroWidth->setEnabled (true);
}

QVariant GraphicsPointCircle::itemChange(GraphicsItemChange change,
                                         const QVariant &value)
{
  if (change == QGraphicsItem::ItemPositionHasChanged) {

    LOG4CPP_DEBUG_S ((*mainCat)) << "GraphicsPointCircle::itemChange"
                                 << " identifier=" << data (DATA_KEY_IDENTIFIER).toString().toLatin1().data()
                                 << " positionHasChanged";

    setData (DATA_KEY_POSITION_HAS_CHANGED, QVariant (true));
  }

  return QGraphicsItem::itemChange(change,
                                   value);
}
