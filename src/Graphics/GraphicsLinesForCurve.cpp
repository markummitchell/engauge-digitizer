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
  QMap<double, GraphicsLine*>::iterator itr;
  for (itr = m_graphicsLines.begin (); itr != m_graphicsLines.end (); itr++) {
    GraphicsLine *line = itr.value();
    line->setWanted (false);
  }
}

void GraphicsLinesForCurve::saveLine (GraphicsScene &scene,
                                      double ordinalAssociated,
                                      double ordinalOther,
                                      GraphicsPoint &pointStart,
                                      GraphicsPoint &pointEnd,
                                      const LineStyle &lineStyle)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::saveLine"
                              << " ordinalAssociated=" << ordinalAssociated
                              << " ordinalOther=" << ordinalOther;

  GraphicsLine *line;
  if (!m_graphicsLines.contains (ordinalAssociated)) {

    line = new GraphicsLine (ordinalAssociated,
                             ordinalOther,
                             lineStyle);
    line->moveStart (pointStart.pos ());
    line->moveEnd (pointEnd.pos ());

    m_graphicsLines [ordinalAssociated] = line;

    scene.addItem (line);

  } else {

    // Line already exists, but move its endpoints only if necessary to reduce the chance of flicker
    line = m_graphicsLines [ordinalAssociated];
    if (line->line ().p1 () != pointStart.pos ()) {
      line->moveStart (pointStart.pos ());
    }

    if (line->line ().p2 () != pointEnd.pos ()) {
      line->moveEnd (pointEnd.pos ());
    }
  }

  // Line is wanted
  line->setWanted (true);

  // Bind the two points to this line
  pointStart.setLineWithPointAsStart (line);
  pointEnd.setLineWithPointAsEnd (line);
}

void GraphicsLinesForCurve::updateLines (GraphicsScene &scene)
{
  // Remove unwanted lines
  QMap<double, GraphicsLine*>::iterator itr, itrNext;
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
