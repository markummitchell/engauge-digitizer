#include "DataKey.h"
#include "EnumsToQt.h"
#include "GraphicsLinesForCurve.h"
#include "GraphicsPoint.h"
#include "GraphicsScene.h"
#include "LineStyle.h"
#include "Logger.h"
#include <QGraphicsItem>
#include <QPen>
#include "QtToString.h"
#include "Spline.h"

using namespace std;

GraphicsLinesForCurve::GraphicsLinesForCurve(const QString &curveName) :
  m_curveName (curveName)
{
}

QPainterPath GraphicsLinesForCurve::drawLinesSmooth ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::drawLinesSmooth";

  QPainterPath path;

  // Prepare spline inputs. The ordinal values may not start at 0 so we iterate with an
  // iterator instead of an index
  vector<double> t;
  vector<SplinePair> xy;
  MapOrdinalToPoint::const_iterator itr;
  for (itr = m_graphicsPoints.begin(); itr != m_graphicsPoints.end(); itr++) {

    double ordinal = itr.key();
    const Point &point = itr.value();

    t.push_back (ordinal);
    xy.push_back (SplinePair (point.posScreen ().x(),
                              point.posScreen ().y()));
  }

  // Spline through points
  Spline spline (t, xy);

  // Drawing from point i-1 to this point i uses the control points from point i-1
  int segmentEndingAtPointI = 0;

  // Create QPainterPath through the points
  bool isFirst = true;
  for (itr = m_graphicsPoints.begin(); itr != m_graphicsPoints.end(); itr++) {

    const Point &point = itr.value();

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

QPainterPath GraphicsLinesForCurve::drawLinesStraight ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::drawLinesStraight";

  QPainterPath path;

  // Create QPainterPath through the points
  bool isFirst = true;
  MapOrdinalToPoint::const_iterator itr;
  for (itr = m_graphicsPoints.begin(); itr != m_graphicsPoints.end(); itr++) {

    const Point &point = *itr;

    if (isFirst) {
      isFirst = false;
      path.moveTo (point.posScreen());
    } else {
      path.lineTo (point.posScreen());
    }
  }

  return path;
}

void GraphicsLinesForCurve::moveLinesWithDraggedPoint (const QString & /* pointIdentifier */,
                                                       int ordinal,
                                                       const QPointF &scenePos)
{
  m_graphicsPoints [ordinal] = Point (m_curveName,
                                      scenePos);
}

void GraphicsLinesForCurve::moveLinesWithDraggedPoints (const LineStyle &lineStyle)
{
  // Draw as either straight or smoothed. The function/relation differences were handled already with ordinals
  QPainterPath path;
  if (lineStyle.curveConnectAs() == CONNECT_AS_FUNCTION_STRAIGHT ||
      lineStyle.curveConnectAs() == CONNECT_AS_RELATION_STRAIGHT) {

    path = drawLinesStraight ();
  } else {
    path = drawLinesSmooth ();
  }

  setPath (path);
}

void GraphicsLinesForCurve::savePoint (double ordinal,
                                       GraphicsPoint &point)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::savePoint"
                              << " curve=" << m_curveName.toLatin1().data()
                              << " ordinal=" << ordinal
                              << " pos=" << QPointFToString (point.pos()).toLatin1().data()
                              << " newPointCount=" << (m_graphicsPoints.count() + 1);

  m_graphicsPoints [ordinal] = Point (m_curveName,
                                      point.pos());
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

void GraphicsLinesForCurve::updateStart ()
{
  m_graphicsPoints.clear();
}
