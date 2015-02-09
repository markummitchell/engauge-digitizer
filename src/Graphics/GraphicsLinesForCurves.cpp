#include "GraphicsLinesForCurve.h"
#include "GraphicsLinesForCurves.h"
#include "GraphicsScene.h"
#include "Logger.h"
#include <QGraphicsItem>

GraphicsLinesForCurves::GraphicsLinesForCurves()
{
}

void GraphicsLinesForCurves::saveItem (const QString &curveName,
                                       int ordinal,
                                       QGraphicsItem *line)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurves::saveItem";

  if (!m_graphicsLinesForCurve.contains (curveName)) {
    m_graphicsLinesForCurve [curveName] = new GraphicsLinesForCurve;
  }

  m_graphicsLinesForCurve [curveName]->saveItem (ordinal,
                                                 line);
}

void GraphicsLinesForCurves::updateLines (GraphicsScene &scene)
{
}
