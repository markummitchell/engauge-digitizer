#include "CmdMediator.h"
#include "DocumentModelCommon.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include <QTextStream>
#include "QtToString.h"
#include <QXmlStreamWriter>
#include "Xml.h"

const int DEFAULT_CURSOR_SIZE = 3;
const int DEFAULT_EXTRA_PRECISION = 1;

DocumentModelCommon::DocumentModelCommon() :
  m_cursorSize (DEFAULT_CURSOR_SIZE),
  m_extraPrecision (DEFAULT_EXTRA_PRECISION)
{
}

DocumentModelCommon::DocumentModelCommon(const Document &document) :
  m_cursorSize (document.modelCommon().cursorSize()),
  m_extraPrecision (document.modelCommon().extraPrecision())
{
}

DocumentModelCommon::DocumentModelCommon(const DocumentModelCommon &other) :
  m_cursorSize (other.cursorSize()),
  m_extraPrecision (other.extraPrecision())
{
}

DocumentModelCommon &DocumentModelCommon::operator=(const DocumentModelCommon &other)
{
  m_cursorSize = other.cursorSize();
  m_extraPrecision = other.extraPrecision();

  return *this;
}

int DocumentModelCommon::cursorSize() const
{
  return m_cursorSize;
}

int DocumentModelCommon::extraPrecision() const
{
  return m_extraPrecision;
}

void DocumentModelCommon::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelCommon::loadXml";

  bool success = true;

  QXmlStreamAttributes attributes = reader.attributes();

  if (attributes.hasAttribute(DOCUMENT_SERIALIZE_COMMON_CURSOR_SIZE) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_COMMON_EXTRA_PRECISION)) {

    setCursorSize (attributes.value(DOCUMENT_SERIALIZE_COMMON_CURSOR_SIZE).toInt());
    setExtraPrecision (attributes.value(DOCUMENT_SERIALIZE_COMMON_EXTRA_PRECISION).toInt());

    // Read until end of this subtree
    while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
    (reader.name() != DOCUMENT_SERIALIZE_COMMON)){
      loadNextFromReader(reader);
      if (reader.atEnd()) {
        success = false;
        break;
      }
    }
  }

  if (!success) {
    reader.raiseError ("Cannot read axes checker data");
  }
}

void DocumentModelCommon::printStream(QString indentation,
                                      QTextStream &str) const
{
  str << indentation << "DocumentModelCommon\n";

  indentation += INDENTATION_DELTA;

  str << indentation << "cursorSize=" << m_cursorSize << "\n";
  str << indentation << "extraPrecision=" << m_extraPrecision << "\n";
}

void DocumentModelCommon::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelCommon::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_COMMON);
  writer.writeAttribute(DOCUMENT_SERIALIZE_COMMON_CURSOR_SIZE, QString::number (m_cursorSize));
  writer.writeAttribute(DOCUMENT_SERIALIZE_COMMON_EXTRA_PRECISION, QString::number (m_extraPrecision));
  writer.writeEndElement();
}

void DocumentModelCommon::setCursorSize(int cursorSize)
{
  m_cursorSize = cursorSize;
}

void DocumentModelCommon::setExtraPrecision (int extraPrecision)
{
  m_extraPrecision = extraPrecision;
}
