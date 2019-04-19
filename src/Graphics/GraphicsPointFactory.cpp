/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DataKey.h"
#include "EnumsToQt.h"
#include "GeometryWindow.h"
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
                                                  const PointStyle &pointStyle,
                                                  GeometryWindow *geometryWindow)
{
  GraphicsPoint *item = nullptr;

  switch (pointStyle.shape ())
  {
    case POINT_SHAPE_CIRCLE:
      {
        item = new GraphicsPoint (scene,
                                  identifier,
                                  posScreen,
                                  ColorPaletteToQColor (pointStyle.paletteColor ()),
                                  unsigned (pointStyle.radius ()),
                                  pointStyle.lineWidth(),
                                  geometryWindow);
      }
      break;

    default:
      {
        item = new GraphicsPoint (scene,
                                  identifier,
                                  posScreen,
                                  ColorPaletteToQColor (pointStyle.paletteColor ()),
                                  pointStyle.polygon (),
                                  pointStyle.lineWidth(),
                                  geometryWindow);
      }
      break;
  }
  
  return item;
}
