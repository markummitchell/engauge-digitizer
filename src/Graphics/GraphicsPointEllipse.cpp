#include "DataKey.h"
#include "GraphicsPoint.h"
#include "GraphicsPointEllipse.h"
#include "Logger.h"
#include <QGraphicsScene>

GraphicsPointEllipse::GraphicsPointEllipse(GraphicsPoint &graphicsPoint) :
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

    m_graphicsPoint.moveAttachedLines(pos());
  }

  return QGraphicsEllipseItem::itemChange(change,
                                          value);
}
