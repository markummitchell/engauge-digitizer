#include "Curve.h"
#include "CurvesGraphs.h"
#include "Logger.h"
#include "Point.h"
#include <QDebug>
#include "Transformation.h"

const QString AXIS_CURVE_NAME ("Axes");
const QString DEFAULT_GRAPH_CURVE_NAME ("Curve1");
const QString TAB_DELIMITER ("\t");

Curve::Curve(const QString &curveName) :
  m_curveName (curveName)
{
}

Curve::Curve (const Curve &curve)
{
  m_curveName = curve.curveName ();
  m_points = curve.points ();
}

Curve &Curve::operator=(const Curve &curve)
{
  m_curveName = curve.curveName ();
  m_points = curve.points ();

  return *this;
}

void Curve::addPoint (Point point)
{
  m_points.push_back (point);
}

void Curve::applyTransformation (const Transformation &transformation)
{
  QList<Point>::iterator itr;
  for (itr = m_points.begin (); itr != m_points.end (); itr++) {

    Point &point = *itr;
    QPointF posScreen = point.posScreen();
    QPointF posGraph;
    transformation.transform (posScreen,
                              posGraph);

    point.setPosGraph (posGraph);
  }
}

QString Curve::curveName () const
{
  return  m_curveName;
}

void Curve::editPoint (const QPointF &posGraph,
                       const QString &identifier)
{
  QList<Point>::iterator itr;
  for (itr = m_points.begin (); itr != m_points.end (); itr++) {

    Point &point = *itr;
    if (point.identifier () == identifier) {

      point.setPosGraph (posGraph);
      break;

    }
  }
}

void Curve::exportToClipboard (const QHash<QString, bool> &selectedHash,
                               bool transformIsDefined,
                               QTextStream &strCsv,
                               QTextStream &strHtml,
                               CurvesGraphs &curvesGraphs) const
{
  // This method assumes Copy is only allowed when Transformation is valid

  bool isFirst = true;
  QList<Point>::const_iterator itr;
  for (itr = m_points.begin (); itr != m_points.end (); itr++) {

    const Point &point = *itr;
    if (selectedHash.contains (point.identifier ())) {

      if (isFirst) {

        // Insert headers to identify the points that follow
        isFirst = false;
        strCsv << "X" << TAB_DELIMITER << m_curveName << "\n";
        strHtml << "<table>\n"
                << "<tr><th>X</th><th>" << m_curveName << "</th></tr>\n";
      }

      // Check if this curve already exists from a previously exported point
      if (curvesGraphs.curveForCurveName (m_curveName) == 0) {
        Curve curve(m_curveName);
        curvesGraphs.addGraphCurveAtEnd(curve);
      }

      double x = point.posScreen ().x (), y = point.posScreen ().y ();
      if (transformIsDefined) {
        x = point.posGraph ().x ();
        y = point.posGraph ().y ();
      }

      // Add point to text going to clipboard
      strCsv << x << TAB_DELIMITER << y << "\n";
      strHtml << "<tr><td>" << x << "</td><td>" << y << "</td></tr>\n";

      // Add point to list for undo/redo
      curvesGraphs.curveForCurveName (m_curveName)->addPoint (point);
    }
  }

  if (!isFirst) {
    strHtml << "</table>\n";
  }
}

void Curve::iterateThroughCurvePoints (const Functor2wRet<const QString &, const Point&, CallbackSearchReturn> &ftorWithCallback) const
{
  QList<Point>::const_iterator itr;
  for (itr = m_points.begin (); itr != m_points.end (); itr++) {

    const Point &point = *itr;

    CallbackSearchReturn rtn = ftorWithCallback (m_curveName, point);

    if (rtn == CALLBACK_SEARCH_RETURN_INTERRUPT) {
      break;
    }
  }
}

void Curve::movePoint (const QString &pointIdentifier,
                       const QPointF &deltaScreen)
{
  Point *point = pointForPointIdentifier (pointIdentifier);

  QPointF posScreen = deltaScreen + point->posScreen ();
  point->setPosScreen (posScreen);
}

int Curve::numPoints () const
{
  return m_points.count ();
}

Point *Curve::pointForPointIdentifier (const QString pointIdentifier)
{
  Points::iterator itr;
  for (itr = m_points.begin (); itr != m_points.end (); itr++) {
    Point &point = *itr;
    if (pointIdentifier == point.identifier ()) {
      return &point;
    }
  }

  Q_ASSERT (false);
  return 0;
}

QPointF Curve::positionGraph (const QString &pointIdentifier) const
{
  QPointF posGraph;

  Points::const_iterator itr;
  for (itr = m_points.begin (); itr != m_points.end (); itr++) {
    const Point &point = *itr;
    if (pointIdentifier == point.identifier ()) {
      posGraph = point.posGraph ();
      break;
    }
  }

  return posGraph;
}

QPointF Curve::positionScreen (const QString &pointIdentifier) const
{
  QPointF posScreen;

  Points::const_iterator itr;
  for (itr = m_points.begin (); itr != m_points.end (); itr++) {
    const Point &point = *itr;
    if (pointIdentifier == point.identifier ()) {
      posScreen = point.posScreen ();
      break;
    }
  }

  return posScreen;
}

const Points Curve::points () const
{
  return m_points;
}

void Curve::removePoint (const QString &identifier)
{
  Points::iterator itr;
  for (itr = m_points.begin (); itr != m_points.end (); itr++) {
    Point point = *itr;
    if (point.identifier () == identifier) {
      m_points.erase (itr);
      break;
    }
  }
}

void Curve::setCurveName (const QString &curveName)
{
  m_curveName = curveName;
}
