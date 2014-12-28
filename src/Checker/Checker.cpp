#include "Checker.h"
#include "EnumsToQt.h"
#include "Logger.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <qmath.h>
#include <QPen>
#include <QTextStream>
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
  m_side2 (0),
  m_side3 (0)
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

QString Checker::connectivityString (Connectivity connectivity)
{
  switch (connectivity) {
    case CONNECTIVITY_NOT_ALONG_SIDE:
      return "NotAlongSide       ";
      break;

    case CONNECTIVITY_ALONG_SIDE_UNASSIGNED:
      return "AlongSideUnassigned";
      break;

    case CONNECTIVITY_ALONG_SIDE_ASSIGNED:
      return "AlongSideAssigned  ";
      break;
  }

  return "";
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
          connected = (qAbs (points.at(i).posGraph().x() - xMax) < xEpsilon);
          break;

        case SIDE_TOP:
          connected = (qAbs (points.at(i).posGraph().y() - yMax) < yEpsilon);
          break;

        default:
          Q_ASSERT (false);
      }

      axesPointToSideConnectivity [i] [side] = (connected ?
                                                  CONNECTIVITY_ALONG_SIDE_UNASSIGNED :
                                                  CONNECTIVITY_NOT_ALONG_SIDE);
    }
  }
}

void Checker::markSideAsAssigned (Side sideAssigned,
                                  Connectivity axesPointToSideConnectivity [NUM_AXES_POINTS] [NUM_SIDES])
{
  // Search for points that are unassigned for this side
  for (int i = 0; i < NUM_AXES_POINTS; i++) {
    if (axesPointToSideConnectivity [i] [sideAssigned] == CONNECTIVITY_ALONG_SIDE_UNASSIGNED) {

      // Mark this point as assigned for all sides that are currently unassigned, so it never gets processed again
      for (int side = 0; side < NUM_SIDES; side++) {
        axesPointToSideConnectivity [i] [side] = CONNECTIVITY_ALONG_SIDE_ASSIGNED;
      }
    }
  }
}

int Checker::nextSide (const Connectivity axesPointToSideConnectivity [NUM_AXES_POINTS] [NUM_SIDES],
                       bool isBottom,
                       bool isLeft,
                       bool isTop,
                       bool isRight)
{
  const int NO_SIDE = -1;

  // Output the current connectivity table to the log file
  QString table;
  QTextStream str (&table);
  str << "         i=0 i=1 i=2\n";
  str << "bottom " << connectivityString (axesPointToSideConnectivity [0] [SIDE_BOTTOM]) << " "
                   << connectivityString (axesPointToSideConnectivity [1] [SIDE_BOTTOM]) << " "
                   << connectivityString (axesPointToSideConnectivity [2] [SIDE_BOTTOM]) << "\n";
  str << "left   " << connectivityString (axesPointToSideConnectivity [0] [SIDE_LEFT  ]) << " "
                   << connectivityString (axesPointToSideConnectivity [1] [SIDE_LEFT  ]) << " "
                   << connectivityString (axesPointToSideConnectivity [2] [SIDE_LEFT  ]) << "\n";
  str << "top    " << connectivityString (axesPointToSideConnectivity [0] [SIDE_TOP   ]) << " "
                   << connectivityString (axesPointToSideConnectivity [1] [SIDE_TOP   ]) << " "
                   << connectivityString (axesPointToSideConnectivity [2] [SIDE_TOP   ]) << "\n";
  str << "right  " << connectivityString (axesPointToSideConnectivity [0] [SIDE_RIGHT ]) << " "
                   << connectivityString (axesPointToSideConnectivity [1] [SIDE_RIGHT ]) << " "
                   << connectivityString (axesPointToSideConnectivity [2] [SIDE_RIGHT ]) << "\n";
  LOG4CPP_DEBUG_S ((*mainCat)) << "Checker::nextSide\n" << table.toLatin1().data();

  if (isTop && isBottom) {

    // Rare case where both horizontal sides are used but not the vertical sides. To have something
    // vertical we add both vertical sides (looks better than just one vertical side)
    if (!isLeft) {
      return SIDE_LEFT;
    } else if (!isRight) {
      return SIDE_RIGHT;
    } else {
      return NO_SIDE;
    }
  } else if (isLeft && isRight) {

    // Rare case where both vertical sides are used but not the horizontal sides. To have something
    // horizontal we add both vertical sides (looks better than just one horizontal side)
    if (!isTop) {
      return SIDE_TOP;
    } else if (!isBottom) {
      return SIDE_BOTTOM;
    } else {
      return NO_SIDE;
    }
  } else {

    // Normal case where we try to find two sides that pass through all three points
    const double FOM_DELTA_FOR_UNASSIGNED = 1.0;
    const double FOM_DELTA_FOR_ASSIGNED = 0.1;

    // As a clever figure of merit, we define a figure of merit for each side that has the number of
    // unconnected points as the integer part, and the number of connected points as the tenths decimal.
    // This gives preference to the side with more connected points, when two sides have the same
    // number of unconnected points
    double fomMax = 0;
    int sideMax = NO_SIDE; // Value that is returned if no unassigned points are found
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
  deleteLine (m_side3);

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

  // Greedy algorithm to assign axes points to sides. We use a minimum number of two sides which is usually enough.
  // However, the special case where 2 points are on one side and the third point is in the middle of the opposite
  // side, we use all four sides since having just two opposite, and disconnected, sides looks horrible
  bool isBottom = false, isLeft = false, isTop = false, isRight = false;
  int sideCount = 0;
  int nextS;
  while ((nextS = nextSide (axesPointToSideConnectivity,
                            isBottom,
                            isLeft,
                            isTop,
                            isRight)) >= 0) {

    markSideAsAssigned ((Side) nextS,
                        axesPointToSideConnectivity);

    QPointF p1, p2;
    switch (nextS) {
      case SIDE_BOTTOM:
        isBottom = true;
        p1 = QPointF (xMin, yMin);
        p2 = QPointF (xMax, yMin);
        break;

      case SIDE_LEFT:
        isLeft = true;
        p1 = QPointF (xMin, yMin);
        p2 = QPointF (xMin, yMax);
        break;

      case SIDE_RIGHT:
        isRight = true;
        p1 = QPointF (xMax, yMin);
        p2 = QPointF (xMax, yMax);
        break;

      case SIDE_TOP:
        isTop = true;
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
        break;

      case 3:
        createLine (m_side3, p1, p2, transformation);
        break;
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
    if (m_side2 != 0) {
      m_side2->setVisible (visible);
    }
    if (m_side3 != 0) {
      m_side3->setVisible (visible);
    }
  }
}

void Checker::updateModelAxesChecker (const DocumentModelAxesChecker &modelAxesChecker)
{
  QColor color = ColorPaletteToQColor (modelAxesChecker.lineColor());
  QPen pen (QBrush (color), CHECKER_POINTS_WIDTH);

  setLineColor (m_side0, pen);
  setLineColor (m_side1, pen);
  if (m_side2 != 0) {
    setLineColor (m_side2, pen);
  }
  if (m_side3 != 0) {
    setLineColor (m_side3, pen);
  }
}
