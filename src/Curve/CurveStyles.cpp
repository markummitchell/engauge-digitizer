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
  m_curveStyles [AXIS_CURVE_NAME].setLineStyle (curveAxes.curveStyle().lineStyle());
  m_curveStyles [AXIS_CURVE_NAME].setPointStyle (curveAxes.curveStyle().pointStyle());

  // Graph curves
  QStringList graphCurveNames = document.curvesGraphsNames();
  QStringList::const_iterator itr;
  for (itr = graphCurveNames.begin (); itr != graphCurveNames.end (); itr++) {

    const QString &graphCurveName = *itr;
    const Curve *graphCurve = document.curveForCurveName(graphCurveName);
    m_curveStyles [graphCurveName].setLineStyle (graphCurve->curveStyle().lineStyle());
    m_curveStyles [graphCurveName].setPointStyle (graphCurve->curveStyle().pointStyle());
  }
}

CurveStyles::CurveStyles (const CurveStyles &other)
{
  const QStringList curveNames = other.curveNames();
  QStringList::const_iterator itr;
  for (itr = curveNames.begin(); itr != curveNames.end(); itr++) {

    QString curveName = *itr;

    m_curveStyles [curveName] = other.curveStyle (curveName);
  }
}

CurveStyles &CurveStyles::operator=(const CurveStyles &other)
{
  const QStringList curveNames = other.curveNames();
  QStringList::const_iterator itr;
  for (itr = curveNames.begin(); itr != curveNames.end(); itr++) {

    QString curveName = *itr;

    m_curveStyles [curveName] = other.curveStyle (curveName);
  }

  return *this;
}

QStringList CurveStyles::curveNames () const
{
  QStringList curveNames;
  CurveStylesInternal::const_iterator itr;
  for (itr = m_curveStyles.begin(); itr != m_curveStyles.end(); itr++) {

    curveNames << itr.key();
  }

  return curveNames;
}

CurveStyle CurveStyles::curveStyle (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_curveStyles.contains (curveName));
  return m_curveStyles [curveName];
}

ColorPalette CurveStyles::lineColor (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_curveStyles.contains (curveName));
  return m_curveStyles [curveName].lineStyle().paletteColor();
}

CurveConnectAs CurveStyles::lineConnectAs (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_curveStyles.contains (curveName));
  return m_curveStyles [curveName].lineStyle().curveConnectAs();
}

const LineStyle CurveStyles::lineStyle (const QString &curveName) const
{
  return m_curveStyles [curveName].lineStyle();
}

int CurveStyles::lineWidth (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_curveStyles.contains (curveName));
  return m_curveStyles [curveName].lineStyle().width();
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
        (reader.name() == DOCUMENT_SERIALIZE_CURVE_STYLE)) {

      // Node has a CurveStyle that we need to parse and save
      CurveStyle curveStyle;
      QString curveName = curveStyle.loadXml (reader);

      m_curveStyles [curveName] = curveStyle;
    }
  }

  if (!success) {
    reader.raiseError ("Cannot read curve styles");
  }
}

ColorPalette CurveStyles::pointColor (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_curveStyles.contains (curveName));
  return m_curveStyles [curveName].pointStyle().paletteColor();
}

bool CurveStyles::pointIsCircle (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_curveStyles.contains (curveName));
  return m_curveStyles [curveName].pointStyle().isCircle();
}

int CurveStyles::pointLineWidth (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_curveStyles.contains (curveName));
  return m_curveStyles [curveName].pointStyle().lineWidth();
}

QPolygonF CurveStyles::pointPolygon (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_curveStyles.contains (curveName));
  return m_curveStyles [curveName].pointStyle().polygon();
}

int CurveStyles::pointRadius (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_curveStyles.contains (curveName));
  return m_curveStyles [curveName].pointStyle().radius();
}

PointShape CurveStyles::pointShape (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_curveStyles.contains (curveName));
  return m_curveStyles [curveName].pointStyle().shape ();
}

const PointStyle CurveStyles::pointStyle (const QString &curveName) const
{
  ENGAUGE_ASSERT (m_curveStyles.contains (curveName));
  return m_curveStyles [curveName].pointStyle();
}

void CurveStyles::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CurveStyles::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_CURVE_STYLES);
  CurveStylesInternal::const_iterator itr;
  for (itr = m_curveStyles.begin(); itr != m_curveStyles.end(); itr++) {

    QString curveName = itr.key();
    const CurveStyle &curveStyle = itr.value();

    curveStyle.saveXml(writer,
                       curveName);
  }
  writer.writeEndElement();
}

void CurveStyles::setCurveStyle (const QString &curveName,
                                 const CurveStyle &curveStyle)
{
  ENGAUGE_ASSERT (m_curveStyles.contains (curveName));
  m_curveStyles [curveName] = curveStyle;
}

void CurveStyles::setLineColor (const QString &curveName,
                                ColorPalette lineColor)
{
  ENGAUGE_ASSERT (m_curveStyles.contains (curveName));
  CurveStyle &curveStyle = m_curveStyles [curveName];
  curveStyle.setLineColor (lineColor);
}

void CurveStyles::setLineConnectAs (const QString &curveName,
                                    CurveConnectAs curveConnectAs)
{
  ENGAUGE_ASSERT (m_curveStyles.contains (curveName));
  CurveStyle &curveStyle = m_curveStyles [curveName];
  curveStyle.setLineConnectAs(curveConnectAs);
}

void CurveStyles::setLineWidth (const QString &curveName,
                                int width)
{
  ENGAUGE_ASSERT (m_curveStyles.contains (curveName));
  CurveStyle &curveStyle = m_curveStyles [curveName];
  curveStyle.setLineWidth(width);
}

void CurveStyles::setPointColor (const QString &curveName,
                                 ColorPalette curveColor)
{
  ENGAUGE_ASSERT (m_curveStyles.contains (curveName));
  CurveStyle &curveStyle = m_curveStyles [curveName];
  curveStyle.setPointColor (curveColor);
}

void CurveStyles::setPointLineWidth (const QString &curveName,
                                     int width)
{
  ENGAUGE_ASSERT (m_curveStyles.contains (curveName));
  CurveStyle &curveStyle = m_curveStyles [curveName];
  curveStyle.setPointLineWidth (width);
}

void CurveStyles::setPointRadius (const QString &curveName,
                                  int radius)
{
  ENGAUGE_ASSERT (m_curveStyles.contains (curveName));
  CurveStyle &curveStyle = m_curveStyles [curveName];
  curveStyle.setPointRadius (radius);
}

void CurveStyles::setPointShape (const QString &curveName,
                                 PointShape shape)
{
  ENGAUGE_ASSERT (m_curveStyles.contains (curveName));
  CurveStyle &curveStyle = m_curveStyles [curveName];
  curveStyle.setPointShape (shape);
}

