#include "Curve.h"
#include "GraphicsLinesForCurve.h"
#include "GraphicsLinesForCurves.h"
#include "GraphicsScene.h"
#include "Logger.h"
#include <QGraphicsItem>

GraphicsLinesForCurves::GraphicsLinesForCurves()
{
}

void GraphicsLinesForCurves::saveItem (const QString &curveName,
                                       const LineStyle &lineStyle,
                                       int ordinal,
                                       QGraphicsItem *line)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurves::saveItem";

  // No lines are drawn for the axis points, other than the axes checker box
  if (curveName != AXIS_CURVE_NAME) {

    if (!m_graphicsLinesForCurve.contains (curveName)) {
      m_graphicsLinesForCurve [curveName] = new GraphicsLinesForCurve;
    }

    m_graphicsLinesForCurve [curveName]->saveItem (ordinal,
                                                   lineStyle,
                                                   line);
  }
}

void GraphicsLinesForCurves::updateLines (GraphicsScene &scene,
                                          const LineStyles &lineStyles)
{
  GraphicsLinesContainer::const_iterator itr;

  for (itr = m_graphicsLinesForCurve.begin (); itr != m_graphicsLinesForCurve.end (); itr++) {

    const QString curveName = itr.key();
    GraphicsLinesForCurve *graphicsLines = itr.value();

    graphicsLines->updateLines (scene,
                                lineStyles [curveName]);
  }
}
