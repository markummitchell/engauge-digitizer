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

  // Mark all points as unwanted.
  QMap<int, GraphicsLine*>::iterator itr;
  for (itr = m_graphicsLines.begin (); itr != m_graphicsLines.end (); itr++) {
    GraphicsLine *line = itr.value();
    line->setWanted (false);
  }
}

void GraphicsLinesForCurve::saveLine (GraphicsScene &scene,
                                      int ordinalLow,
                                      const GraphicsPoint &pointLow,
                                      const GraphicsPoint &pointHigh,
                                      const LineStyle &lineStyle)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::saveLine";

  GraphicsLine *line;
  if (!m_graphicsLines.contains (ordinalLow)) {

    line = new GraphicsLine (lineStyle);
    line->moveStart (pointLow.pos ());
    line->moveEnd (pointHigh.pos ());

    m_graphicsLines [ordinalLow] = line;

    scene.addItem (line);

  } else {

    // Line already exists, but move its endpoints only if necessary to reduce the chance of flicker
    line = m_graphicsLines [ordinalLow];
    if (line->line ().p1 () != pointLow.pos ()) {
      line->moveStart (pointLow.pos ());
    }

    if (line->line ().p2 () != pointHigh.pos ()) {
      line->moveEnd (pointHigh.pos ());
    }
  }

  line->setWanted (true);
}

void GraphicsLinesForCurve::updateLines (GraphicsScene &scene)
{
  // Remove unwanted lines
  QMap<int, GraphicsLine*>::iterator itr, itrNext;
  for (itr = m_graphicsLines.begin (); itr != m_graphicsLines.end (); itr = itrNext) {

    // Save next iterator value in case we remove entry itr
    itrNext = itr;
    itrNext++;

    // Get line from map
    GraphicsLine *line = itr.value();

    if (!line->wanted ()) {

      scene.removeItem (line);
      m_graphicsLines.erase (itr);
    }
  }
}
