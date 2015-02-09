#include "DataKey.h"
#include "GraphicsLine.h"
#include "GraphicsLinesForCurve.h"
#include "GraphicsPointAbstractBase.h"
#include "GraphicsScene.h"
#include "LineStyle.h"
#include "Logger.h"
#include <QGraphicsItem>

GraphicsLinesForCurve::GraphicsLinesForCurve()
{
}

void GraphicsLinesForCurve::resetPoints()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::resetPoints";

  // Delete the pointers. The allocated memory is managed elsewhere so no deletion is involved here
  m_graphicsPoints.clear ();
}

void GraphicsLinesForCurve::savePoint (int ordinal,
                                       QGraphicsItem *item,
                                       GraphicsPointAbstractBase *point)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::savePoint";

  m_graphicsItems [ordinal] = item;
  m_graphicsPoints [ordinal] = point;
}

void GraphicsLinesForCurve::updateLines (GraphicsScene &scene,
                                         const LineStyle &lineStyle)
{
  // Loop through successive pairs of points. Since they
  bool isFirst = true;
  int ordinalLast = -1;
  QPointF posLast (0, 0);
  QMap<int, QGraphicsItem*>::iterator itr;
  for (itr = m_graphicsItems.begin (); itr != m_graphicsItems.end (); itr++) {

    int ordinal = itr.key();
    QGraphicsItem *item = itr.value();

    // Get GraphicsPointAbstractBase representation of the same item
    GraphicsPointAbstractBase *point = m_graphicsPoints [ordinal];

    // Points that are involved
    QPointF pos = item->pos ();

    if (isFirst) {

      // Skip line ending at first point
      isFirst = false;

    } else {

      // Connect lines between the ordered points
      GraphicsLine *line = new GraphicsLine (lineStyle);
      line->setLine (QLineF (posLast,
                             pos));
      line->setData (DATA_KEY_ORDINAL_LAST, ordinalLast);
      line->setData (DATA_KEY_ORDINAL, ordinal);

      point->setLineWithPointAsEnd(*line);

      scene.addItem (line);
    }

    // Save values for next ieration of this loop
    ordinalLast = ordinal;
    posLast = pos;
  }
}
