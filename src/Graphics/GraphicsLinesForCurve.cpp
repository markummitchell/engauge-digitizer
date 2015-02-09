#include "GraphicsLine.h"
#include "GraphicsLinesForCurve.h"
#include "GraphicsScene.h"
#include "LineStyle.h"
#include "Logger.h"
#include <QGraphicsItem>

GraphicsLinesForCurve::GraphicsLinesForCurve()
{
}

void GraphicsLinesForCurve::saveItem (int ordinal,
                                      const LineStyle &lineStyle,
                                      QGraphicsItem *line)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::saveItem";

  if (!m_graphicsLines.contains (ordinal)) {
    m_graphicsLines [ordinal] = new GraphicsLine (lineStyle);
  }

  m_graphicsLines [ordinal] = line;
}

void GraphicsLinesForCurve::updateLines (GraphicsScene &scene,
                                         const LineStyle &lineStyle)
{
  // Loop through successive pairs of points
  bool isFirst = true;
  QPointF posLast (0, 0);
  QMap<int, QGraphicsItem*>::iterator itr;
  for (itr = m_graphicsLines.begin (); itr != m_graphicsLines.end (); itr++) {

    QGraphicsItem *item = *itr;

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

      scene.addItem (line);
    }

    posLast = pos;
  }
}
