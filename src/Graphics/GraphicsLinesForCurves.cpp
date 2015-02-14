#include "Curve.h"
#include "GraphicsLinesForCurve.h"
#include "GraphicsLinesForCurves.h"
#include "GraphicsPointAbstractBase.h"
#include "GraphicsScene.h"
#include "Logger.h"
#include <QGraphicsItem>

GraphicsLinesForCurves::GraphicsLinesForCurves()
{
}

void GraphicsLinesForCurves::resetPoints ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurves::resetPoints";

  GraphicsLinesContainer::const_iterator itr;

  for (itr = m_graphicsLinesForCurve.begin (); itr != m_graphicsLinesForCurve.end (); itr++) {

    GraphicsLinesForCurve *graphicsLines = itr.value();
    graphicsLines->resetPoints ();
  }
}

void GraphicsLinesForCurves::saveLine (GraphicsScene &scene,
                                       const QString &curveName,
                                       double ordinalAssociated,
                                       double ordinalOther,
                                       const GraphicsPoint &pointLow,
                                       const GraphicsPoint &pointHigh,
                                       const LineStyle &lineStyle)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurves::saveLine"
                              << " curve=" << curveName.toLatin1().data()
                              << " ordinalAssociated=" << ordinalAssociated
                              << " ordinalOther=" << ordinalOther;

  // No lines are drawn for the axis points, other than the axes checker box
  if (curveName != AXIS_CURVE_NAME) {

    if (!m_graphicsLinesForCurve.contains (curveName)) {
      m_graphicsLinesForCurve [curveName] = new GraphicsLinesForCurve;
    }

    m_graphicsLinesForCurve [curveName]->saveLine (scene,
                                                   ordinalAssociated,
                                                   ordinalOther,
                                                   pointLow,
                                                   pointHigh,
                                                   lineStyle);
  }
}

void GraphicsLinesForCurves::updateLines (GraphicsScene &scene)
{
  GraphicsLinesContainer::const_iterator itr;
  for (itr = m_graphicsLinesForCurve.begin (); itr != m_graphicsLinesForCurve.end (); itr++) {

    const QString curveName = itr.key();
    GraphicsLinesForCurve *graphicsLines = itr.value();

    graphicsLines->updateLines (scene);
  }
}
