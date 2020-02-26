/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdGuidelineAddYR.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "GuidelineIdentifierGenerator.h"
#include "Logger.h"
#include "MainWindow.h"
#include "Xml.h"

const QString CMD_DESCRIPTION ("GuidelineAddYR");

CmdGuidelineAddYR::CmdGuidelineAddYR(MainWindow &mainWindow,
                                     Document &document,
                                     double value) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_identifier (GuidelineIdentifierGenerator::next ()),
  m_value (value)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineAddYR::CmdGuidelineAddYR";
}

CmdGuidelineAddYR::CmdGuidelineAddYR (MainWindow &mainWindow,
                                      Document &document,
                                      const QString &cmdDescription,
                                      QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineAddYR::CmdGuidelineAddYR";

  QXmlStreamAttributes attributes = reader.attributes();

  if (!attributes.hasAttribute(DOCUMENT_SERIALIZE_IDENTIFIER) ||
      !attributes.hasAttribute(DOCUMENT_SERIALIZE_GRAPH_AFTER)) {
    xmlExitWithError (reader,
                      QString ("%1 %2 %3 %4")
                      .arg (QObject::tr ("Missing attribute(s)"))
                      .arg (DOCUMENT_SERIALIZE_IDENTIFIER)
                      .arg (QObject::tr ("and/or"))
                      .arg (DOCUMENT_SERIALIZE_GRAPH_AFTER));
  }

  m_identifier = attributes.value(DOCUMENT_SERIALIZE_IDENTIFIER).toString();
  m_value = attributes.value(DOCUMENT_SERIALIZE_GRAPH_AFTER).toDouble();
}

CmdGuidelineAddYR::~CmdGuidelineAddYR ()
{
}

void CmdGuidelineAddYR::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineAddYR::cmdRedo"
                              << " identifier=" << m_identifier.toLatin1().data()
                              << " value=" << m_value;

  mainWindow().guidelineAddYR (m_identifier,
                               m_value);
}

void CmdGuidelineAddYR::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineAddYR::cmdUndo"
                              << " identifier=" << m_identifier.toLatin1().data();

  mainWindow().guidelineRemove (m_identifier);
}

void CmdGuidelineAddYR::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_GUIDELINE_ADD_Y_R);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  writer.writeAttribute(DOCUMENT_SERIALIZE_IDENTIFIER, m_identifier);
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRAPH_AFTER, QString::number (m_value));
  writer.writeEndElement();
}
