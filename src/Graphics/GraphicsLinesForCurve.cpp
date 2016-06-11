/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DataKey.h"
#include "EngaugeAssert.h"
#include "EnumsToQt.h"
#include "GraphicsItemType.h"
#include "GraphicsLinesForCurve.h"
#include "GraphicsPoint.h"
#include "GraphicsScene.h"
#include "LineStyle.h"
#include "Logger.h"
#include "Point.h"
#include "PointStyle.h"
#include <QGraphicsItem>
#include <QMap>
#include <QPen>
#include <QTextStream>
#include "QtToString.h"
#include "Spline.h"
#include "Transformation.h"

using namespace std;

typedef QMap<double, double> XOrThetaToOrdinal;

GraphicsLinesForCurve::GraphicsLinesForCurve(const QString &curveName) :
  m_curveName (curveName)
{
  setData (DATA_KEY_GRAPHICS_ITEM_TYPE,
           GRAPHICS_ITEM_TYPE_LINE);
  setData (DATA_KEY_IDENTIFIER,
           QVariant (m_curveName));
}

GraphicsLinesForCurve::~GraphicsLinesForCurve()
{
  OrdinalToGraphicsPoint::iterator itr;
  for (itr = m_graphicsPoints.begin(); itr != m_graphicsPoints.end(); itr++) {
    GraphicsPoint *point = itr.value();
    delete point;
  }

  m_graphicsPoints.clear();
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

  m_graphicsPoints [ordinal] = &graphicsPoint;
}

QPainterPath GraphicsLinesForCurve::drawLinesSmooth ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::drawLinesSmooth"
                              << " curve=" << m_curveName.toLatin1().data();

  QPainterPath path;

  // Prepare spline inputs. Note that the ordinal values may not start at 0
  vector<double> t;
  vector<SplinePair> xy;
  OrdinalToGraphicsPoint::const_iterator itr;
  for (itr = m_graphicsPoints.begin(); itr != m_graphicsPoints.end(); itr++) {

    double ordinal = itr.key();
    const GraphicsPoint *point = itr.value();

    t.push_back (ordinal);
    xy.push_back (SplinePair (point->pos ().x(),
                              point->pos ().y()));
  }

  // Spline class requires at least one point
  if (xy.size() > 0) {

    // Spline through points
    Spline spline (t, xy);

    // Drawing from point i-1 to this point i uses the control points from point i-1
    int segmentEndingAtPointI = 0;

    // Create QPainterPath through the points
    bool isFirst = true;
    for (itr = m_graphicsPoints.begin(); itr != m_graphicsPoints.end(); itr++) {

      const GraphicsPoint *point = itr.value();

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
  }

  return path;
}

QPainterPath GraphicsLinesForCurve::drawLinesStraight ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::drawLinesStraight"
                              << " curve=" << m_curveName.toLatin1().data();

  QPainterPath path;

  // Create QPainterPath through the points
  bool isFirst = true;
  OrdinalToGraphicsPoint::const_iterator itr;
  for (itr = m_graphicsPoints.begin(); itr != m_graphicsPoints.end(); itr++) {

    const GraphicsPoint *point = itr.value();

    if (isFirst) {
      isFirst = false;
      path.moveTo (point->pos ());
    } else {
      path.lineTo (point->pos ());
    }
  }

  return path;
}

double GraphicsLinesForCurve::identifierToOrdinal (const QString &identifier) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::identifierToOrdinal"
                              << " identifier=" << identifier.toLatin1().data();

  OrdinalToGraphicsPoint::const_iterator itr;
  for (itr = m_graphicsPoints.begin(); itr != m_graphicsPoints.end(); itr++) {

    const GraphicsPoint *point = itr.value();

    if (point->data (DATA_KEY_IDENTIFIER) == identifier) {
      return itr.key();
    }
  }

  ENGAUGE_ASSERT (false);

  return 0;
}

void GraphicsLinesForCurve::lineMembershipPurge (const LineStyle &lineStyle)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::lineMembershipPurge"
                              << " curve=" << m_curveName.toLatin1().data();

  OrdinalToGraphicsPoint::iterator itr, itrNext;
  for (itr = m_graphicsPoints.begin(); itr != m_graphicsPoints.end(); itr = itrNext) {

    itrNext = itr;
    ++itrNext;

    GraphicsPoint *point = *itr;

    if (!point->wanted ()) {

      double ordinal = itr.key ();

      delete point;
      m_graphicsPoints.remove (ordinal);
    }
  }

  // Apply line style
  QPen pen;
  if (lineStyle.paletteColor() == COLOR_PALETTE_TRANSPARENT) {

    pen = QPen (Qt::NoPen);

  } else {

    pen = QPen (QBrush (ColorPaletteToQColor (lineStyle.paletteColor())),
                lineStyle.width());

  }

  setPen (pen);

  updateGraphicsLinesToMatchGraphicsPoints (lineStyle);
}

void GraphicsLinesForCurve::lineMembershipReset ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::lineMembershipReset"
                              << " curve=" << m_curveName.toLatin1().data();

  OrdinalToGraphicsPoint::iterator itr;
  for (itr = m_graphicsPoints.begin(); itr != m_graphicsPoints.end(); itr++) {

    GraphicsPoint *point = itr.value();

    point->reset ();
  }
}

bool GraphicsLinesForCurve::needOrdinalRenumbering () const
{
  // Ordinals should be 0, 1, ...
  bool needRenumbering = false;
  for (int ordinalKeyWanted = 0; ordinalKeyWanted < m_graphicsPoints.count(); ordinalKeyWanted++) {

    double ordinalKeyGot = m_graphicsPoints.keys().at (ordinalKeyWanted);

    // Sanity checks
    ENGAUGE_ASSERT (ordinalKeyGot != Point::UNDEFINED_ORDINAL ());

    if (ordinalKeyWanted != ordinalKeyGot) {
      needRenumbering = true;
      break;
    }
  }

  return needRenumbering;
}

void GraphicsLinesForCurve::printStream (QString indentation,
                                         QTextStream &str) const
{
  DataKey type = (DataKey) data (DATA_KEY_GRAPHICS_ITEM_TYPE).toInt();

  str << indentation << "GraphicsLinesForCurve=" << m_curveName
      << " dataIdentifier=" << data (DATA_KEY_IDENTIFIER).toString().toLatin1().data()
      << " dataType=" << dataKeyToString (type).toLatin1().data() << "\n";

  indentation += INDENTATION_DELTA;

  OrdinalToGraphicsPoint::const_iterator itr;
  for (itr = m_graphicsPoints.begin(); itr != m_graphicsPoints.end(); itr++) {

    double ordinalKey = itr.key();
    const GraphicsPoint *point = itr.value();

    point->printStream (indentation,
                        str,
                        ordinalKey);
  }
}

void GraphicsLinesForCurve::removePoint (double ordinal)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::removePoint"
                              << " point=" << ordinal
                              << " pointCount=" << m_graphicsPoints.count();

  ENGAUGE_ASSERT (m_graphicsPoints.contains (ordinal));
  GraphicsPoint *graphicsPoint = m_graphicsPoints [ordinal];

  m_graphicsPoints.remove (ordinal);

  delete graphicsPoint;
}

void GraphicsLinesForCurve::removeTemporaryPointIfExists()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::removeTemporaryPointIfExists";

  OrdinalToGraphicsPoint::iterator itr;
  for (itr = m_graphicsPoints.begin(); itr != m_graphicsPoints.end(); itr++) {

    GraphicsPoint *graphicsPoint = itr.value();

    m_graphicsPoints.remove (itr.key());

    delete graphicsPoint;

    break;
  }
}

void GraphicsLinesForCurve::renumberOrdinals ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::renumberOrdinals";

  int ordinalKeyWanted;

  // Ordinals should be 0, 1, and so on. Assigning a list to QMap::keys has no effect, so the
  // approach is to copy to a temporary list and then copy back
  QList<GraphicsPoint*> points;
  for (ordinalKeyWanted = 0; ordinalKeyWanted < m_graphicsPoints.count(); ordinalKeyWanted++) {

    GraphicsPoint *graphicsPoint = m_graphicsPoints.values().at (ordinalKeyWanted);
    points << graphicsPoint;
  }

  m_graphicsPoints.clear ();

  for (ordinalKeyWanted = 0; ordinalKeyWanted < points.count(); ordinalKeyWanted++) {

    GraphicsPoint *graphicsPoint = points.at (ordinalKeyWanted);
    m_graphicsPoints [ordinalKeyWanted] = graphicsPoint;
  }
}

void GraphicsLinesForCurve::updateAfterCommand (GraphicsScene &scene,
                                                const PointStyle &pointStyle,
                                                const Point &point)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "GraphicsLinesForCurve::updateAfterCommand"
                               << " curve=" << m_curveName.toLatin1().data()
                               << " pointCount=" << m_graphicsPoints.count();

  GraphicsPoint *graphicsPoint = 0;
  if (m_graphicsPoints.contains (point.ordinal())) {

    graphicsPoint = m_graphicsPoints [point.ordinal()];

    // Due to ordinal renumbering, the coordinates may belong to some other point so we override
    // them for consistent ordinal-position mapping. Updating the identifier also was added for
    // better logging (i.e. consistency between Document and GraphicsScene dumps), but happened
    // to fix a bug with the wrong set of points getting deleted from Cut and Delete
    graphicsPoint->setPos (point.posScreen());
    graphicsPoint->setData (DATA_KEY_IDENTIFIER, point.identifier());

  } else {

    // Point does not exist in scene so create it
    graphicsPoint = scene.createPoint (point.identifier (),
                                       pointStyle,
                                       point.posScreen());
    m_graphicsPoints [point.ordinal ()] = graphicsPoint;

  }

  // Mark point as wanted
  ENGAUGE_CHECK_PTR (graphicsPoint);
  graphicsPoint->setWanted ();
}

void GraphicsLinesForCurve::updateCurveStyle (const CurveStyle &curveStyle)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::updateCurveStyle";

  OrdinalToGraphicsPoint::const_iterator itr;
  for (itr = m_graphicsPoints.begin(); itr != m_graphicsPoints.end(); itr++) {

     GraphicsPoint *point = itr.value();
     point->updateCurveStyle (curveStyle);
  }
}

void GraphicsLinesForCurve::updateGraphicsLinesToMatchGraphicsPoints (const LineStyle &lineStyle)
{
  // LOG4CPP_INFO_S is below

  bool needRenumbering = needOrdinalRenumbering ();
  if (needRenumbering) {

    renumberOrdinals();

  }

  LOG4CPP_INFO_S ((*mainCat)) << "GraphicsLinesForCurve::updateGraphicsLinesToMatchGraphicsPoints"
                              << " numberPoints=" << m_graphicsPoints.count()
                              << " ordinalRenumbering=" << (needRenumbering ? "true" : "false");

  if (lineStyle.curveConnectAs() != CONNECT_SKIP_FOR_AXIS_CURVE) {

    // Draw as either straight or smoothed. The function/relation differences were handled already with ordinals. The
    // Spline algorithm will crash with fewer than three points so it is only called when there are enough points
    QPainterPath path;
    if (lineStyle.curveConnectAs() == CONNECT_AS_FUNCTION_STRAIGHT ||
        lineStyle.curveConnectAs() == CONNECT_AS_RELATION_STRAIGHT ||
        m_graphicsPoints.count () < 3) {

      path = drawLinesStraight ();
    } else {
      path = drawLinesSmooth ();
    }

   setPath (path);
  }
}

void GraphicsLinesForCurve::updatePointOrdinalsAfterDrag (const LineStyle &lineStyle,
                                                          const Transformation &transformation)
{
  CurveConnectAs curveConnectAs = lineStyle.curveConnectAs();

  LOG4CPP_DEBUG_S ((*mainCat)) << "GraphicsLinesForCurve::updateGraphicsLinesToMatchGraphicsPoints"
                               << " curve=" << m_curveName.toLatin1().data()
                               << " curveConnectAs=" << curveConnectAsToString(curveConnectAs).toLatin1().data();

  if (curveConnectAs == CONNECT_AS_FUNCTION_SMOOTH ||
      curveConnectAs == CONNECT_AS_FUNCTION_STRAIGHT) {

    // Make sure ordinals are properly ordered

    // Get a map of x/theta values as keys with point identifiers as the values
    XOrThetaToOrdinal xOrThetaToOrdinal;
    OrdinalToGraphicsPoint::iterator itrP;
    for (itrP = m_graphicsPoints.begin(); itrP != m_graphicsPoints.end(); itrP++) {

       double ordinal = itrP.key();
       const GraphicsPoint *point = itrP.value();

       // Convert screen coordinate to graph coordinates, which gives us x/theta
       QPointF pointGraph;
       transformation.transformScreenToRawGraph(point->pos (),
                                                pointGraph);

       xOrThetaToOrdinal [pointGraph.x()] = ordinal;
    }

    // Loop through the sorted x/theta values. Since QMap is used, the x/theta keys are sorted
    OrdinalToGraphicsPoint temporaryList;
    int ordinalNew = 0;
    XOrThetaToOrdinal::const_iterator itrX;
    for (itrX = xOrThetaToOrdinal.begin(); itrX != xOrThetaToOrdinal.end(); itrX++) {

      double ordinalOld = *itrX;
      GraphicsPoint *point = m_graphicsPoints [ordinalOld];

      temporaryList [ordinalNew++] = point;
    }

    // Copy from temporary back to original map
    m_graphicsPoints.clear();
    for (itrP = temporaryList.begin(); itrP != temporaryList.end(); itrP++) {

      double ordinal = itrP.key();
      GraphicsPoint *point = itrP.value();

      m_graphicsPoints [ordinal] = point;
    }
  }
}
