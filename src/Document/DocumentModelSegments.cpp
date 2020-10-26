/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMediator.h"
#include "DocumentModelSegments.h"
#include "DocumentSerialize.h"
#include "InactiveOpacity.h"
#include "Logger.h"
#include <QObject>
#include <QTextStream>
#include <QXmlStreamWriter>
#include "Xml.h"

const double DEFAULT_POINT_SEPARATION = 25;
const double DEFAULT_MIN_LENGTH = 2;
const double DEFAULT_LINE_WIDTH_ACTIVE = 6; // Highlight is slightly bigger
const double DEFAULT_LINE_WIDTH_INACTIVE = 4;
const ColorPalette DEFAULT_LINE_COLOR (COLOR_PALETTE_GREEN);
const InactiveOpacity DEFAULT_INACTIVE_OPACITY = INACTIVE_OPACITY_128; // Highlight is slightly brighter as INACTIVE_OPACITY_256

DocumentModelSegments::DocumentModelSegments() :
  m_pointSeparation (DEFAULT_POINT_SEPARATION),
  m_minLength (DEFAULT_MIN_LENGTH),
  m_fillCorners (false),
  m_lineWidthActive (DEFAULT_LINE_WIDTH_ACTIVE),
  m_lineWidthInactive (DEFAULT_LINE_WIDTH_INACTIVE),  
  m_lineColor (DEFAULT_LINE_COLOR),
  m_inactiveOpacity (DEFAULT_INACTIVE_OPACITY)
{
}

DocumentModelSegments::DocumentModelSegments(const Document &document) :
  m_pointSeparation (document.modelSegments().pointSeparation()),
  m_minLength (document.modelSegments().minLength()),
  m_fillCorners (document.modelSegments().fillCorners()),
  m_lineWidthActive (document.modelSegments().lineWidthActive()),
  m_lineWidthInactive (document.modelSegments().lineWidthInactive()),  
  m_lineColor (document.modelSegments().lineColor()),
  m_inactiveOpacity (document.modelSegments().inactiveOpacity())
{
}

DocumentModelSegments::DocumentModelSegments(const DocumentModelSegments &other) :
  m_pointSeparation (other.pointSeparation()),
  m_minLength (other.minLength()),
  m_fillCorners (other.fillCorners ()),
  m_lineWidthActive (other.lineWidthActive()),
  m_lineWidthInactive (other.lineWidthInactive()),  
  m_lineColor (other.lineColor()),
  m_inactiveOpacity (other.inactiveOpacity())
{
}

DocumentModelSegments &DocumentModelSegments::operator=(const DocumentModelSegments &other)
{
  m_pointSeparation = other.pointSeparation();
  m_minLength = other.minLength();
  m_fillCorners = other.fillCorners ();
  m_lineWidthActive = other.lineWidthActive();
  m_lineWidthInactive = other.lineWidthInactive();  
  m_lineColor = other.lineColor();
  m_inactiveOpacity = other.inactiveOpacity();

  return *this;
}

bool DocumentModelSegments::fillCorners () const
{
  return m_fillCorners;
}

InactiveOpacity DocumentModelSegments::inactiveOpacity() const
{
  return m_inactiveOpacity;
}

ColorPalette DocumentModelSegments::lineColor() const
{
  return m_lineColor;
}

double DocumentModelSegments::lineWidthActive() const
{
  return m_lineWidthActive;
}

double DocumentModelSegments::lineWidthInactive() const
{
  return m_lineWidthInactive;
}

void DocumentModelSegments::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelSegments::loadXml";

  bool success = true;

  QXmlStreamAttributes attributes = reader.attributes ();

  // Entries that are optional since they were removed in version 13
  //   DOCUMENT_SERIALIZE_SEGMENTS_LINE_WIDTH
  // Entries that are optional since they were added in version 13
  //   DOCUMENT_SERIALIZE_SEGMENTS_INACTIVE_OPACITY
  //   DOCUMENT_SERIALIZE_SEGMENTS_LINE_WIDTH_ACTIVE
  //   DOCUMENT_SERIALIZE_SEGMENTS_LINE_WIDTH_ACTIVE_STRING
  //   DOCUMENT_SERIALIZE_SEGMENTS_LINE_WIDTH_INACTIVE
  //   DOCUMENT_SERIALIZE_SEGMENTS_LINE_WIDTH_INACTIVE_STRING
  if (attributes.hasAttribute(DOCUMENT_SERIALIZE_SEGMENTS_POINT_SEPARATION) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_SEGMENTS_MIN_LENGTH) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_SEGMENTS_FILL_CORNERS) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_SEGMENTS_LINE_WIDTH) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_SEGMENTS_LINE_COLOR)) {

    // Boolean values
    QString fillCorners = attributes.value(DOCUMENT_SERIALIZE_SEGMENTS_FILL_CORNERS).toString();

    setPointSeparation (attributes.value (DOCUMENT_SERIALIZE_SEGMENTS_POINT_SEPARATION).toDouble());
    setMinLength (attributes.value (DOCUMENT_SERIALIZE_SEGMENTS_MIN_LENGTH).toDouble());
    setFillCorners (fillCorners == DOCUMENT_SERIALIZE_BOOL_TRUE);
    setLineColor (static_cast<ColorPalette> (attributes.value (DOCUMENT_SERIALIZE_SEGMENTS_LINE_COLOR).toInt()));
    
    if (attributes.hasAttribute (DOCUMENT_SERIALIZE_SEGMENTS_INACTIVE_OPACITY)) {
      setInactiveOpacity (static_cast<InactiveOpacity>  (attributes.value (DOCUMENT_SERIALIZE_SEGMENTS_INACTIVE_OPACITY).toInt ()));
    } else{
      setInactiveOpacity (DEFAULT_INACTIVE_OPACITY);
    }
    
    // For line widths, first look for single value (corresponding to versions before 13), then look
    // for two values (corresponding to version 13+)
    int lineWidthActive = DEFAULT_LINE_WIDTH_ACTIVE;
    int lineWidthInactive = DEFAULT_LINE_WIDTH_INACTIVE;    
    if (attributes.hasAttribute (DOCUMENT_SERIALIZE_SEGMENTS_LINE_WIDTH)) {
      lineWidthActive = attributes.value (DOCUMENT_SERIALIZE_SEGMENTS_LINE_WIDTH).toInt ();
      lineWidthInactive = attributes.value (DOCUMENT_SERIALIZE_SEGMENTS_LINE_WIDTH).toInt ();      
    } else if (attributes.hasAttribute (DOCUMENT_SERIALIZE_SEGMENTS_LINE_WIDTH_ACTIVE) &&
               attributes.hasAttribute (DOCUMENT_SERIALIZE_SEGMENTS_LINE_WIDTH_INACTIVE)) {
      lineWidthActive = attributes.value (DOCUMENT_SERIALIZE_SEGMENTS_LINE_WIDTH_ACTIVE).toInt ();
      lineWidthInactive = attributes.value (DOCUMENT_SERIALIZE_SEGMENTS_LINE_WIDTH_INACTIVE).toInt ();      
    }
    setLineWidthActive (lineWidthActive);
    setLineWidthInactive (lineWidthInactive);

    // Read until end of this subtree
    while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
    (reader.name() != DOCUMENT_SERIALIZE_SEGMENTS)){
      loadNextFromReader(reader);
      if (reader.atEnd()) {
        success = false;
        break;
      }
    }
  }

  if (!success) {
    reader.raiseError(QObject::tr ("Cannot read segment data"));
  }
}

double DocumentModelSegments::minLength() const
{
  return m_minLength;
}

double DocumentModelSegments::pointSeparation() const
{
  return m_pointSeparation;
}

void DocumentModelSegments::printStream(QString indentation,
                                        QTextStream &str) const
{
  str << indentation << "DocumentModelSegments\n";

  indentation += INDENTATION_DELTA;

  str << indentation << "pointSeparation=" << m_pointSeparation << "\n";
  str << indentation << "minLength=" << m_minLength << "\n";
  str << indentation << "fillCorners=" << (m_fillCorners ? "true" : "false") << "\n";
  str << indentation << "lineWidthActive=" << m_lineWidthActive << "\n";
  str << indentation << "lineWidthInactive=" << m_lineWidthInactive << "\n";  
  str << indentation << "lineColor=" << colorPaletteToString (m_lineColor) << "\n";
  str << indentation << "inactiveOpacity=" << m_inactiveOpacity << "\n";
}

void DocumentModelSegments::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelSegments::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_SEGMENTS);
  writer.writeAttribute(DOCUMENT_SERIALIZE_SEGMENTS_POINT_SEPARATION, QString::number (m_pointSeparation));
  writer.writeAttribute(DOCUMENT_SERIALIZE_SEGMENTS_MIN_LENGTH, QString::number (m_minLength));
  writer.writeAttribute(DOCUMENT_SERIALIZE_SEGMENTS_FILL_CORNERS, m_fillCorners ?
                          DOCUMENT_SERIALIZE_BOOL_TRUE :
                          DOCUMENT_SERIALIZE_BOOL_FALSE);
  writer.writeAttribute(DOCUMENT_SERIALIZE_SEGMENTS_LINE_WIDTH_ACTIVE, QString::number (m_lineWidthActive));
  writer.writeAttribute(DOCUMENT_SERIALIZE_SEGMENTS_LINE_WIDTH_INACTIVE, QString::number (m_lineWidthInactive));  
  writer.writeAttribute(DOCUMENT_SERIALIZE_SEGMENTS_LINE_COLOR, QString::number (m_lineColor));
  writer.writeAttribute(DOCUMENT_SERIALIZE_SEGMENTS_LINE_COLOR_STRING, colorPaletteToString (m_lineColor));
  writer.writeAttribute(DOCUMENT_SERIALIZE_SEGMENTS_INACTIVE_OPACITY, QString::number (m_inactiveOpacity));
  writer.writeEndElement();
}

void DocumentModelSegments::setFillCorners (bool fillCorners)
{
  m_fillCorners = fillCorners;
}

void DocumentModelSegments::setInactiveOpacity (InactiveOpacity inactiveOpacity)
{
  m_inactiveOpacity = inactiveOpacity;
}

void DocumentModelSegments::setLineColor(ColorPalette lineColor)
{
  m_lineColor = lineColor;
}

void DocumentModelSegments::setLineWidthActive(double lineWidthActive)
{
  m_lineWidthActive = lineWidthActive;
}

void DocumentModelSegments::setLineWidthInactive(double lineWidthInactive)
{
  m_lineWidthInactive = lineWidthInactive;
}

void DocumentModelSegments::setMinLength(double minLength)
{
  m_minLength = minLength;
}

void DocumentModelSegments::setPointSeparation(double pointSeparation)
{
  m_pointSeparation = pointSeparation;
}
