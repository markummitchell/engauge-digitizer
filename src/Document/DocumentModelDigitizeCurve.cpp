#include "CmdMediator.h"
#include "DocumentModelDigitizeCurve.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include <QTextStream>
#include <QXmlStreamWriter>
#include "Xml.h"

const bool DEFAULT_CURSOR_STANDARD_CROSS = true;
const int DEFAULT_CURSOR_INNER_RADIUS = 5;
const int DEFAULT_CURSOR_LINE_LENGTH = 10;
const int DEFAULT_CURSOR_LINE_WIDTH = 2;

DocumentModelDigitizeCurve::DocumentModelDigitizeCurve() :
  m_cursorStandardCross (DEFAULT_CURSOR_STANDARD_CROSS),
  m_cursorInnerRadius (DEFAULT_CURSOR_INNER_RADIUS),
  m_cursorLineLength (DEFAULT_CURSOR_LINE_LENGTH),
  m_cursorLineWidth (DEFAULT_CURSOR_LINE_WIDTH)
{
}

DocumentModelDigitizeCurve::DocumentModelDigitizeCurve(const Document &document) :
  m_cursorStandardCross (document.modelDigitizeCurve().cursorStandardCross()),
  m_cursorInnerRadius (document.modelDigitizeCurve().cursorInnerRadius()),
  m_cursorLineLength (document.modelDigitizeCurve().cursorLineLength()),
  m_cursorLineWidth (document.modelDigitizeCurve().cursorLineWidth())
{
}

DocumentModelDigitizeCurve::DocumentModelDigitizeCurve(const DocumentModelDigitizeCurve &other) :
  m_cursorStandardCross (other.cursorStandardCross()),
  m_cursorInnerRadius (other.cursorInnerRadius()),
  m_cursorLineLength (other.cursorLineLength ()),
  m_cursorLineWidth (other.cursorLineWidth())
{
}

DocumentModelDigitizeCurve &DocumentModelDigitizeCurve::operator=(const DocumentModelDigitizeCurve &other)
{
  m_cursorStandardCross = other.cursorStandardCross();
  m_cursorInnerRadius = other.cursorInnerRadius();
  m_cursorLineLength = other.cursorLineLength ();
  m_cursorLineWidth = other.cursorLineWidth();

  return *this;
}

int DocumentModelDigitizeCurve::cursorInnerRadius() const
{
  return m_cursorInnerRadius;
}

int DocumentModelDigitizeCurve::cursorLineLength() const
{
  return m_cursorLineLength;
}

int DocumentModelDigitizeCurve::cursorLineWidth() const
{
  return m_cursorLineWidth;
}

bool DocumentModelDigitizeCurve::cursorStandardCross () const
{
  return m_cursorStandardCross;
}

void DocumentModelDigitizeCurve::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelDigitizeCurve::loadXml";

  bool success = true;

  QXmlStreamAttributes attributes = reader.attributes();

  if (attributes.hasAttribute(DOCUMENT_SERIALIZE_DIGITIZE_CURVE_CURSOR_INNER_RADIUS) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_DIGITIZE_CURVE_LINE_LENGTH) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_DIGITIZE_CURVE_LINE_WIDTH) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_DIGITIZE_CURVE_CURSOR_STANDARD_CROSS)) {

    // Boolean values
    QString standardCrossValue = attributes.value(DOCUMENT_SERIALIZE_DIGITIZE_CURVE_CURSOR_STANDARD_CROSS).toString();

    setCursorInnerRadius (attributes.value(DOCUMENT_SERIALIZE_DIGITIZE_CURVE_CURSOR_INNER_RADIUS).toInt());
    setCursorLineLength (attributes.value(DOCUMENT_SERIALIZE_DIGITIZE_CURVE_LINE_LENGTH).toInt());
    setCursorLineWidth (attributes.value(DOCUMENT_SERIALIZE_DIGITIZE_CURVE_LINE_WIDTH).toInt());
    setCursorStandardCross (standardCrossValue == DOCUMENT_SERIALIZE_BOOL_TRUE);

    // Read until end of this subtree
    while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
    (reader.name() != DOCUMENT_SERIALIZE_DIGITIZE_CURVE)){
      loadNextFromReader(reader);
      if (reader.atEnd()) {
        success = false;
        break;
      }
    }
  }

  if (!success) {
    reader.raiseError ("Cannot read digitize curve data");
  }
}

void DocumentModelDigitizeCurve::printStream(QString indentation,
                                        QTextStream &str) const
{
  str << indentation << "DocumentModelDigitizeCurve\n";

  indentation += INDENTATION_DELTA;

  str << indentation << "cursorStandardCross=" << (m_cursorStandardCross ? "true" : "false") << "\n";
  str << indentation << "cursorInnerRadius=" << m_cursorInnerRadius << "\n";
  str << indentation << "cursorLineLength=" << m_cursorLineLength << "\n";
  str << indentation << "cursorLineWidth=" << m_cursorLineWidth << "\n";
}

void DocumentModelDigitizeCurve::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelDigitizeCurve::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_DIGITIZE_CURVE);
  writer.writeAttribute(DOCUMENT_SERIALIZE_DIGITIZE_CURVE_CURSOR_INNER_RADIUS, QString::number (m_cursorInnerRadius));
  writer.writeAttribute(DOCUMENT_SERIALIZE_DIGITIZE_CURVE_LINE_LENGTH, QString::number (m_cursorLineLength));
  writer.writeAttribute(DOCUMENT_SERIALIZE_DIGITIZE_CURVE_LINE_WIDTH, QString::number (m_cursorLineWidth));
  writer.writeAttribute(DOCUMENT_SERIALIZE_DIGITIZE_CURVE_CURSOR_STANDARD_CROSS, m_cursorStandardCross ?
                          DOCUMENT_SERIALIZE_BOOL_TRUE :
                          DOCUMENT_SERIALIZE_BOOL_FALSE);
  writer.writeEndElement();
}

void DocumentModelDigitizeCurve::setCursorInnerRadius (int cursorInnerRadius)
{
  m_cursorInnerRadius = cursorInnerRadius;
}

void DocumentModelDigitizeCurve::setCursorLineLength (int cursorLineLength)
{
  m_cursorLineLength = cursorLineLength;
}

void DocumentModelDigitizeCurve::setCursorLineWidth (int cursorLineWidth)
{
  m_cursorLineWidth = cursorLineWidth;
}

void DocumentModelDigitizeCurve::setCursorStandardCross (bool cursorStandardCross)
{
  m_cursorStandardCross = cursorStandardCross;
}
