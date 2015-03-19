#include "DataKey.h"
#include "EnumsToQt.h"
#include "GraphicsLinesForCurve.h"
#include "GraphicsPoint.h"
#include "GraphicsScene.h"
#include "LineStyle.h"
#include "Logger.h"
#include "Point.h"
#include <QGraphicsItem>
#include <QMap>
#include <QPen>
#include "QtToString.h"
#include "Spline.h"

using namespace std;

typedef QMap<double, QString> XOrThetaToPointIdentifier;

GraphicsLinesForCurve::GraphicsLinesForCurve(const QString &curveName) :
  m_curveName (curveName)
{
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
    const Point &point = m_graphicsPoints [pointIdentifier];

    t.push_back (point.ordinal ());
    xy.push_back (SplinePair (point.posScreen ().x(),
                              point.posScreen ().y()));
  }

  // Spline through points
  Spline spline (t, xy);

  // Drawing from point i-1 to this point i uses the control points from point i-1
  int segmentEndingAtPointI = 0;

  // Create QPainterPath through the points
  bool isFirst = true;
  for (itr = ordinalToPointIdentifier.begin(); itr != ordinalToPointIdentifier.end(); itr++) {

    const QString pointIdentifier = itr.value();
    const Point &point = m_graphicsPoints [pointIdentifier];

    if (isFirst) {
      isFirst = false;
      path.moveTo (point.posScreen());
    } else {

      QPointF p1 (spline.p1 (segmentEndingAtPointI).x(),
                  spline.p1 (segmentEndingAtPointI).y());
      QPointF p2 (spline.p2 (segmentEndingAtPointI).x(),
                  spline.p2 (segmentEndingAtPointI).y());

      path.cubicTo (p1,
                    p2,
                    point.posScreen());

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
    const Point &point = m_graphicsPoints [pointIdentifier];

    if (isFirst) {
      isFirst = false;
      path.moveTo (point.posScreen());
    } else {
      path.lineTo (point.posScreen());
    }
  }

  return path;
}

void GraphicsLinesForCurve::moveLinesWithDraggedPoint (const QString &pointIdentifier,
                                                       const QPointF &scenePos)
{
  Point pointOld = m_graphicsPoints [pointIdentifier];
  double ordinal = pointOld.ordinal();

  // Replace existing entry if there is one, with a proxy Point for the one in the Document. Steal the
  // ordinal value from the old Point
  Point point (pointIdentifier,
               ordinal,
               scenePos);

  m_graphicsPoints [pointIdentifier] = point;
}

void GraphicsLinesForCurve::moveLinesWithDraggedPoints (const LineStyle &lineStyle)
{
  OrdinalToPointIdentifier ordinalToPointIdentifier;

  // Order by ordinals locally
  PointIdentifierToPoint::const_iterator itr;
  for (itr = m_graphicsPoints.begin(); itr != m_graphicsPoints.end(); itr++) {

    const Point &point = *itr;
    ordinalToPointIdentifier [point.ordinal ()] = point.identifier ();

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

void GraphicsLinesForCurve::savePoint (const QString &pointIdentifier,
                                       double ordinal,
                                       GraphicsPoint &graphicsPoint)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::savePoint"
                              << " curve=" << m_curveName.toLatin1().data()
                              << " identifier=" << pointIdentifier.toLatin1().data()
                              << " ordinal=" << ordinal
                              << " pos=" << QPointFToString (graphicsPoint.pos()).toLatin1().data()
                              << " newPointCount=" << (m_graphicsPoints.count() + 1);

  // Replace existing entry if there is one, with a proxy Point for the one in the Document
  Point point (pointIdentifier,
               ordinal,
               graphicsPoint.pos());

  m_graphicsPoints [pointIdentifier] = point;
}

void GraphicsLinesForCurve::updateFinish (const LineStyle &lineStyle)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::updateFinish";

  // Apply line style
  QPen pen = QPen (QBrush (ColorPaletteToQColor (lineStyle.paletteColor())),
                   lineStyle.width());
  setPen (pen);

  moveLinesWithDraggedPoints (lineStyle);
}

void GraphicsLinesForCurve::updateOrdinalsAfterDrag (const LineStyle &lineStyle)
{
  if (lineStyle.curveConnectAs() == CONNECT_AS_FUNCTION_SMOOTH ||
      lineStyle.curveConnectAs() == CONNECT_AS_FUNCTION_STRAIGHT) {

    // Make sure ordinals are properly ordered

    // Get a map of x/theta values as keys with point identifiers as the values
    XOrThetaToPointIdentifier xOrThetaToPointIdentifier;
    PointIdentifierToPoint::iterator itrP;
    for (itrP = m_graphicsPoints.begin(); itrP != m_graphicsPoints.end(); itrP++) {

       QString pointIdentifier = itrP.key();
       const Point &point = itrP.value();

       xOrThetaToPointIdentifier [point.posScreen().x()] = pointIdentifier;
    }

    // Loop through the sorted x/theta values. Since QMap is used, the x/theta keys are sorted
    int ordinal = 0;
    XOrThetaToPointIdentifier::const_iterator itrX;
    for (itrX = xOrThetaToPointIdentifier.begin(); itrX != xOrThetaToPointIdentifier.end(); itrX++) {

      QString pointIdentifier = itrX.value();
      Point &point = m_graphicsPoints [pointIdentifier];

      point.setOrdinal (ordinal++); // Override the old ordinal
    }
  }
}

void GraphicsLinesForCurve::updateStart ()
{
  m_graphicsPoints.clear();
}
