/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdGuidelineMoveYR.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include "Xml.h"

const QString CMD_DESCRIPTION ("GuidelineMoveYR");

CmdGuidelineMoveYR::CmdGuidelineMoveYR(MainWindow &mainWindow,
                                       Document &document,
                                       const QString &identifier,
                                       double valueBefore,
                                       double valueAfter) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_identifier (identifier),
  m_valueBefore (valueBefore),
  m_valueAfter (valueAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineMoveYR::CmdGuidelineMoveYR";
}

CmdGuidelineMoveYR::CmdGuidelineMoveYR (MainWindow &mainWindow,
                                        Document &document,
                                        const QString &cmdDescription,
                                        QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineMoveYR::CmdGuidelineMoveYR";

  QXmlStreamAttributes attributes = reader.attributes();

  if (!attributes.hasAttribute(DOCUMENT_SERIALIZE_IDENTIFIER) ||
      !attributes.hasAttribute(DOCUMENT_SERIALIZE_GRAPH_BEFORE) ||
      !attributes.hasAttribute(DOCUMENT_SERIALIZE_GRAPH_AFTER)) {
    xmlExitWithError (reader,
                      QString ("%1 %2 %3 %4 %5 %6")
                      .arg (QObject::tr ("Missing attribute(s)"))
                      .arg (DOCUMENT_SERIALIZE_IDENTIFIER)
                      .arg (QObject::tr (","))
                      .arg (DOCUMENT_SERIALIZE_GRAPH_BEFORE)
                      .arg (QObject::tr ("and/or"))
                      .arg (DOCUMENT_SERIALIZE_GRAPH_AFTER));
  }

  m_identifier = attributes.value(DOCUMENT_SERIALIZE_IDENTIFIER).toString();
  m_valueBefore = attributes.value(DOCUMENT_SERIALIZE_GRAPH_BEFORE).toDouble();
  m_valueAfter = attributes.value(DOCUMENT_SERIALIZE_GRAPH_AFTER).toDouble();
}

CmdGuidelineMoveYR::~CmdGuidelineMoveYR ()
{
}

void CmdGuidelineMoveYR::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineMoveYR::cmdRedo"
                              << " identifier=" << m_identifier.toLatin1().data()
                              << " value=" << m_valueAfter;

  mainWindow().guidelineMoveYR (m_identifier,
                                m_valueAfter);
}

void CmdGuidelineMoveYR::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineMoveYR::cmdUndo"
                              << " identifier=" << m_identifier.toLatin1().data()
                              << " value=" << m_valueBefore;

  mainWindow().guidelineMoveYR (m_identifier,
                                m_valueBefore);
}

void CmdGuidelineMoveYR::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_GUIDELINE_MOVE_Y_R);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  writer.writeAttribute(DOCUMENT_SERIALIZE_IDENTIFIER, m_identifier);
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRAPH_BEFORE, QString::number (m_valueBefore));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GRAPH_AFTER, QString::number (m_valueAfter));
  writer.writeEndElement();
}
