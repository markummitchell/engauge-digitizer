/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdGuidelineRemoveYR.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include "Xml.h"

const QString CMD_DESCRIPTION ("GuidelineRemoveYR");

CmdGuidelineRemoveYR::CmdGuidelineRemoveYR(MainWindow &mainWindow,
                                           Document &document,
                                           const QString &identifier,
                                           double valueBefore) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_identifier (identifier),
  m_valueBefore (valueBefore)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineRemoveYR::CmdGuidelineRemoveYR";
}

CmdGuidelineRemoveYR::CmdGuidelineRemoveYR (MainWindow &mainWindow,
                                            Document &document,
                                            const QString &cmdDescription,
                                            QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineRemoveYR::CmdGuidelineRemoveYR";

  QXmlStreamAttributes attributes = reader.attributes();

  if (!attributes.hasAttribute(DOCUMENT_SERIALIZE_IDENTIFIER) ||
      !attributes.hasAttribute(DOCUMENT_SERIALIZE_GRAPH_BEFORE)) {
    xmlExitWithError (reader,
                      QString ("%1 %2 %3 %4")
                      .arg (QObject::tr ("Missing attribute(s)"))
                      .arg (DOCUMENT_SERIALIZE_IDENTIFIER)
                      .arg (QObject::tr ("and/or"))
                      .arg (DOCUMENT_SERIALIZE_GRAPH_BEFORE));
  }

  m_identifier = attributes.value(DOCUMENT_SERIALIZE_IDENTIFIER).toString();
  m_valueBefore = attributes.value(DOCUMENT_SERIALIZE_GRAPH_BEFORE).toDouble();
}

CmdGuidelineRemoveYR::~CmdGuidelineRemoveYR ()
{
}

void CmdGuidelineRemoveYR::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineRemoveYR::cmdRedo"
                              << " identifier=" << m_identifier.toLatin1().data();

  mainWindow().guidelineRemove (m_identifier);
}

void CmdGuidelineRemoveYR::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineRemoveYR::cmdUndo"
                              << " identifier=" << m_identifier.toLatin1().data()
                              << " value=" << m_valueBefore;

  mainWindow().guidelineAddYR (m_identifier,
                               m_valueBefore);
}

void CmdGuidelineRemoveYR::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_GUIDELINE_REMOVE_Y_R);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  writer.writeAttribute(DOCUMENT_SERIALIZE_IDENTIFIER, m_identifier);
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRAPH_BEFORE, QString::number (m_valueBefore));
  writer.writeEndElement();
}
