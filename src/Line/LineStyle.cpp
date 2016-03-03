/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DocumentSerialize.h"
#include "LineStyle.h"
#include "Logger.h"
#include <QObject>
#include <QSettings>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "Settings.h"
#include "SettingsForGraph.h"
#include "Xml.h"

const ColorPalette DEFAULT_LINE_COLOR_AXES = COLOR_PALETTE_TRANSPARENT; // Same default color as used for PointStyle axes curve default
const ColorPalette DEFAULT_LINE_COLOR_GRAPH = COLOR_PALETTE_BLUE;       // Same default color as used for PointStyle axes curve default
const CurveConnectAs DEFAULT_LINE_CONNECT_AS_AXES = CONNECT_SKIP_FOR_AXIS_CURVE;
const CurveConnectAs DEFAULT_LINE_CONNECT_AS_GRAPH = CONNECT_AS_FUNCTION_SMOOTH;
const int DEFAULT_LINE_WIDTH_AXES = 0;
const int DEFAULT_LINE_WIDTH_GRAPH = 1;

LineStyle::LineStyle ()
{
  QSettings settings (SETTINGS_ENGAUGE, SETTINGS_DIGITIZER);
  settings.beginGroup (SETTINGS_GROUP_CURVE_AXES);
  m_width = settings.value (SETTINGS_CURVE_LINE_WIDTH,
                            DEFAULT_LINE_WIDTH_AXES).toInt();
  m_paletteColor = (ColorPalette) settings.value (SETTINGS_CURVE_LINE_COLOR,
                                                  DEFAULT_LINE_COLOR_AXES).toInt();
  m_curveConnectAs = (CurveConnectAs) settings.value (SETTINGS_CURVE_LINE_CONNECT_AS,
                                                      DEFAULT_LINE_CONNECT_AS_AXES).toInt();
}

LineStyle::LineStyle (unsigned int width,
                      ColorPalette paletteColor,
                      CurveConnectAs curveConnectAs) :
  m_width (width),
  m_paletteColor (paletteColor),
  m_curveConnectAs (curveConnectAs)
{
}

LineStyle::LineStyle (const LineStyle &other) :
  m_width (other.width ()),
  m_paletteColor (other.paletteColor()),
  m_curveConnectAs (other.curveConnectAs())
{
}

LineStyle &LineStyle::operator= (const LineStyle &other)
{
  m_width = other.width ();
  m_paletteColor = other.paletteColor();
  m_curveConnectAs = other.curveConnectAs();

  return *this;
}

CurveConnectAs LineStyle::curveConnectAs () const
{
  return m_curveConnectAs;
}

LineStyle LineStyle::defaultAxesCurve ()
{
  QSettings settings (SETTINGS_ENGAUGE, SETTINGS_DIGITIZER);
  settings.beginGroup (SETTINGS_GROUP_CURVE_AXES);
  int width = settings.value (SETTINGS_CURVE_LINE_WIDTH,
                              DEFAULT_LINE_WIDTH_AXES).toInt();
  ColorPalette color = (ColorPalette) settings.value (SETTINGS_CURVE_LINE_COLOR,
                                                      DEFAULT_LINE_COLOR_AXES).toInt();
  CurveConnectAs connectAs = (CurveConnectAs) settings.value (SETTINGS_CURVE_LINE_CONNECT_AS,
                                                              DEFAULT_LINE_CONNECT_AS_AXES).toInt();

  return LineStyle (width,
                    color,
                    connectAs);
}

LineStyle LineStyle::defaultGraphCurve (int index)
{
  SettingsForGraph settingsForGraph;
  int indexOneBased = index + 1;
  QString groupName = settingsForGraph.groupNameForNthCurve (indexOneBased);

  QSettings settings (SETTINGS_ENGAUGE, SETTINGS_DIGITIZER);
  settings.beginGroup (groupName);
  int width = settings.value (SETTINGS_CURVE_LINE_WIDTH,
                              DEFAULT_LINE_WIDTH_GRAPH).toInt();
  ColorPalette color = (ColorPalette) settings.value (SETTINGS_CURVE_LINE_COLOR,
                                                      DEFAULT_LINE_COLOR_GRAPH).toInt();
  CurveConnectAs connectAs = (CurveConnectAs) settings.value (SETTINGS_CURVE_LINE_CONNECT_AS,
                                                              DEFAULT_LINE_CONNECT_AS_GRAPH).toInt();

  return LineStyle (width,
                    color,
                    connectAs);
}

void LineStyle::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "LineStyle::loadXml";

  QXmlStreamAttributes attributes = reader.attributes();

  if (attributes.hasAttribute(DOCUMENT_SERIALIZE_LINE_STYLE_WIDTH) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_LINE_STYLE_COLOR) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_LINE_STYLE_CONNECT_AS)) {

    setWidth (attributes.value(DOCUMENT_SERIALIZE_LINE_STYLE_WIDTH).toInt());
    setPaletteColor ((ColorPalette) attributes.value(DOCUMENT_SERIALIZE_LINE_STYLE_COLOR).toInt());
    setCurveConnectAs ((CurveConnectAs) attributes.value(DOCUMENT_SERIALIZE_LINE_STYLE_CONNECT_AS).toInt());

    // Read until end of this subtree
    while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
    (reader.name() != DOCUMENT_SERIALIZE_LINE_STYLE)){
      loadNextFromReader(reader);
    }
  } else {
    reader.raiseError (QObject::tr ("Cannot read line style data"));
  }
}

ColorPalette LineStyle::paletteColor() const
{
  return m_paletteColor;
}

void LineStyle::printStream(QString indentation,
                            QTextStream &str) const
{
  str << indentation << "LineStyle\n";
  
  indentation += INDENTATION_DELTA;

  str << indentation << "width=" << m_width << "\n";
  str << indentation << "color=" << colorPaletteToString (m_paletteColor) << "\n";
  str << indentation << "curveConnectAs=" << curveConnectAsToString (m_curveConnectAs) << "\n";
}

void LineStyle::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat))  << "LineStyle::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_LINE_STYLE);
  writer.writeAttribute (DOCUMENT_SERIALIZE_LINE_STYLE_WIDTH, QString::number(m_width));
  writer.writeAttribute (DOCUMENT_SERIALIZE_LINE_STYLE_COLOR, QString::number (m_paletteColor));
  writer.writeAttribute (DOCUMENT_SERIALIZE_LINE_STYLE_COLOR_STRING, colorPaletteToString (m_paletteColor));
  writer.writeAttribute (DOCUMENT_SERIALIZE_LINE_STYLE_CONNECT_AS, QString::number (m_curveConnectAs));
  writer.writeAttribute (DOCUMENT_SERIALIZE_LINE_STYLE_CONNECT_AS_STRING, curveConnectAsToString (m_curveConnectAs));
  writer.writeEndElement();
}

void LineStyle::setCurveConnectAs(CurveConnectAs curveConnectAs)
{
  m_curveConnectAs = curveConnectAs;
}

void LineStyle::setPaletteColor (ColorPalette paletteColor)
{
  m_paletteColor = paletteColor;
}

void LineStyle::setWidth (int width)
{
  m_width = width;
}

unsigned int LineStyle::width () const
{
  return m_width;
}
