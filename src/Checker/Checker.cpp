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

void Checker::loadAxesPointToSideConnectivity (const QList<Point> points,
                                               double xMin,
                                               double xMax,
                                               double yMin,
                                               double yMax,
                                               Connectivity axesPointToSideConnectivity [NUM_AXES_POINTS] [NUM_SIDES])
{
  // Point is on a side if it is closer than the distance between two tic marks
  const double MAX_NUMBER_OF_TICS = 20.0;
  double xEpsilon = (xMax - xMin) / MAX_NUMBER_OF_TICS;
  double yEpsilon = (yMax - yMin) / MAX_NUMBER_OF_TICS;

  for (int i = 0; i < NUM_AXES_POINTS; i++) {
    for (int side = 0; side < NUM_SIDES; side++) {

      bool connected;
      switch (side) {
        case SIDE_BOTTOM:
          connected= (qAbs (points.at(i).posGraph().y() - yMin) < yEpsilon);
          break;

        case SIDE_LEFT:
          connected = (qAbs (points.at(i).posGraph().x() - xMin) < xEpsilon);
          break;

        case SIDE_RIGHT:
          connected = (qAbs (points.at(i).posGraph().y() - yMax) < yEpsilon);
          break;

        case SIDE_TOP:
          connected = (qAbs (points.at(i).posGraph().x() - xMax) < xEpsilon);
          break;

        default:
          Q_ASSERT (false);
      }

      axesPointToSideConnectivity [i] [side] = (connected ?
                                                  CONNECTIVITY_NOT_ALONG_SIDE :
                                                  CONNECTIVITY_ALONG_SIDE_UNASSIGNED);
    }
  }
}

void Checker::markSideAsAssigned (Side side,
                                  Connectivity axesPointToSideConnectivity [NUM_AXES_POINTS] [NUM_SIDES])
{
  for (int i = 0; i < NUM_SIDES; i++) {
    if (axesPointToSideConnectivity [i] [side] == CONNECTIVITY_ALONG_SIDE_UNASSIGNED) {
      axesPointToSideConnectivity [i] [side] = CONNECTIVITY_ALONG_SIDE_ASSIGNED;
    }
  }
}

int Checker::nextSide (const Connectivity axesPointToSideConnectivity [NUM_AXES_POINTS] [NUM_SIDES])
{
  const double FOM_DELTA_FOR_UNASSIGNED = 1.0;
  const double FOM_DELTA_FOR_ASSIGNED = 0.1;

  // As a clever figure of merit, we define a figure of merit for each side that has the number of
  // unconnected points as the integer part, and the number of connected points as the tenths decimal.
  // This gives preference to the side with more connected points, when two sides have the same
  // number of unconnected points
  double fomMax = 0;
  int sideMax = -1; // Value that is returned if no unassigned points are found
  for (int side = 0; side < NUM_SIDES; side++) {
    double fom = 0;
    for (int i = 0; i < NUM_AXES_POINTS; i++) {
      if (axesPointToSideConnectivity [i] [side] == CONNECTIVITY_ALONG_SIDE_UNASSIGNED) {
        fom += FOM_DELTA_FOR_UNASSIGNED;
      } else if (axesPointToSideConnectivity [i] [side] == CONNECTIVITY_ALONG_SIDE_ASSIGNED) {
        fom += FOM_DELTA_FOR_ASSIGNED;
      }
    }

    if ((fom > fomMax) && (fom >= FOM_DELTA_FOR_UNASSIGNED)) {
      fomMax = fom;
      sideMax = side;
    }
  }

  return sideMax;
}

void Checker::prepareForDisplay (const QPolygonF &polygon,
                                 const DocumentModelAxesChecker &modelAxesChecker,
                                 const DocumentModelCoords &modelCoords)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Checker::prepareForDisplay";

  Q_ASSERT (polygon.count () == NUM_AXES_POINTS);

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

  Q_ASSERT (points.count () == NUM_AXES_POINTS);

  deleteLine (m_side0);
  deleteLine (m_side1);
  deleteLine (m_side2);

  // Get the min and max of x and y
  double xMin, xMax, yMin, yMax;
  int i;
  for (i = 0; i < 3; i++) {
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

  // Match up each axes point with the one or two sides it lies along
  Connectivity axesPointToSideConnectivity [NUM_AXES_POINTS] [NUM_SIDES];
  loadAxesPointToSideConnectivity (points,
                                   xMin,
                                   xMax,
                                   yMin,
                                   yMax,
                                   axesPointToSideConnectivity);

  // Greedy algorithm to assign axes points to sides. We use a minimum number of sides
  int sideCount = 0;
  int nextS;
  while ((nextS = nextSide (axesPointToSideConnectivity)) >= 0) {

    markSideAsAssigned ((Side) nextS,
                        axesPointToSideConnectivity);

    QPointF p1, p2;
    switch (nextS) {
      case SIDE_BOTTOM:
        p1 = QPointF (xMin, yMin);
        p2 = QPointF (xMax, yMin);
        break;

      case SIDE_LEFT:
        p1 = QPointF (xMin, yMin);
        p2 = QPointF (xMin, yMax);
        break;

      case SIDE_RIGHT:
        p1 = QPointF (xMax, yMin);
        p2 = QPointF (xMax, yMax);
        break;

      case SIDE_TOP:
        p1 = QPointF (xMin, yMax);
        p2 = QPointF (xMax, yMax);
        break;
    }

    switch (sideCount++) {
      case 0:
        createLine (m_side0, p1, p2, transformation);
        break;

      case 1:
        createLine (m_side1, p1, p2, transformation);
        break;

      case 2:
        createLine (m_side2, p1, p2, transformation);
    }
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
