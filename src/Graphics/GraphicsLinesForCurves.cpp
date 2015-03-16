#include "Curve.h"
#include "CurveStyles.h"
#include "GraphicsLinesForCurve.h"
#include "GraphicsLinesForCurves.h"
#include "GraphicsPointAbstractBase.h"
#include "GraphicsScene.h"
#include "Logger.h"
#include <QGraphicsItem>
#include "QtToString.h"

GraphicsLinesForCurves::GraphicsLinesForCurves()
{
}

void GraphicsLinesForCurves::savePoint (GraphicsScene &scene,
                                        const QString &curveName,
                                        double ordinal,
                                        GraphicsPoint &point)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurves::savePoint"
                              << " curve=" << curveName.toLatin1().data()
                              << " ordinal=" << ordinal
                              << " pos=" << QPointFToString (point.pos()).toLatin1().data();

  // No lines are drawn for the axis points, other than the axes checker box
  if (curveName != AXIS_CURVE_NAME) {

    if (!m_graphicsLinesForCurve.contains (curveName)) {

      GraphicsLinesForCurve *item = new GraphicsLinesForCurve(curveName);
      scene.addItem (item);

      m_graphicsLinesForCurve [curveName] = item;
    }

    m_graphicsLinesForCurve [curveName]->savePoint (ordinal,
                                                    point);
  }
}

void GraphicsLinesForCurves::updateFinish (const CurveStyles &curveStyles)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurves::updateFinish";

  GraphicsLinesContainer::const_iterator itr;
  for (itr = m_graphicsLinesForCurve.begin (); itr != m_graphicsLinesForCurve.end (); itr++) {

    QString curveName = itr.key();
    GraphicsLinesForCurve *graphicsLines = itr.value();

    graphicsLines->updateFinish (curveStyles.lineStyle (curveName));
  }
}

void GraphicsLinesForCurves::updateStart ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurves::updateStart";

  GraphicsLinesContainer::const_iterator itr;
  for (itr = m_graphicsLinesForCurve.begin (); itr != m_graphicsLinesForCurve.end (); itr++) {

    GraphicsLinesForCurve *graphicsLines = itr.value();

    graphicsLines->updateStart ();
  }
}
