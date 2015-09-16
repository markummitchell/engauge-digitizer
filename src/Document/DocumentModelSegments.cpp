#include "CmdMediator.h"
#include "DocumentModelSegments.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include <QTextStream>
#include <QXmlStreamWriter>
#include "Xml.h"

const double DEFAULT_POINT_SEPARATION = 25;
const double DEFAULT_MIN_LENGTH = 2;
const double DEFAULT_LINE_WIDTH = 4;
const ColorPalette DEFAULT_LINE_COLOR (COLOR_PALETTE_GREEN);

DocumentModelSegments::DocumentModelSegments() :
  m_pointSeparation (DEFAULT_POINT_SEPARATION),
  m_minLength (DEFAULT_MIN_LENGTH),
  m_fillCorners (false),
  m_lineWidth (DEFAULT_LINE_WIDTH),
  m_lineColor (DEFAULT_LINE_COLOR)
{
}

DocumentModelSegments::DocumentModelSegments(const Document &document) :
  m_pointSeparation (document.modelSegments().pointSeparation()),
  m_minLength (document.modelSegments().minLength()),
  m_fillCorners (document.modelSegments().fillCorners()),
  m_lineWidth (document.modelSegments().lineWidth()),
  m_lineColor (document.modelSegments().lineColor())
{
}

DocumentModelSegments::DocumentModelSegments(const DocumentModelSegments &other) :
  m_pointSeparation (other.pointSeparation()),
  m_minLength (other.minLength()),
  m_fillCorners (other.fillCorners ()),
  m_lineWidth (other.lineWidth()),
  m_lineColor (other.lineColor())
{
}

DocumentModelSegments &DocumentModelSegments::operator=(const DocumentModelSegments &other)
{
  m_pointSeparation = other.pointSeparation();
  m_minLength = other.minLength();
  m_fillCorners = other.fillCorners ();
  m_lineWidth = other.lineWidth();
  m_lineColor = other.lineColor();

  return *this;
}

bool DocumentModelSegments::fillCorners () const
{
  return m_fillCorners;
}

ColorPalette DocumentModelSegments::lineColor() const
{
  return m_lineColor;
}

double DocumentModelSegments::lineWidth() const
{
  return m_lineWidth;
}

void DocumentModelSegments::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelSegments::loadXml";

  bool success = true;

  // Read until end of this subtree
  while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
  (reader.name() != DOCUMENT_SERIALIZE_SEGMENTS)){
    loadNextFromReader(reader);
    if (reader.atEnd()) {
      success = false;
      break;
    }
  }

  if (!success) {
    reader.raiseError("Cannot read segment data");
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
  str << indentation << "lineWidth=" << m_lineWidth << "\n";
  str << indentation << "lineColor=" << colorPaletteToString (m_lineColor) << "\n";
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
  writer.writeAttribute(DOCUMENT_SERIALIZE_SEGMENTS_LINE_WIDTH, QString::number (m_lineWidth));
  writer.writeAttribute(DOCUMENT_SERIALIZE_SEGMENTS_LINE_COLOR, QString::number (m_lineColor));
  writer.writeAttribute(DOCUMENT_SERIALIZE_SEGMENTS_LINE_COLOR_STRING, colorPaletteToString (m_lineColor));
  writer.writeEndElement();
}

void DocumentModelSegments::setFillCorners (bool fillCorners)
{
  m_fillCorners = fillCorners;
}

void DocumentModelSegments::setLineColor(ColorPalette lineColor)
{
  m_lineColor = lineColor;
}

void DocumentModelSegments::setLineWidth(double lineWidth)
{
  m_lineWidth = lineWidth;
}

void DocumentModelSegments::setMinLength(double minLength)
{
  m_minLength = minLength;
}

void DocumentModelSegments::setPointSeparation(double pointSeparation)
{
  m_pointSeparation = pointSeparation;
}
