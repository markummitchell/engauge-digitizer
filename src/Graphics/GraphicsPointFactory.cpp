#include "DataKey.h"
#include "EnumsToQt.h"
#include "GraphicsItemType.h"
#include "GraphicsPointCircle.h"
#include "GraphicsPointFactory.h"
#include "GraphicsPointPolygon.h"
#include "PointStyle.h"
#include <QColor>
#include <QPointF>
#include <QPolygonF>

GraphicsPointFactory::GraphicsPointFactory()
{
}

GraphicsPointAbstractBase *GraphicsPointFactory::createPoint (const QString &identifier,
                                                              const QPointF &posScreen,
                                                              const PointStyle &pointStyle)
{
  switch (pointStyle.shape ())
  {
    case POINT_SHAPE_CIRCLE:
      {
        GraphicsPointCircle *item = new GraphicsPointCircle (identifier,
                                                             posScreen,
                                                             ColorPaletteToQColor (pointStyle.paletteColor ()),
                                                             pointStyle.radius (),
                                                             pointStyle.lineWidth());
        item->setToolTip (identifier);
        item->setData (DATA_KEY_GRAPHICS_ITEM_TYPE, GRAPHICS_ITEM_TYPE_POINT);

        return item;
      }

    default:
      {
        GraphicsPointPolygon *item = new GraphicsPointPolygon (identifier,
                                                               posScreen,
                                                               ColorPaletteToQColor (pointStyle.paletteColor ()),
                                                               pointStyle.polygon (),
                                                               pointStyle.lineWidth());

        item->setToolTip (identifier);
        item->setData (DATA_KEY_GRAPHICS_ITEM_TYPE, GRAPHICS_ITEM_TYPE_POINT);

        return item;
      }
  }
}
