#include "Curve.h"
#include "CurvesGraphs.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "Point.h"
#include <QTextStream>
#include <QXmlStreamWriter>
#include "Transformation.h"
#include "Xml.h"

CurvesGraphs::CurvesGraphs()
{
}

void CurvesGraphs::addGraphCurveAtEnd (Curve curve)
{
  m_curvesGraphs.push_back (curve);
}

void CurvesGraphs::addPoint (const Point &point)
{
  QString curveName = Point::curveNameFromPointIdentifier (point.identifier());

  Curve *curve = curveForCurveName (curveName);
  curve->addPoint (point);
}

void CurvesGraphs::applyTransformation (const Transformation &transformation)
{
  CurveList::iterator itr;
  for (itr = m_curvesGraphs.begin (); itr != m_curvesGraphs.end (); itr++) {

    Curve &curve = *itr;
    curve.applyTransformation (transformation);
  }
}

Curve *CurvesGraphs::curveForCurveName (const QString &curveName)
{
  // Search for curve with matching name
  CurveList::iterator itr;
  for (itr = m_curvesGraphs.begin (); itr != m_curvesGraphs.end (); itr++) {

    Curve &curve = *itr;
    if (curveName == curve.curveName ()) {
      return &curve;
    }
  }

  return 0;
}

const Curve *CurvesGraphs::curveForCurveName (const QString &curveName) const
{
  // Search for curve with matching name
  CurveList::const_iterator itr;
  for (itr = m_curvesGraphs.begin (); itr != m_curvesGraphs.end (); itr++) {

    const Curve &curve = *itr;
    if (curveName == curve.curveName ()) {
      return &curve;
    }
  }

  return 0;
}

QStringList CurvesGraphs::curvesGraphsNames () const
{
  QStringList names;

  CurveList::const_iterator itr;
  for (itr = m_curvesGraphs.begin (); itr != m_curvesGraphs.end (); itr++) {

    const Curve &curve = *itr;
    names << curve.curveName ();
  }

  return names;
}

int CurvesGraphs::curvesGraphsNumPoints (const QString &curveName) const
{
  // Search for curve with matching name
  CurveList::const_iterator itr;
  for (itr = m_curvesGraphs.begin (); itr != m_curvesGraphs.end (); itr++) {

    const Curve &curve = *itr;
    if (curve.curveName () == curveName) {
      return curve.numPoints ();
    }
  }

  return 0;
}

void CurvesGraphs::iterateThroughCurvePoints (const QString &curveNameWanted,
                                              const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback)
{
  // Search for curve with matching name
  CurveList::const_iterator itr;
  for (itr = m_curvesGraphs.begin (); itr != m_curvesGraphs.end (); itr++) {

    const Curve &curve = *itr;
    if (curve.curveName () == curveNameWanted) {

      curve.iterateThroughCurvePoints (ftorWithCallback);
      return;
    }
  }

  Q_ASSERT (false);
}

void CurvesGraphs::iterateThroughCurvesPoints (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback)
{
  CurveList::const_iterator itr;
  for (itr = m_curvesGraphs.begin (); itr != m_curvesGraphs.end (); itr++) {

    const Curve &curve = *itr;
    curve.iterateThroughCurvePoints (ftorWithCallback);
  }
}

void CurvesGraphs::loadDocument(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CurvesGraphs::loadDocument";

  bool success = true;

  // Read until end of this subtree
  while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
  (reader.name() != DOCUMENT_SERIALIZE_CURVES_GRAPHS)){

    if ((reader.tokenType() == QXmlStreamReader::StartElement) &&
        (reader.name () == DOCUMENT_SERIALIZE_CURVE)) {

      Curve curve (reader);

      m_curvesGraphs.push_back (curve);

    } else {

      loadNextFromReader(reader);
      if (reader.hasError()) {
        // No need to set success flag, which raises the error, since error was already raised. Just
        // need to exit loop immediately
        break;
      }
      if (reader.atEnd()) {
        success = false;
        break;
      }
    }
  }

  if (!success) {
    reader.raiseError ("Cannot read graph curves data");
  }
}

int CurvesGraphs::numCurves () const
{
  return m_curvesGraphs.count ();
}

void CurvesGraphs::removePoint (const QString &pointIdentifier)
{
  QString curveName = Point::curveNameFromPointIdentifier(pointIdentifier);

  Curve *curve = curveForCurveName (curveName);
  curve->removePoint (pointIdentifier);
}

void CurvesGraphs::saveDocument(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CurvesGraphs::saveDocument";

  writer.writeStartElement(DOCUMENT_SERIALIZE_CURVES_GRAPHS);

  CurveList::const_iterator itr;
  for (itr = m_curvesGraphs.begin (); itr != m_curvesGraphs.end (); itr++) {

    const Curve &curve = *itr;
    curve.saveDocument (writer);
  }

  writer.writeEndElement();
}
