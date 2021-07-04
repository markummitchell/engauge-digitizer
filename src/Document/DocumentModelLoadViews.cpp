/******************************************************************************************************
 * (C) 2021 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Document.h"
#include "DocumentModelLoadViews.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include <QObject>
#include <QTextStream>
#include "QtToString.h"
#include <QXmlStreamWriter>
#include "Xml.h"

DocumentModelLoadViews::DocumentModelLoadViews() :
  m_gridlines (false),
  m_guidelines (false)
{
}

DocumentModelLoadViews::DocumentModelLoadViews(const Document &document) :
  m_gridlines (document.modelLoadViews().gridlines ()),
  m_guidelines (document.modelLoadViews().guidelines ())
{
}

DocumentModelLoadViews::DocumentModelLoadViews(const DocumentModelLoadViews &other) :
  m_gridlines (other.gridlines ()),
  m_guidelines (other.guidelines ())
{
}

DocumentModelLoadViews::DocumentModelLoadViews(bool gridlines,
                                               bool guidelines) :
  m_gridlines (gridlines),
  m_guidelines (guidelines)
{
}

DocumentModelLoadViews &DocumentModelLoadViews::operator=(const DocumentModelLoadViews &other)
{
  m_gridlines = other.gridlines ();
  m_guidelines = other.guidelines ();

  return *this;
}

bool DocumentModelLoadViews::gridlines () const
{
  return m_gridlines;
}

bool DocumentModelLoadViews::guidelines () const
{
  return m_guidelines;
}

void DocumentModelLoadViews::loadXml(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelLoadViews::loadXml";

  bool success = true;

  QXmlStreamAttributes attributes = reader.attributes();

  if (attributes.hasAttribute(DOCUMENT_SERIALIZE_LOAD_VIEWS_GRIDLINES) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_LOAD_VIEWS_GUIDELINES)) {

    // Boolean values
    QString stringGridlines = attributes.value (DOCUMENT_SERIALIZE_LOAD_VIEWS_GRIDLINES).toString();
    QString stringGuidelines = attributes.value (DOCUMENT_SERIALIZE_LOAD_VIEWS_GUIDELINES).toString();

    setGridlines (stringGridlines == DOCUMENT_SERIALIZE_BOOL_TRUE);
    setGuidelines (stringGuidelines == DOCUMENT_SERIALIZE_BOOL_TRUE);
    
    // Read until end of this subtree
    while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
    (reader.name() != DOCUMENT_SERIALIZE_LOAD_VIEWS)){
      loadNextFromReader(reader);
      if (reader.atEnd()) {
        success = false;
        break;
      }
    }
  }

  if (!success) {
    reader.raiseError (QObject::tr ("Cannot read settings for views loading"));
  }
}

void DocumentModelLoadViews::printStream(QString indentation,
                                      QTextStream &str) const
{
  str << indentation << "DocumentModelLoadViews\n";

  indentation += INDENTATION_DELTA;

  str << indentation << "gridlines=" << (m_gridlines ? "yes" : "no") << "\n";
  str << indentation << "guidelines=" << (m_guidelines ? "yes" : "no") << "\n";
}

void DocumentModelLoadViews::saveXml(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelLoadViews::saveXml";

  writer.writeStartElement(DOCUMENT_SERIALIZE_LOAD_VIEWS);
  writer.writeAttribute(DOCUMENT_SERIALIZE_LOAD_VIEWS_GRIDLINES, m_gridlines ?
                        DOCUMENT_SERIALIZE_BOOL_TRUE :
                        DOCUMENT_SERIALIZE_BOOL_FALSE);
  writer.writeAttribute(DOCUMENT_SERIALIZE_LOAD_VIEWS_GUIDELINES, m_guidelines ?
                        DOCUMENT_SERIALIZE_BOOL_TRUE :
                        DOCUMENT_SERIALIZE_BOOL_FALSE);  
  writer.writeEndElement();
}

void DocumentModelLoadViews::setGridlines (bool gridlines)
{
  m_gridlines = gridlines;
}

void DocumentModelLoadViews::setGuidelines (bool guidelines)
{
  m_guidelines = guidelines;
}
