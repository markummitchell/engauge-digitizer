#include "DataKey.h"
#include "EnumsToQt.h"
#include "GraphicsItemType.h"
#include "GraphicsPoint.h"
#include "GraphicsPointFactory.h"
#include "PointStyle.h"
#include <QColor>
#include <QGraphicsScene>
#include <QPointF>
#include <QPolygonF>

GraphicsPointFactory::GraphicsPointFactory()
{
}

GraphicsPoint *GraphicsPointFactory::createPoint (QGraphicsScene &scene,
                                                  const QString &identifier,
                                                  const QPointF &posScreen,
                                                  const PointStyle &pointStyle)
{
  GraphicsPoint *item = 0;

  switch (pointStyle.shape ())
  {
    case POINT_SHAPE_CIRCLE:
      {
        item = new GraphicsPoint (scene,
                                  identifier,
                                  posScreen,
                                  ColorPaletteToQColor (pointStyle.paletteColor ()),
                                  pointStyle.radius (),
                                  pointStyle.lineWidth());
      }
      break;

    default:
      {
        item = new GraphicsPoint (scene,
                                  identifier,
                                  posScreen,
                                  ColorPaletteToQColor (pointStyle.paletteColor ()),
                                  pointStyle.polygon (),
                                  pointStyle.lineWidth());
      }
      break;
  }
  
  return item;
}
