#include "DataKey.h"
#include "GraphicsLine.h"
#include "GraphicsLinesForCurve.h"
#include "GraphicsPoint.h"
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
                                       GraphicsPoint *point)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::savePoint";

  m_graphicsPoints [ordinal] = point;
}

void GraphicsLinesForCurve::updateLines (GraphicsScene &scene,
                                         const LineStyle &lineStyle)
{
  // Loop through successive pairs of points. Since they
  bool isFirst = true;
  int ordinalLast = -1;
  QPointF posLast (0, 0);
  QMap<int, GraphicsPoint*>::iterator itr;
  for (itr = m_graphicsPoints.begin (); itr != m_graphicsPoints.end (); itr++) {

    int ordinal = itr.key();
    GraphicsPoint *point = itr.value();

    // Points that are involved
    QPointF pos = point->pos ();

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
