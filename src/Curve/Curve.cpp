#include "Curve.h"
#include "CurvesGraphs.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "Point.h"
#include <QDebug>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "Transformation.h"
#include "Xml.h"

const QString AXIS_CURVE_NAME ("Axes");
const QString DEFAULT_GRAPH_CURVE_NAME ("Curve1");
const QString TAB_DELIMITER ("\t");

Curve::Curve(const QString &curveName,
             const CurveFilter &curveFilter,
             const LineStyle &lineStyle,
             const PointStyle &pointStyle) :
  m_curveName (curveName),
  m_curveFilter (curveFilter),
  m_lineStyle (lineStyle),
  m_pointStyle (pointStyle)
{
}

Curve::Curve (const Curve &curve) :
  m_curveName (curve.curveName ()),
  m_points (curve.points ()),
  m_curveFilter (curve.curveFilter ()),
  m_lineStyle (curve.lineStyle ()),
  m_pointStyle (curve.pointStyle ())
{
}

Curve::Curve (QXmlStreamReader &reader)
{
  loadDocument(reader);
}

Curve &Curve::operator=(const Curve &curve)
{
  m_curveName = curve.curveName ();
  m_points = curve.points ();
  m_curveFilter = curve.curveFilter ();
  m_lineStyle = curve.lineStyle ();
  m_pointStyle = curve.pointStyle ();

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

    // Get current screen coordinates
    Point &point = *itr;
    QPointF posScreen = point.posScreen();
    QPointF posGraph;
    transformation.transform (posScreen,
                              posGraph);

    // Overwrite old graph coordinates
    point.setPosGraph (posGraph);
  }
}

CurveFilter Curve::curveFilter () const
{
  return m_curveFilter;
}

QString Curve::curveName () const
{
  return  m_curveName;
}

void Curve::editPoint (const QPointF &posGraph,
                       const QString &identifier)
{
  // Search for the point with matching identifier
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
        Curve curve(m_curveName,
                    CurveFilter::defaultFilter (),
                    LineStyle::defaultAxesCurve (),
                    PointStyle::defaultGraphCurve (curvesGraphs.numCurves ()));
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

LineStyle Curve::lineStyle () const
{
  return m_lineStyle;
}

void Curve::loadDocument(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "Curve::loadDocument";

  bool success = true;

  // Read until end of this subtree
  while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
         (reader.name() != DOCUMENT_SERIALIZE_COORDS)){

    QXmlStreamReader::TokenType tokenType = loadNextFromReader(reader);

    if (tokenType == QXmlStreamReader::StartElement) {

      if (reader.name() == DOCUMENT_SERIALIZE_CURVE_FILTER) {
        m_curveFilter.loadDocument(reader);
      } else if (reader.name() == DOCUMENT_SERIALIZE_CURVE_POINTS) {

      } else if (reader.name() == DOCUMENT_SERIALIZE_LINE_STYLE) {
        m_lineStyle.loadDocument(reader);
      } else if (reader.name() == DOCUMENT_SERIALIZE_POINT_STYLE) {
        m_lineStyle.loadDocument(reader);
      } else {
        success = false;
        break;
      }
    }
  }

  if (!success) {
    reader.raiseError ("Cannot read curve data");
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

PointStyle Curve::pointStyle () const
{
  return m_pointStyle;
}

QPointF Curve::positionGraph (const QString &pointIdentifier) const
{
  QPointF posGraph;

  // Search for point with matching identifier
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

  // Search for point with matching identifier
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
  // Search for point with matching identifier
  Points::iterator itr;
  for (itr = m_points.begin (); itr != m_points.end (); itr++) {
    Point point = *itr;
    if (point.identifier () == identifier) {
      m_points.erase (itr);
      break;
    }
  }
}

void Curve::saveDocument(QXmlStreamWriter &stream) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "Curve::saveDocument";

  stream.writeStartElement(DOCUMENT_SERIALIZE_CURVE);
  stream.writeAttribute(DOCUMENT_SERIALIZE_CURVE_NAME, m_curveName);
  m_curveFilter.saveDocument (stream);
  m_lineStyle.saveDocument (stream);
  m_pointStyle.saveDocument (stream);

  // Loop through points
  stream.writeStartElement(DOCUMENT_SERIALIZE_CURVE_POINTS);
  Points::const_iterator itr;
  for (itr = m_points.begin (); itr != m_points.end (); itr++) {
    const Point &point = *itr;
    point.saveDocument (stream);
  }
  stream.writeEndElement();

  stream.writeEndElement();
}

void Curve::setCurveFilter (const CurveFilter &curveFilter)
{
  m_curveFilter = curveFilter;
}

void Curve::setCurveName (const QString &curveName)
{
  m_curveName = curveName;
}

void Curve::setLineStyle (const LineStyle &lineStyle)
{
  m_lineStyle = lineStyle;
}

void Curve::setPointStyle (const PointStyle &pointStyle)
{
  m_pointStyle = pointStyle;
}
