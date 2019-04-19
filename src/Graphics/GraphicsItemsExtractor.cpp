/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Curve.h"
#include "DataKey.h"
#include "GraphicsItemsExtractor.h"
#include "GraphicsItemType.h"
#include "Logger.h"
#include "Point.h"
#include <QGraphicsItem>

GraphicsItemsExtractor::GraphicsItemsExtractor()
{
}

GraphicsItemsExtractor::~GraphicsItemsExtractor()
{
}

bool GraphicsItemsExtractor::allSelectedItemsAreEitherAxisOrGraph (const QList<QGraphicsItem*> &items,
                                                                   AxisOrGraph axisOrGraph) const
{
  bool allAreEitherAxisOrGraph = true;

  QList<QGraphicsItem*>::const_iterator itr;
  for (itr = items.begin(); itr != items.end(); itr++) {

    QGraphicsItem *item = *itr;
    GraphicsItemType type = static_cast<GraphicsItemType> (item->data (DATA_KEY_GRAPHICS_ITEM_TYPE).toInt ());

    if (type == GRAPHICS_ITEM_TYPE_POINT) {

      QString pointIdentifier = item->data (DATA_KEY_IDENTIFIER).toString ();
      QString curveName = Point::curveNameFromPointIdentifier (pointIdentifier);

      bool unwantedAxisPoint = ((curveName == AXIS_CURVE_NAME) && (axisOrGraph == GRAPH_POINTS));
      bool unwantedCurvePoint = ((curveName != AXIS_CURVE_NAME) && (axisOrGraph == AXIS_POINTS));

      if (unwantedAxisPoint || unwantedCurvePoint) {

        allAreEitherAxisOrGraph = false;
        break;

      }
    } else {

      allAreEitherAxisOrGraph = false;
      break;

    }
  }

  return allAreEitherAxisOrGraph;
}

QStringList GraphicsItemsExtractor::selectedPointIdentifiers (const QList<QGraphicsItem*> &items) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsScene::selectedPointIdentifiers"
                              << " selectedItems=" << items.count();

  QStringList selectedIds;
  QList<QGraphicsItem*>::const_iterator itr;
  for (itr = items.begin(); itr != items.end(); itr++) {

    const QGraphicsItem* item = *itr;

    // Skip the image and only keep the Points
    bool isPoint = (item->data (DATA_KEY_GRAPHICS_ITEM_TYPE).toInt () == GRAPHICS_ITEM_TYPE_POINT);
    if (isPoint) {

      // Add Point to the list
      selectedIds << item->data(DATA_KEY_IDENTIFIER).toString ();

    }
  }

  return  selectedIds;
}
