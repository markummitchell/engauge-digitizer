/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CurveStyle.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include <QTextStream>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "Xml.h"

CurveStyle::CurveStyle()
{
}

CurveStyle::CurveStyle (const LineStyle &lineStyle,
                        const PointStyle &pointStyle) :
  m_pointStyle (pointStyle),
  m_lineStyle (lineStyle)
{
}

LineStyle CurveStyle::lineStyle() const
{
  return m_lineStyle;
}

QString CurveStyle::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CurveStyle::loadXml";

  bool success = true;
  QString curveName;

  QXmlStreamAttributes attributes = reader.attributes();

  if (attributes.hasAttribute(DOCUMENT_SERIALIZE_CURVE_NAME)) {

    curveName = attributes.value (DOCUMENT_SERIALIZE_CURVE_NAME).toString();

    // Read until end of this subtree
    while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
    (reader.name() != DOCUMENT_SERIALIZE_POINT_STYLE)){
      loadNextFromReader(reader);

      if (reader.atEnd()) {
        success = false;
        break;
      }

      if ((reader.tokenType() == QXmlStreamReader::StartElement) &&
          (reader.name() == DOCUMENT_SERIALIZE_LINE_STYLE)) {

        m_lineStyle.loadXml (reader);

      } else if ((reader.tokenType() == QXmlStreamReader::StartElement) &
                 (reader.name() == DOCUMENT_SERIALIZE_POINT_STYLE)) {

        m_pointStyle.loadXml (reader);

      }
    }
  }

  if (!success) {
    reader.raiseError (QObject::tr ("Cannot read curve style data"));
  }

  return curveName;
}

PointStyle CurveStyle::pointStyle() const
{
  return m_pointStyle;
}

void CurveStyle::printStream(QString indentation,
                             QTextStream &str) const
{
  str << indentation << "CurveStyle\n";

  indentation += INDENTATION_DELTA;

  m_pointStyle.printStream (indentation,
                            str);
  m_lineStyle.printStream (indentation,
                           str);
}

void CurveStyle::saveXml(QXmlStreamWriter &writer,
                         const QString &curveName) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CurveStyle::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_CURVE_STYLE);
  writer.writeAttribute (DOCUMENT_SERIALIZE_CURVE_NAME, curveName);
  m_lineStyle.saveXml (writer);
  m_pointStyle.saveXml (writer);
  writer.writeEndElement();
}

void CurveStyle::setLineColor (ColorPalette lineColor)
{
  m_lineStyle.setPaletteColor(lineColor);
}

void CurveStyle::setLineConnectAs (CurveConnectAs curveConnectAs)
{
  m_lineStyle.setCurveConnectAs(curveConnectAs);
}

void CurveStyle::setLineStyle(const LineStyle &lineStyle)
{
  m_lineStyle = lineStyle;
}

void CurveStyle::setLineWidth (int width)
{
  m_lineStyle.setWidth(width);
}

void CurveStyle::setPointColor (ColorPalette curveColor)
{
  m_pointStyle.setPaletteColor(curveColor);
}

void CurveStyle::setPointLineWidth (int width)
{
  m_pointStyle.setLineWidth(width);
}

void CurveStyle::setPointRadius (int radius)
{
  m_pointStyle.setRadius(radius);
}

void CurveStyle::setPointShape (PointShape shape)
{
  m_pointStyle.setShape(shape);
}

void CurveStyle::setPointStyle(const PointStyle &pointStyle)
{
  m_pointStyle = pointStyle;
}
