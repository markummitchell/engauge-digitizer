#include "DataKey.h"
#include "GraphicsItemType.h"
#include "GraphicsPoint.h"
#include "Logger.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QPen>
#include "QtToString.h"

GraphicsPoint::GraphicsPoint(QGraphicsScene &scene,
                             const QString &identifier,
                             const QPointF &posScreen,
                             const QColor &color,
                             unsigned int radius,
                             double lineWidth,
                             double ordinal) :
  GraphicsPointAbstractBase (),
  m_graphicsItemEllipse (0),
  m_shadowZeroWidthEllipse (0),
  m_graphicsItemPolygon (0),
  m_shadowZeroWidthPolygon (0),
  m_wanted (true)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsPoint::GraphicsPoint identifier=" << identifier.toLatin1 ().data ();

  const double ZERO_WIDTH = 0.0;

  m_graphicsItemEllipse = new QGraphicsEllipseItem (QRect (posScreen.x () - radius,
                                                           posScreen.y () - radius,
                                                           2 * radius + 1,
                                                           2 * radius + 1));
  scene.addItem (m_graphicsItemEllipse);

  m_graphicsItemEllipse->setData (DATA_KEY_IDENTIFIER, identifier);
  m_graphicsItemEllipse->setData (DATA_KEY_GRAPHICS_ITEM_TYPE, GRAPHICS_ITEM_TYPE_POINT);
  m_graphicsItemEllipse->setData (DATA_KEY_ORDINAL, ordinal);
  m_graphicsItemEllipse->setPos (posScreen.x (),
                                 posScreen.y ());
  m_graphicsItemEllipse->setPen (QPen (QBrush (color), lineWidth));
  m_graphicsItemEllipse->setEnabled (true);
  m_graphicsItemEllipse->setFlags (QGraphicsItem::ItemIsSelectable |
                                   QGraphicsItem::ItemIsMovable |
                                   QGraphicsItem::ItemSendsGeometryChanges);

  m_graphicsItemEllipse->setToolTip (identifier);
  m_graphicsItemEllipse->setData (DATA_KEY_GRAPHICS_ITEM_TYPE, GRAPHICS_ITEM_TYPE_POINT);

  // Shadow item is not selectable so it needs no stored data
  m_shadowZeroWidthEllipse = new QGraphicsEllipseItem (m_graphicsItemEllipse->rect(),
                                                       m_graphicsItemEllipse);
  m_shadowZeroWidthEllipse->setPen (QPen (QBrush (color), ZERO_WIDTH));
  m_shadowZeroWidthEllipse->setEnabled (true);
}

GraphicsPoint::GraphicsPoint(QGraphicsScene &scene,
                             const QString &identifier,
                             const QPointF &posScreen,
                             const QColor &color,
                             const QPolygonF &polygon,
                             double lineWidth,
                             double ordinal) :
  GraphicsPointAbstractBase (),
  m_graphicsItemEllipse (0),
  m_shadowZeroWidthEllipse (0),
  m_graphicsItemPolygon (0),
  m_shadowZeroWidthPolygon (0),
  m_wanted (true)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsPoint::GraphicsPoint identifier=" << identifier.toLatin1 ().data ();

  const double ZERO_WIDTH = 0.0;

  m_graphicsItemPolygon = new QGraphicsPolygonItem (polygon);
  scene.addItem (m_graphicsItemPolygon);

  m_graphicsItemPolygon->setData (DATA_KEY_IDENTIFIER, identifier);
  m_graphicsItemPolygon->setData (DATA_KEY_GRAPHICS_ITEM_TYPE, GRAPHICS_ITEM_TYPE_POINT);
  m_graphicsItemPolygon->setData (DATA_KEY_ORDINAL, ordinal);
  m_graphicsItemPolygon->setPos (posScreen.x (),
                                 posScreen.y ());
  m_graphicsItemPolygon->setPen (QPen (QBrush (color), lineWidth));
  m_graphicsItemPolygon->setEnabled (true);
  m_graphicsItemPolygon->setFlags (QGraphicsItem::ItemIsSelectable |
                                   QGraphicsItem::ItemIsMovable |
                                   QGraphicsItem::ItemSendsGeometryChanges);

  m_graphicsItemPolygon->setToolTip (identifier);
  m_graphicsItemPolygon->setData (DATA_KEY_GRAPHICS_ITEM_TYPE, GRAPHICS_ITEM_TYPE_POINT);

  // Shadow item is not selectable so it needs no stored data
  m_shadowZeroWidthPolygon = new QGraphicsPolygonItem (polygon,
                                                       m_graphicsItemPolygon);
  m_shadowZeroWidthPolygon->setPen (QPen (QBrush (color), ZERO_WIDTH));
  m_shadowZeroWidthPolygon->setEnabled (true);
}

GraphicsPoint::~GraphicsPoint()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsPoint::~GraphicsPoint";

  if (m_graphicsItemEllipse == 0) {
    QGraphicsScene *scene = m_graphicsItemPolygon->scene();
    scene->removeItem (m_graphicsItemPolygon);
    delete m_graphicsItemPolygon;
    m_graphicsItemPolygon = 0;
  } else {
    QGraphicsScene *scene = m_graphicsItemEllipse->scene();
    scene->removeItem (m_graphicsItemEllipse);
    delete m_graphicsItemEllipse;
    m_graphicsItemEllipse = 0;
  }
}

QVariant GraphicsPoint::data (int key) const
{
  if (m_graphicsItemEllipse == 0) {
    return m_graphicsItemPolygon->data (key);
  } else {
    return m_graphicsItemEllipse->data (key);
  }
}

QPointF GraphicsPoint::pos () const
{
  if (m_graphicsItemEllipse == 0) {
    return m_graphicsItemPolygon->pos ();
  } else {
    return m_graphicsItemEllipse->pos ();
  }
}

void GraphicsPoint::setData (int key, const QVariant &data)
{
  if (m_graphicsItemEllipse == 0) {
    m_graphicsItemPolygon->setData (key, data);
  } else {
    m_graphicsItemPolygon->setData (key, data);
  }
}

void GraphicsPoint::setToolTip (const QString &toolTip)
{
  if (m_graphicsItemEllipse == 0) {
    m_graphicsItemPolygon->setToolTip (toolTip);
  } else {
    m_graphicsItemEllipse->setToolTip (toolTip);
  }
}

void GraphicsPoint::setWanted (bool wanted)
{
  m_wanted = wanted;
}

bool GraphicsPoint::wanted () const
{
  return m_wanted;
}
