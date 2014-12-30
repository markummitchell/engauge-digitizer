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
const int NO_SIDE = -1;

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

void Checker::createLine (QGraphicsItem *&item,
                          const QPointF &pointFromGraph,
                          const QPointF &pointToGraph,
                          const Transformation &transformation)
{
  // Convert graph coordinates to screen coordinates
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

  // Screen and graph coordinates are treated as the same, so identity transform is used
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

  // Remove previous lines
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

  // Draw the bounding box as four sides
  createLine (m_side0, QPointF (xMin, yMin), QPointF (xMax, yMin), transformation);
  createLine (m_side1, QPointF (xMin, yMin), QPointF (xMin, yMax), transformation);
  createLine (m_side2, QPointF (xMax, yMin), QPointF (xMax, yMax), transformation);
  createLine (m_side3, QPointF (xMin, yMax), QPointF (xMax, yMax), transformation);

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
    m_side3->setVisible (visible);
  }
}

void Checker::updateModelAxesChecker (const DocumentModelAxesChecker &modelAxesChecker)
{
  QColor color = ColorPaletteToQColor (modelAxesChecker.lineColor());
  QPen pen (QBrush (color), CHECKER_POINTS_WIDTH);

  setLineColor (m_side0, pen);
  setLineColor (m_side1, pen);
  setLineColor (m_side2, pen);
  setLineColor (m_side3, pen);
}
