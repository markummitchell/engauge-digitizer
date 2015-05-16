#include "CurveStyle.h"
#include "DataKey.h"
#include "EnumsToQt.h"
#include "GraphicsItemType.h"
#include "GraphicsPoint.h"
#include "GraphicsPointEllipse.h"
#include "GraphicsPointPolygon.h"
#include "Logger.h"
#include "PointStyle.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QPen>
#include <QTextStream>
#include "QtToString.h"

const double ZERO_WIDTH = 0.0;

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

  m_graphicsItemEllipse = new GraphicsPointEllipse (*this,
                                                    QRect (- radius,
                                                           - radius,
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

  // Shadow item is not selectable so it needs no stored data. Do NOT
  // call QGraphicsScene::addItem since the QGraphicsItem::setParentItem call adds the item
  m_shadowZeroWidthEllipse = new GraphicsPointEllipse (*this,
                                                       QRect (- radius,
                                                              - radius,
                                                              2 * radius + 1,
                                                              2 * radius + 1));
  m_shadowZeroWidthEllipse->setParentItem(m_graphicsItemPolygon); // Dragging parent also drags child

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

  m_graphicsItemPolygon = new GraphicsPointPolygon (*this,
                                                    polygon);
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

  // Shadow item is not selectable so it needs no stored data. Do NOT
  // call QGraphicsScene::addItem since the QGraphicsItem::setParentItem call adds the item
  m_shadowZeroWidthPolygon = new GraphicsPointPolygon (*this,
                                                       polygon);
  m_shadowZeroWidthPolygon->setParentItem(m_graphicsItemPolygon); // Dragging parent also drags child

  m_shadowZeroWidthPolygon->setPen (QPen (QBrush (color), ZERO_WIDTH));
  m_shadowZeroWidthPolygon->setEnabled (true);
}

GraphicsPoint::~GraphicsPoint()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsPoint::~GraphicsPoint";

  if (m_graphicsItemEllipse == 0) {

    QGraphicsScene *scene = m_graphicsItemPolygon->scene();

    // Since m_shadowZeroWidthPolygon is a child of m_graphicsItemPolygon, removing the parent removes both
    scene->removeItem (m_graphicsItemPolygon);
    delete m_graphicsItemPolygon;
    m_graphicsItemPolygon = 0;
    m_shadowZeroWidthPolygon = 0;


  } else {

    QGraphicsScene *scene = m_graphicsItemEllipse->scene();

    // Since m_shadowZeroWidthEllipse is a child of m_graphicsItemEllipse, removing the parent removes both
    scene->removeItem (m_graphicsItemEllipse);
    delete m_graphicsItemEllipse;
    m_graphicsItemEllipse = 0;
    m_shadowZeroWidthEllipse = 0;

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

void GraphicsPoint::printStream (QString indentation,
                                 QTextStream &str) const
{
  str << indentation << "GraphicsPoint\n";

  indentation += INDENTATION_DELTA;

  QString identifier;
  int ordinal;
  QString pointType;
  QPointF pos;
  if (m_graphicsItemEllipse == 0) {
    identifier = m_graphicsItemPolygon->data (DATA_KEY_IDENTIFIER).toString ();
    ordinal = m_graphicsItemPolygon->data (DATA_KEY_ORDINAL).toDouble ();
    pointType = "polygon";
    pos = m_graphicsItemPolygon->pos();
  } else {
    identifier = m_graphicsItemEllipse->data (DATA_KEY_IDENTIFIER).toString ();
    ordinal = m_graphicsItemEllipse->data (DATA_KEY_ORDINAL).toDouble ();
    pointType = "ellipse";
    pos = m_graphicsItemEllipse->pos();
  }

  str << indentation << identifier
      << " ordinal=" << ordinal
      << " " << pointType << "Pos=" << QPointFToString (pos) << "\n";
}

void GraphicsPoint::reset ()
{
  m_wanted = false;
}

void GraphicsPoint::setData (int key, const QVariant &data)
{
  if (m_graphicsItemEllipse == 0) {
    m_graphicsItemPolygon->setData (key, data);
  } else {
    m_graphicsItemEllipse->setData (key, data);
  }
}


void GraphicsPoint::setPointStyle(const PointStyle &pointStyle)
{
  // Setting pen and radius of parent graphics items below also affects the child shadows
  // (m_shadowItemPolygon and m_shadowItemEllipse)
  if (m_graphicsItemEllipse == 0) {
    m_graphicsItemPolygon->setPen (QPen (ColorPaletteToQColor(pointStyle.paletteColor()),
                                         pointStyle.lineWidth()));
    m_graphicsItemPolygon->setRadius (pointStyle.radius());

  } else {
    m_graphicsItemEllipse->setPen (QPen (ColorPaletteToQColor(pointStyle.paletteColor()),
                                         pointStyle.lineWidth()));
    m_graphicsItemEllipse->setRadius (pointStyle.radius());
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

void GraphicsPoint::setWanted ()
{
  m_wanted = true;
}

void GraphicsPoint::updateCurveStyle (const CurveStyle &curveStyle)
{
  setPointStyle (curveStyle.pointStyle()); // This point
}

bool GraphicsPoint::wanted () const
{
  return m_wanted;
}
