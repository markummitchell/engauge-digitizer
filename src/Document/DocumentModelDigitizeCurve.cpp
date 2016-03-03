/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMediator.h"
#include "DocumentModelDigitizeCurve.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include <QObject>
#include <QTextStream>
#include <QXmlStreamWriter>
#include "Xml.h"

const bool DEFAULT_CURSOR_STANDARD_CROSS = true;
const int DEFAULT_CURSOR_INNER_RADIUS = 5;
const int DEFAULT_CURSOR_LINE_WIDTH = 2;
const CursorSize DEFAULT_CURSOR_SIZE = CURSOR_SIZE_32;

DocumentModelDigitizeCurve::DocumentModelDigitizeCurve() :
  m_cursorStandardCross (DEFAULT_CURSOR_STANDARD_CROSS),
  m_cursorInnerRadius (DEFAULT_CURSOR_INNER_RADIUS),
  m_cursorLineWidth (DEFAULT_CURSOR_LINE_WIDTH),
  m_cursorSize (DEFAULT_CURSOR_SIZE)
{
}

DocumentModelDigitizeCurve::DocumentModelDigitizeCurve(const Document &document) :
  m_cursorStandardCross (document.modelDigitizeCurve().cursorStandardCross()),
  m_cursorInnerRadius (document.modelDigitizeCurve().cursorInnerRadius()),
  m_cursorLineWidth (document.modelDigitizeCurve().cursorLineWidth()),
  m_cursorSize (document.modelDigitizeCurve().cursorSize())
{
}

DocumentModelDigitizeCurve::DocumentModelDigitizeCurve(const DocumentModelDigitizeCurve &other) :
  m_cursorStandardCross (other.cursorStandardCross()),
  m_cursorInnerRadius (other.cursorInnerRadius()),
  m_cursorLineWidth (other.cursorLineWidth()),
  m_cursorSize (other.cursorSize ())
{
}

DocumentModelDigitizeCurve &DocumentModelDigitizeCurve::operator=(const DocumentModelDigitizeCurve &other)
{
  m_cursorStandardCross = other.cursorStandardCross();
  m_cursorInnerRadius = other.cursorInnerRadius();
  m_cursorLineWidth = other.cursorLineWidth();
  m_cursorSize = other.cursorSize ();

  return *this;
}

int DocumentModelDigitizeCurve::cursorInnerRadius() const
{
  return m_cursorInnerRadius;
}

int DocumentModelDigitizeCurve::cursorLineWidth() const
{
  return m_cursorLineWidth;
}

CursorSize DocumentModelDigitizeCurve::cursorSize() const
{
  return m_cursorSize;
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
      attributes.hasAttribute(DOCUMENT_SERIALIZE_DIGITIZE_CURVE_CURSOR_LINE_WIDTH) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_DIGITIZE_CURVE_CURSOR_SIZE) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_DIGITIZE_CURVE_CURSOR_STANDARD_CROSS)) {

    // Boolean values
    QString standardCrossValue = attributes.value(DOCUMENT_SERIALIZE_DIGITIZE_CURVE_CURSOR_STANDARD_CROSS).toString();

    setCursorInnerRadius (attributes.value(DOCUMENT_SERIALIZE_DIGITIZE_CURVE_CURSOR_INNER_RADIUS).toInt());
    setCursorLineWidth (attributes.value(DOCUMENT_SERIALIZE_DIGITIZE_CURVE_CURSOR_LINE_WIDTH).toInt());
    setCursorSize ((CursorSize) attributes.value(DOCUMENT_SERIALIZE_DIGITIZE_CURVE_CURSOR_SIZE).toInt());
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
    reader.raiseError (QObject::tr ("Cannot read digitize curve data"));
  }
}

void DocumentModelDigitizeCurve::printStream(QString indentation,
                                        QTextStream &str) const
{
  str << indentation << "DocumentModelDigitizeCurve\n";

  indentation += INDENTATION_DELTA;

  str << indentation << "cursorStandardCross=" << (m_cursorStandardCross ? "true" : "false") << "\n";
  str << indentation << "cursorInnerRadius=" << m_cursorInnerRadius << "\n";
  str << indentation << "cursorSize=" << m_cursorSize << "\n";
  str << indentation << "cursorLineWidth=" << m_cursorLineWidth << "\n";
}

void DocumentModelDigitizeCurve::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelDigitizeCurve::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_DIGITIZE_CURVE);
  writer.writeAttribute(DOCUMENT_SERIALIZE_DIGITIZE_CURVE_CURSOR_INNER_RADIUS, QString::number (m_cursorInnerRadius));
  writer.writeAttribute(DOCUMENT_SERIALIZE_DIGITIZE_CURVE_CURSOR_LINE_WIDTH, QString::number (m_cursorLineWidth));
  writer.writeAttribute(DOCUMENT_SERIALIZE_DIGITIZE_CURVE_CURSOR_SIZE, QString::number (m_cursorSize));
  writer.writeAttribute(DOCUMENT_SERIALIZE_DIGITIZE_CURVE_CURSOR_STANDARD_CROSS, m_cursorStandardCross ?
                          DOCUMENT_SERIALIZE_BOOL_TRUE :
                          DOCUMENT_SERIALIZE_BOOL_FALSE);
  writer.writeEndElement();
}

void DocumentModelDigitizeCurve::setCursorInnerRadius (int cursorInnerRadius)
{
  m_cursorInnerRadius = cursorInnerRadius;
}

void DocumentModelDigitizeCurve::setCursorLineWidth (int cursorLineWidth)
{
  m_cursorLineWidth = cursorLineWidth;
}

void DocumentModelDigitizeCurve::setCursorSize (CursorSize cursorSize)
{
  m_cursorSize = cursorSize;
}

void DocumentModelDigitizeCurve::setCursorStandardCross (bool cursorStandardCross)
{
  m_cursorStandardCross = cursorStandardCross;
}
