/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include "PointIdentifiers.h"
#include <QObject>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "Xml.h"

PointIdentifiers::PointIdentifiers()
{
}

bool PointIdentifiers::contains(const QString &pointIdentifier) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "PointIdentifiers::contains"
                               << " pointCount=" << m_pointIdentifiers.count();

  return m_pointIdentifiers.contains (pointIdentifier);
}

int PointIdentifiers::count() const
{
  return m_pointIdentifiers.count();
}

QString PointIdentifiers::getKey (int i) const
{
  ENGAUGE_ASSERT (i < m_pointIdentifiers.count());

  QList<QString> keys = m_pointIdentifiers.keys();

  return keys.at(i);
}

bool PointIdentifiers::getValue (const QString &pointIdentifier) const
{
  ENGAUGE_ASSERT (m_pointIdentifiers.contains (pointIdentifier));

  return m_pointIdentifiers [pointIdentifier];
}

void PointIdentifiers::loadXml (QXmlStreamReader &reader)
{
  bool success = true;

  // Read through each DOCUMENT_SERIALIZE_POINT_IDENTIFIER until end of DOCUMENT_SERIALIZE_POINT_IDENTIFIERS is encountered
  while (loadNextFromReader (reader)) {

    if (reader.atEnd() || reader.hasError ()) {
      success = false;
      break;
    }

    if ((reader.tokenType() == QXmlStreamReader::EndElement) &&
         (reader.name() == DOCUMENT_SERIALIZE_POINT_IDENTIFIERS)) {
      break;
    }

    // Not done yet
    if ((reader.tokenType() == QXmlStreamReader::StartElement) &&
        (reader.name() == DOCUMENT_SERIALIZE_POINT_IDENTIFIER)) {

      // This is an entry that we need to add
      QXmlStreamAttributes attributes = reader.attributes();

      if (attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_IDENTIFIER_NAME) &&
          attributes.hasAttribute(DOCUMENT_SERIALIZE_POINT_IDENTIFIER_VALUE)) {

        QString valueStr = attributes.value (DOCUMENT_SERIALIZE_POINT_IDENTIFIER_VALUE).toString();

        QString identifier = attributes.value (DOCUMENT_SERIALIZE_POINT_IDENTIFIER_NAME).toString();
        bool value = (valueStr == DOCUMENT_SERIALIZE_BOOL_TRUE);

        m_pointIdentifiers [identifier] = value;
      }
    }
  }

  if (!success) {
    reader.raiseError (QObject::tr ("Cannot read point identifiers"));
  }
}

void PointIdentifiers::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_POINT_IDENTIFIERS);
  PointIdentifiersInternal::const_iterator itr;
  for (itr = m_pointIdentifiers.begin(); itr != m_pointIdentifiers.end (); itr++) {
    QString identifier = itr.key();
    bool value = itr.value();
    writer.writeStartElement (DOCUMENT_SERIALIZE_POINT_IDENTIFIER);
    writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_IDENTIFIER_NAME, identifier);
    writer.writeAttribute(DOCUMENT_SERIALIZE_POINT_IDENTIFIER_VALUE,
                          value ? DOCUMENT_SERIALIZE_BOOL_TRUE : DOCUMENT_SERIALIZE_BOOL_FALSE);
    writer.writeEndElement();
  }
  writer.writeEndElement();
}

void PointIdentifiers::setKeyValue (const QString &pointIdentifier,
                                    bool value)
{
  m_pointIdentifiers [pointIdentifier] = value;
}
