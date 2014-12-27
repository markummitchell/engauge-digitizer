#include "Checker.h"
#include "EnumsToQt.h"
#include "Logger.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <qmath.h>
#include <QPen>
#include "Transformation.h"

const QString DUMMY_CURVENAME ("dummy");
const int Z_VALUE_IN_FRONT = 100;

// To emphasize that the axis lines are still there, we make these checker somewhat transparent
const double CHECKER_OPACITY = 0.6;

// One-pixel wide line (produced by setting width=0) is too small
const int CHECKER_POINTS_WIDTH = 5;

Checker::Checker(QGraphicsScene &scene) :
  m_scene (scene),
  m_side0 (0),
  m_side1 (0),
  m_side2 (0)
{
}

void Checker::bindItemToScene(QGraphicsItem *item)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "Checker:bindItemToScene";

  item->setOpacity (CHECKER_OPACITY);
  item->setZValue (Z_VALUE_IN_FRONT);
  item->setToolTip (QObject::tr ("Axes checker. If this does not align with the axes, then the axes points should be checked"));

  m_scene.addItem (item);
}

void Checker::createLine (QGraphicsItem *&item,
                          const QPointF &pointFromGraph,
                          const QPointF &pointToGraph,
                          const Transformation &transformation)
{
  QPointF pointFromScreen, pointToScreen;
  transformation.transformInverse (pointFromGraph,
                                   pointFromScreen);
  transformation.transformInverse (pointToGraph,
                                   pointToScreen);

  item = new QGraphicsLineItem (QLineF (pointFromScreen,
                                        pointToScreen));
  bindItemToScene (item);
}

void Checker::deleteLine (QGraphicsItem *&item)
{
  if (item != 0) {
    delete item;
  }

  item = 0;
}

void Checker::createUMissingXSide (double xMissing,
                                   double xKept,
                                   double yMin,
                                   double yMax,
                                   const Transformation &transformation)
{
  createLine (m_side0, QPointF (xMissing, yMin), QPointF (xKept, yMin), transformation);
  createLine (m_side1, QPointF (xKept, yMin), QPointF (xKept, yMax), transformation);
  createLine (m_side2, QPointF (xKept, yMax), QPointF (xMissing, yMax), transformation);
}

void Checker::createUMissingYSide (double xMin,
                                   double xMax,
                                   double yMissing,
                                   double yKept,
                                   const Transformation &transformation)
{
  createLine (m_side0, QPointF (xMin, yMissing), QPointF (xMin, yKept), transformation);
  createLine (m_side1, QPointF (xMin, yKept), QPointF (xMax, yKept), transformation);
  createLine (m_side2, QPointF (xMax, yKept), QPointF (xMax, yMissing), transformation);
}

void Checker::prepareForDisplay (const QPolygonF &polygon,
                                 const DocumentModelAxesChecker &modelAxesChecker,
                                 const DocumentModelCoords &modelCoords)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Checker::prepareForDisplay";

  Q_ASSERT (polygon.count () == 3);

  // Convert pixel coordinates in QPointF to screen and graph coordinates in Point using
  // identity transformation, so this routine can call the general case routine
  QList<Point> points;
  QPolygonF::const_iterator itr;
  for (itr = polygon.begin (); itr != polygon.end (); itr++) {

    QPointF pF = *itr;
    Point p (DUMMY_CURVENAME,
             pF,
             pF);
    points.push_back (p);
  }

  Transformation transformIdentity;
  transformIdentity.identity();
  prepareForDisplay (points,
                     modelAxesChecker,
                     modelCoords,
                     transformIdentity);
}

void Checker::prepareForDisplay (const QList<Point> &points,
                                 const DocumentModelAxesChecker &modelAxesChecker,
                                 const DocumentModelCoords &modelCoords,
                                 const Transformation &transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Checker::prepareForDisplay";

  Q_ASSERT (points.count () == 3);

  // Get the min and max of x and y
  double xMin, xMax, yMin, yMax;
  for (int i = 0; i < 3; i++) {
    if (i == 0) {
      xMin = points.at(i).posGraph().x();
      xMax = points.at(i).posGraph().x();
      yMin = points.at(i).posGraph().y();
      yMax = points.at(i).posGraph().y();
    }
    xMin = qMin (xMin, points.at(i).posGraph().x());
    xMax = qMax (xMax, points.at(i).posGraph().x());
    yMin = qMin (yMin, points.at(i).posGraph().y());
    yMax = qMax (yMax, points.at(i).posGraph().y());
  }

  // Compute the distances of the axes points from the midpoints of each of the four sides
  // of the box bounded by xMin, xMax, yMin and yMax. The side furthest from the axes points will be
  // dropped, with the remaining three sides forming the u shape
  QPointF midXMin (xMin, (yMin + yMax) / 2.0);
  QPointF midXMax (xMax, (yMin + yMax) / 2.0);
  QPointF midYMin ((xMin + xMax) / 2.0, yMin);
  QPointF midYMax ((xMin + xMax) / 2.0, yMax);

  double totalDistanceXMin = (points.at(0).posGraph() - midXMin).manhattanLength() +
                             (points.at(1).posGraph() - midXMin).manhattanLength() +
                             (points.at(2).posGraph() - midXMin).manhattanLength();
  double totalDistanceXMax = (points.at(0).posGraph() - midXMax).manhattanLength() +
                             (points.at(1).posGraph() - midXMax).manhattanLength() +
                             (points.at(2).posGraph() - midXMax).manhattanLength();
  double totalDistanceYMin = (points.at(0).posGraph() - midYMin).manhattanLength() +
                             (points.at(1).posGraph() - midYMin).manhattanLength() +
                             (points.at(2).posGraph() - midYMin).manhattanLength();
  double totalDistanceYMax = (points.at(0).posGraph() - midYMax).manhattanLength() +
                             (points.at(1).posGraph() - midYMax).manhattanLength() +
                             (points.at(2).posGraph() - midYMax).manhattanLength();
  double minTotalDistance = qMin (qMin (qMin (totalDistanceXMin, totalDistanceXMax), totalDistanceYMin), totalDistanceYMax);

  deleteLine (m_side0);
  deleteLine (m_side1);
  deleteLine (m_side2);

  if (minTotalDistance == totalDistanceXMin) {
    createUMissingXSide (xMin, xMax, yMin, yMax, transformation);
  } else if (minTotalDistance == totalDistanceXMax) {
    createUMissingXSide (xMax, xMin, yMin, yMax, transformation);
  } else if (minTotalDistance == totalDistanceYMin) {
    createUMissingYSide (xMin, xMax, yMin, yMax, transformation);
  } else {
    createUMissingYSide (xMin, xMax, yMax, yMin, transformation);
  }

  updateModelAxesChecker (modelAxesChecker);
}

void Checker::setLineColor (QGraphicsItem *item, const QPen &pen)
{
  QGraphicsLineItem *itemLine = dynamic_cast<QGraphicsLineItem*> (item);
  QGraphicsEllipseItem *itemEllipse = dynamic_cast<QGraphicsEllipseItem*> (item);
  if (itemLine == 0) {
    itemEllipse->setPen (pen);
  } else {
    itemLine->setPen (pen);
  }
}

void Checker::setVisible (bool visible)
{
  if (m_side0 != 0) {
    m_side0->setVisible (visible);
    m_side1->setVisible (visible);
    m_side2->setVisible (visible);
  }
}

void Checker::updateModelAxesChecker (const DocumentModelAxesChecker &modelAxesChecker)
{
  QColor color = ColorPaletteToQColor (modelAxesChecker.lineColor());
  QPen pen (QBrush (color), CHECKER_POINTS_WIDTH);

  setLineColor (m_side0, pen);
  setLineColor (m_side1, pen);
  setLineColor (m_side2, pen);
}
