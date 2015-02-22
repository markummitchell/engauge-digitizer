#include "CmdMediator.h"
#include "CurveStyles.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include <QDebug>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "Xml.h"

CurveStyles::CurveStyles()
{
}

CurveStyles::CurveStyles (const Document &document)
{
  // Axis curve
  const Curve &curveAxes = document.curveAxes();
  m_lineStyles [AXIS_CURVE_NAME] = curveAxes.lineStyle();
  m_pointStyles [AXIS_CURVE_NAME] = curveAxes.pointStyle ();

  // Graph curves
  QStringList graphCurveNames = document.curvesGraphsNames();
  QStringList::const_iterator itr;
  for (itr = graphCurveNames.begin (); itr != graphCurveNames.end (); itr++) {

    const QString &graphCurveName = *itr;
    const Curve *graphCurve = document.curveForCurveName(graphCurveName);
    m_lineStyles [graphCurveName] = graphCurve->lineStyle();
    m_pointStyles [graphCurveName] = graphCurve->pointStyle ();
  }
}

CurveStyles::CurveStyles (const CurveStyles &other)
{
  // Line styles
  LineStyles::const_iterator itrL;
  for (itrL = other.lineStyles().constBegin (); itrL != other.lineStyles().constEnd(); itrL++) {
    QString curveName = itrL.key();
    LineStyle lineStyle = itrL.value();
    m_lineStyles [curveName] = lineStyle;
  }

  // Point styles
  PointStyles::const_iterator itrP;
  for (itrP = other.pointStyles().constBegin(); itrP != other.pointStyles().constEnd(); itrP++) {
    QString curveName = itrP.key();
    PointStyle pointStyle = itrP.value();   
    m_pointStyles [curveName] = pointStyle;
  }
}

CurveStyles &CurveStyles::operator=(const CurveStyles &other)
{
  // Line styles
  LineStyles::const_iterator itrL;
  for (itrL = other.lineStyles().constBegin (); itrL != other.lineStyles().constEnd(); itrL++) {
    QString curveName = itrL.key();
    LineStyle lineStyle = itrL.value();
    m_lineStyles [curveName] = lineStyle;
  }

  // Point styles
  PointStyles::const_iterator itrP;
  for (itrP = other.pointStyles().constBegin(); itrP != other.pointStyles().constEnd(); itrP++) {
    QString curveName = itrP.key();
    PointStyle pointStyle = itrP.value();
    m_pointStyles [curveName] = pointStyle;
  }

  return *this;
}

ColorPalette CurveStyles::lineColor (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_lineStyles.contains (curveName));
  return m_lineStyles [curveName].paletteColor();
}

CurveConnectAs CurveStyles::lineConnectAs (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_lineStyles.contains (curveName));
  return m_lineStyles [curveName].curveConnectAs();
}

const LineStyle CurveStyles::lineStyle (const QString &curveName) const
{
  return m_lineStyles [curveName];
}

const LineStyles &CurveStyles::lineStyles () const
{
  return m_lineStyles;
}

double CurveStyles::lineWidth (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_lineStyles.contains (curveName));
  return m_lineStyles [curveName].width();
}

void CurveStyles::loadXml (QXmlStreamReader &reader)
{
  bool success = true;

  // Read through each DOCUMENT_SERIALIZE_LINE_STYLE and DOCUMENT_SERIALIZE_POINT_STYLE until end of DOCUMENT_SERIALIZE_CURVE_STYLES is encountered
  while (loadNextFromReader (reader)) {

    if (reader.atEnd() || reader.hasError ()) {
      success = false;
      break;
    }

    if ((reader.tokenType() == QXmlStreamReader::EndElement) &&
         (reader.name() == DOCUMENT_SERIALIZE_CURVE_STYLES)) {
      break;
    }

    // Not done yet
    if ((reader.tokenType() == QXmlStreamReader::StartElement) &&
        (reader.name() == DOCUMENT_SERIALIZE_LINE_STYLE)) {

      // Node has a LineStyle that we need to parse and save
      LineStyle lineStyle;
      QString curveName = lineStyle.loadXml (reader);

      m_lineStyles [curveName] = lineStyle;

    } else if ((reader.tokenType() == QXmlStreamReader::StartElement) &&
               (reader.name() == DOCUMENT_SERIALIZE_POINT_STYLE)) {

      // Node has a PointSTyle that we need to parse and save
      PointStyle pointStyle;
      QString curveName = pointStyle.loadXml (reader);

      m_pointStyles [curveName] = pointStyle;
    }
  }

  if (!success) {
    reader.raiseError ("Cannot read point identifiers");
  }
}

ColorPalette CurveStyles::pointColor (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_pointStyles.contains (curveName));
  return m_pointStyles [curveName].paletteColor();
}

bool CurveStyles::pointIsCircle (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_pointStyles.contains (curveName));
  return m_pointStyles [curveName].isCircle();
}

double CurveStyles::pointLineWidth (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_pointStyles.contains (curveName));
  return m_pointStyles [curveName].lineWidth();
}

QPolygonF CurveStyles::pointPolygon (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_pointStyles.contains (curveName));
  return m_pointStyles [curveName].polygon();
}

int CurveStyles::pointRadius (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_pointStyles.contains (curveName));
  return m_pointStyles [curveName].radius();
}

PointShape CurveStyles::pointShape (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_pointStyles.contains (curveName));
  return m_pointStyles [curveName].shape ();
}

const PointStyle CurveStyles::pointStyle (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_pointStyles.contains (curveName));
  return m_pointStyles [curveName];
}

const PointStyles &CurveStyles::pointStyles() const
{
  return m_pointStyles;
}

void CurveStyles::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CurveStyles::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_CURVE_STYLES);
  writer.writeStartElement(DOCUMENT_SERIALIZE_CURVE_STYLES_LINE_STYLES);
  LineStyles::const_iterator itrL;
  for (itrL = m_lineStyles.begin(); itrL != m_lineStyles.end(); itrL++) {

    QString curveName = itrL.key();
    const LineStyle &lineStyle = itrL.value();

    lineStyle.saveXml(writer,
                      curveName);
  }
  writer.writeEndElement();
  writer.writeStartElement(DOCUMENT_SERIALIZE_CURVE_STYLES_POINT_STYLES);
  PointStyles::const_iterator itrP;
  for (itrP = m_pointStyles.begin(); itrP != m_pointStyles.end(); itrP++) {

    QString curveName = itrP.key();
    const PointStyle &pointStyle = itrP.value();

    pointStyle.saveXml(writer,
                       curveName);
  }
  writer.writeEndElement();
  writer.writeEndElement();
}

void CurveStyles::setLineColor (const QString &curveName,
                                ColorPalette lineColor)
{
  ENGAUGE_ASSERT (m_lineStyles.contains (curveName));
  m_lineStyles [curveName].setPaletteColor(lineColor);
}

void CurveStyles::setLineConnectAs (const QString &curveName,
                                    CurveConnectAs curveConnectAs)
{
  ENGAUGE_ASSERT (m_lineStyles.contains (curveName));
  m_lineStyles [curveName].setCurveConnectAs(curveConnectAs);
}

void CurveStyles::setLineWidth (const QString &curveName,
                                int width)
{
  ENGAUGE_ASSERT (m_lineStyles.contains (curveName));
  m_lineStyles [curveName].setWidth(width);
}

void CurveStyles::setPointColor (const QString &curveName,
                                 ColorPalette curveColor)
{
  ENGAUGE_ASSERT (m_pointStyles.contains (curveName));
  m_pointStyles [curveName].setPaletteColor(curveColor);
}

void CurveStyles::setPointLineWidth (const QString &curveName,
                                     double width)
{
  ENGAUGE_ASSERT (m_pointStyles.contains (curveName));
  m_pointStyles [curveName].setLineWidth (width);
}

void CurveStyles::setPointRadius (const QString &curveName,
                                  int radius)
{
  ENGAUGE_ASSERT (m_pointStyles.contains (curveName));
  m_pointStyles [curveName].setRadius (radius);
}

void CurveStyles::setPointShape (const QString &curveName,
                                 PointShape shape)
{
  ENGAUGE_ASSERT (m_pointStyles.contains (curveName));
  m_pointStyles [curveName].setShape (shape);
}

