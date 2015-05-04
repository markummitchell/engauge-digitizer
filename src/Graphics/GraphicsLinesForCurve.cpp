#include "DataKey.h"
#include "EngaugeAssert.h"
#include "EnumsToQt.h"
#include "GraphicsLinesForCurve.h"
#include "GraphicsPoint.h"
#include "GraphicsScene.h"
#include "LineStyle.h"
#include "Logger.h"
#include "PointStyle.h"
#include <QGraphicsItem>
#include <QMap>
#include <QPen>
#include <QTextStream>
#include "QtToString.h"
#include "Spline.h"
#include "Transformation.h"

using namespace std;

typedef QMap<double, QString> XOrThetaToPointIdentifier;

GraphicsLinesForCurve::GraphicsLinesForCurve(const QString &curveName) :
  m_curveName (curveName)
{
}

void GraphicsLinesForCurve::addPoint (const QString &pointIdentifier,
                                      double ordinal,
                                      GraphicsPoint &graphicsPoint)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::addPoint"
                              << " curve=" << m_curveName.toLatin1().data()
                              << " identifier=" << pointIdentifier.toLatin1().data()
                              << " ordinal=" << ordinal
                              << " pos=" << QPointFToString (graphicsPoint.pos()).toLatin1().data()
                              << " newPointCount=" << (m_graphicsPoints.count() + 1);

  m_graphicsPoints [pointIdentifier] = &graphicsPoint;
}

QPainterPath GraphicsLinesForCurve::drawLinesSmooth (const OrdinalToPointIdentifier &ordinalToPointIdentifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::drawLinesSmooth";

  QPainterPath path;

  // Prepare spline inputs. Note that the ordinal values may not start at 0
  vector<double> t;
  vector<SplinePair> xy;
  OrdinalToPointIdentifier::const_iterator itr;
  for (itr = ordinalToPointIdentifier.begin(); itr != ordinalToPointIdentifier.end(); itr++) {

    const QString pointIdentifier = itr.value();
    const GraphicsPoint *point = m_graphicsPoints [pointIdentifier];

    t.push_back (point->data (DATA_KEY_ORDINAL).toDouble ());
    xy.push_back (SplinePair (point->pos ().x(),
                              point->pos ().y()));
  }

  // Spline through points
  Spline spline (t, xy);

  // Drawing from point i-1 to this point i uses the control points from point i-1
  int segmentEndingAtPointI = 0;

  // Create QPainterPath through the points
  bool isFirst = true;
  for (itr = ordinalToPointIdentifier.begin(); itr != ordinalToPointIdentifier.end(); itr++) {

    const QString pointIdentifier = itr.value();
    const GraphicsPoint *point = m_graphicsPoints [pointIdentifier];

    if (isFirst) {
      isFirst = false;
      path.moveTo (point->pos());
    } else {

      QPointF p1 (spline.p1 (segmentEndingAtPointI).x(),
                  spline.p1 (segmentEndingAtPointI).y());
      QPointF p2 (spline.p2 (segmentEndingAtPointI).x(),
                  spline.p2 (segmentEndingAtPointI).y());

      path.cubicTo (p1,
                    p2,
                    point->pos ());

      ++segmentEndingAtPointI;
    }
  }

  return path;
}

QPainterPath GraphicsLinesForCurve::drawLinesStraight (const OrdinalToPointIdentifier &ordinalToPointIdentifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::drawLinesStraight";

  QPainterPath path;

  // Create QPainterPath through the points
  bool isFirst = true;
  OrdinalToPointIdentifier::const_iterator itr;
  for (itr = ordinalToPointIdentifier.begin(); itr != ordinalToPointIdentifier.end(); itr++) {

    const QString pointIdentifier = itr.value();
    const GraphicsPoint *point = m_graphicsPoints [pointIdentifier];

    if (isFirst) {
      isFirst = false;
      path.moveTo (point->pos ());
    } else {
      path.lineTo (point->pos ());
    }
  }

  return path;
}

void GraphicsLinesForCurve::lineMembershipPurge (const LineStyle &lineStyle)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::lineMembershipPurge";

  PointIdentifierToGraphicsPoint::iterator itr;
  for (itr = m_graphicsPoints.begin(); itr != m_graphicsPoints.end(); itr++) {

    GraphicsPoint *point = *itr;

    if (!point->wanted ()) {

      const QString pointIdentifier = itr.key ();

      delete point;
      m_graphicsPoints.remove (pointIdentifier);
    }
  }

  // Apply line style
  QPen pen = QPen (QBrush (ColorPaletteToQColor (lineStyle.paletteColor())),
                   lineStyle.width());
  setPen (pen);

  updateGraphicsLinesToMatchGraphicsPoints (lineStyle);
}

void GraphicsLinesForCurve::lineMembershipReset ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::lineMembershipReset";

  PointIdentifierToGraphicsPoint::iterator itr;
  for (itr = m_graphicsPoints.begin(); itr != m_graphicsPoints.end(); itr++) {

    GraphicsPoint *point = *itr;

    point->reset ();
  }
}

void GraphicsLinesForCurve::printStream (QTextStream &str) const
{
  str << "curve name: " << m_curveName << endl;

  PointIdentifierToGraphicsPoint::const_iterator itr;
  for (itr = m_graphicsPoints.begin(); itr != m_graphicsPoints.end(); itr++) {

    const GraphicsPoint *point = *itr;

    point->printStream (str);
  }
}

void GraphicsLinesForCurve::removePoint (const QString &pointIdentifier)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::removePoint"
                              << " point=" << pointIdentifier.toLatin1().data();

  ENGAUGE_ASSERT (m_graphicsPoints.contains (pointIdentifier));
  GraphicsPoint *graphicsPoint = m_graphicsPoints [pointIdentifier];

  m_graphicsPoints.remove (pointIdentifier);

  delete graphicsPoint;
}

void GraphicsLinesForCurve::updateAfterCommand (GraphicsScene &scene,
                                                const PointStyle &pointStyle,
                                                const Point &point)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::updateAfterCommand";

  GraphicsPoint *graphicsPoint = 0;
  if (m_graphicsPoints.contains (point.identifier())) {

    graphicsPoint = m_graphicsPoints [point.identifier()];

  } else {

    // Point does not exist in scene so create it
    graphicsPoint = scene.addPoint (point.identifier (),
                                    pointStyle,
                                    point.posScreen());
  }

  // Mark point as wanted
  ENGAUGE_CHECK_PTR (graphicsPoint);
  graphicsPoint->setWanted ();
}

void GraphicsLinesForCurve::updateGraphicsLinesToMatchGraphicsPoints (const LineStyle &lineStyle)
{
  OrdinalToPointIdentifier ordinalToPointIdentifier;

  // Order by ordinals locally
  PointIdentifierToGraphicsPoint::const_iterator itr;
  for (itr = m_graphicsPoints.begin(); itr != m_graphicsPoints.end(); itr++) {

    const GraphicsPoint *point = *itr;
    double ordinal = point->data (DATA_KEY_ORDINAL).toDouble();
    ordinalToPointIdentifier [ordinal] = point->data (DATA_KEY_IDENTIFIER).toString();

  }

  // Draw as either straight or smoothed. The function/relation differences were handled already with ordinals. The
  // Spline algorithm will crash with fewer than three points so it is only called when there are enough points
  QPainterPath path;
  if (lineStyle.curveConnectAs() == CONNECT_AS_FUNCTION_STRAIGHT ||
      lineStyle.curveConnectAs() == CONNECT_AS_RELATION_STRAIGHT ||
      m_graphicsPoints.count () < 3) {

    path = drawLinesStraight (ordinalToPointIdentifier);
  } else {
    path = drawLinesSmooth (ordinalToPointIdentifier);
  }

  setPath (path);
}

void GraphicsLinesForCurve::updatePointOrdinalsAfterDrag (const LineStyle &lineStyle,
                                                          const Transformation &transformation)
{
  if (lineStyle.curveConnectAs() == CONNECT_AS_FUNCTION_SMOOTH ||
      lineStyle.curveConnectAs() == CONNECT_AS_FUNCTION_STRAIGHT) {

    // Make sure ordinals are properly ordered

    // Get a map of x/theta values as keys with point identifiers as the values
    XOrThetaToPointIdentifier xOrThetaToPointIdentifier;
    PointIdentifierToGraphicsPoint::iterator itrP;
    for (itrP = m_graphicsPoints.begin(); itrP != m_graphicsPoints.end(); itrP++) {

       QString pointIdentifier = itrP.key();
       const GraphicsPoint *pointScreen = itrP.value();

       // Convert screen coordinate to graph coordinates, which gives us x/theta
       QPointF pointGraph;
       transformation.transformScreenToRawGraph(pointScreen->pos (),
                                                pointGraph);

       xOrThetaToPointIdentifier [pointGraph.x()] = pointIdentifier;
    }

    // Loop through the sorted x/theta values. Since QMap is used, the x/theta keys are sorted
    int ordinal = 0;
    XOrThetaToPointIdentifier::const_iterator itrX;
    for (itrX = xOrThetaToPointIdentifier.begin(); itrX != xOrThetaToPointIdentifier.end(); itrX++) {

      QString pointIdentifier = itrX.value();
      GraphicsPoint *point = m_graphicsPoints [pointIdentifier];

      point->setData (DATA_KEY_ORDINAL, QVariant (ordinal++)); // Override the old ordinal
    }
  }
}
