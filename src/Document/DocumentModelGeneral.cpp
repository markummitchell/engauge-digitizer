/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMediator.h"
#include "DocumentModelGeneral.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include <QObject>
#include <QSettings>
#include <QTextStream>
#include "QtToString.h"
#include <QXmlStreamWriter>
#include "Settings.h"
#include "Xml.h"

const int DEFAULT_CURSOR_SIZE = 3;
const int DEFAULT_EXTRA_PRECISION = 1;

DocumentModelGeneral::DocumentModelGeneral() :
  m_cursorSize (DEFAULT_CURSOR_SIZE),
  m_extraPrecision (DEFAULT_EXTRA_PRECISION)
{
  QSettings settings (SETTINGS_ENGAUGE, SETTINGS_DIGITIZER);
  settings.beginGroup (SETTINGS_GROUP_GENERAL);

  m_cursorSize = settings.value (SETTINGS_GENERAL_CURSOR_SIZE,
                                 QVariant (DEFAULT_CURSOR_SIZE)).toInt();
  m_extraPrecision = settings.value (SETTINGS_GENERAL_EXTRA_PRECISION,
                                     QVariant (DEFAULT_EXTRA_PRECISION)).toInt();
  settings.endGroup ();
}

DocumentModelGeneral::DocumentModelGeneral(const Document &document) :
  m_cursorSize (document.modelGeneral().cursorSize()),
  m_extraPrecision (document.modelGeneral().extraPrecision())
{
}

DocumentModelGeneral::DocumentModelGeneral(const DocumentModelGeneral &other) :
  m_cursorSize (other.cursorSize()),
  m_extraPrecision (other.extraPrecision())
{
}

DocumentModelGeneral &DocumentModelGeneral::operator=(const DocumentModelGeneral &other)
{
  m_cursorSize = other.cursorSize();
  m_extraPrecision = other.extraPrecision();

  return *this;
}

int DocumentModelGeneral::cursorSize() const
{
  return m_cursorSize;
}

int DocumentModelGeneral::extraPrecision() const
{
  return m_extraPrecision;
}

void DocumentModelGeneral::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelGeneral::loadXml";

  bool success = true;

  QXmlStreamAttributes attributes = reader.attributes();

  if (attributes.hasAttribute(DOCUMENT_SERIALIZE_GENERAL_CURSOR_SIZE) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_GENERAL_EXTRA_PRECISION)) {

    setCursorSize (attributes.value(DOCUMENT_SERIALIZE_GENERAL_CURSOR_SIZE).toInt());
    setExtraPrecision (attributes.value(DOCUMENT_SERIALIZE_GENERAL_EXTRA_PRECISION).toInt());

    // Read until end of this subtree
    while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
    (reader.name() != DOCUMENT_SERIALIZE_GENERAL &&
     reader.name() != DOCUMENT_SERIALIZE_COMMON)){
      loadNextFromReader(reader);
      if (reader.atEnd()) {
        success = false;
        break;
      }
    }
  }

  if (!success) {
    reader.raiseError (QObject::tr ("Cannot read general data"));
  }
}

void DocumentModelGeneral::printStream(QString indentation,
                                      QTextStream &str) const
{
  str << indentation << "DocumentModelGeneral\n";

  indentation += INDENTATION_DELTA;

  str << indentation << "cursorSize=" << m_cursorSize << "\n";
  str << indentation << "extraPrecision=" << m_extraPrecision << "\n";
}

void DocumentModelGeneral::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelGeneral::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_GENERAL);
  writer.writeAttribute(DOCUMENT_SERIALIZE_GENERAL_CURSOR_SIZE, QString::number (m_cursorSize));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GENERAL_EXTRA_PRECISION, QString::number (m_extraPrecision));
  writer.writeEndElement();
}

void DocumentModelGeneral::setCursorSize(int cursorSize)
{
  m_cursorSize = cursorSize;
}

void DocumentModelGeneral::setExtraPrecision (int extraPrecision)
{
  m_extraPrecision = extraPrecision;
}
