/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Curve.h"
#include "CurvesGraphs.h"
#include "CurveStyles.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "Point.h"
#include <qdebug.h>
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

  ENGAUGE_ASSERT (false);
}

void CurvesGraphs::iterateThroughCurveSegments (const QString &curveNameWanted,
                                                const Functor2wRet<const Point &, const Point &, CallbackSearchReturn> &ftorWithCallback) const
{
  // Search for curve with matching name
  CurveList::const_iterator itr;
  for (itr = m_curvesGraphs.begin (); itr != m_curvesGraphs.end (); itr++) {

    const Curve &curve = *itr;
    if (curve.curveName () == curveNameWanted) {

      curve.iterateThroughCurveSegments (ftorWithCallback);
      return;
    }
  }

  ENGAUGE_ASSERT (false);
}

void CurvesGraphs::iterateThroughCurvesPoints (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback)
{
  CurveList::const_iterator itr;
  for (itr = m_curvesGraphs.begin (); itr != m_curvesGraphs.end (); itr++) {

    const Curve &curve = *itr;
    curve.iterateThroughCurvePoints (ftorWithCallback);
  }
}

void CurvesGraphs::iterateThroughCurvesPoints (const Functor2wRet<const QString &, const Point &, CallbackSearchReturn> &ftorWithCallback)  const
{
  CurveList::const_iterator itr;
  for (itr = m_curvesGraphs.begin (); itr != m_curvesGraphs.end (); itr++) {

    const Curve &curve = *itr;
    curve.iterateThroughCurvePoints (ftorWithCallback);
  }
}

void CurvesGraphs::loadPreVersion6(QDataStream &str)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CurvesGraphs::loadPreVersion6";

  int i;

  // Remove previous Curves. There is a DEFAULT_GRAPH_CURVE_NAME by default
  m_curvesGraphs.clear();

  qint32 numberCurvesGraphs;
  str >> numberCurvesGraphs;
  for (i = 0; i < numberCurvesGraphs; i++) {
    Curve curve (str);
    m_curvesGraphs.append (curve);
  }

  qint32 numberCurvesMeasures;
  str >> numberCurvesMeasures;
  for (i = 0; i < numberCurvesMeasures; i++) {
    Curve curve (str);

    // Measures get dropped on the floor
  }
}

void CurvesGraphs::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CurvesGraphs::loadXml";

  bool success = true;

  // Remove previous Curves. There is a DEFAULT_GRAPH_CURVE_NAME by default
  m_curvesGraphs.clear();

  // Read until end of this subtree
  while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
  (reader.name() != DOCUMENT_SERIALIZE_CURVES_GRAPHS)){

    loadNextFromReader(reader);
    if (reader.atEnd()) {
      success = false;
      break;
    }

    if ((reader.tokenType() == QXmlStreamReader::StartElement) &&
        (reader.name () == DOCUMENT_SERIALIZE_CURVE)) {

      Curve curve (reader);

      // Version 6 of Engauge let users create multiple curves with the same name. Reading a file with duplicate
      // curve names can result in crashes and/or corruption, so we deconflict duplicate curve names here
      QString DUPLICATE = QString ("-%1").arg (QObject::tr ("DUPLICATE"));
      QString curveName = curve.curveName();
      while (curvesGraphsNames().contains (curveName)) {
        curveName += DUPLICATE;
      }
      curve.setCurveName (curveName); // No effect if curve name was not a duplicate

      // Add the curve
      m_curvesGraphs.push_back (curve);

    }
  }

  if (!success) {
    reader.raiseError (QObject::tr ("Cannot read graph curves data"));
  }
}

int CurvesGraphs::numCurves () const
{
  return m_curvesGraphs.count ();
}

void CurvesGraphs::printStream (QString indentation,
                                QTextStream &str) const
{
  str << indentation << "CurvesGraphs\n";

  indentation += INDENTATION_DELTA;

  CurveList::const_iterator itr;
  for (itr = m_curvesGraphs.begin (); itr != m_curvesGraphs.end (); itr++) {

    const Curve &curve = *itr;
    curve.printStream (indentation,
                       str);
  }
}

void CurvesGraphs::removePoint (const QString &pointIdentifier)
{
  QString curveName = Point::curveNameFromPointIdentifier(pointIdentifier);

  Curve *curve = curveForCurveName (curveName);
  curve->removePoint (pointIdentifier);
}

void CurvesGraphs::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CurvesGraphs::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_CURVES_GRAPHS);

  CurveList::const_iterator itr;
  for (itr = m_curvesGraphs.begin (); itr != m_curvesGraphs.end (); itr++) {

    const Curve &curve = *itr;
    curve.saveXml (writer);
  }

  writer.writeEndElement();
}

void CurvesGraphs::updatePointOrdinals (const Transformation &transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CurvesGraphs::updatePointOrdinals";

  CurveList::iterator itr;
  for (itr = m_curvesGraphs.begin (); itr != m_curvesGraphs.end (); itr++) {

    Curve &curve = *itr;
    curve.updatePointOrdinals (transformation);
  }
}
