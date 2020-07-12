/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdDigitizeState.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include "Xml.h"

const QString CMD_DESCRIPTION ("DigitizeState");

CmdDigitizeState::CmdDigitizeState(MainWindow &mainWindow,
                                   Document &document,
                                   DigitizeState stateBefore,
                                   DigitizeState stateAfter) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_stateBefore (stateBefore),
  m_stateAfter (stateAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdDigitizeState::CmdDigitizeState";
}

CmdDigitizeState::CmdDigitizeState (MainWindow &mainWindow,
                                    Document &document,
                                    const QString &cmdDescription,
                                    QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdDigitizeState::CmdDigitizeState";

  QXmlStreamAttributes attributes = reader.attributes();

  if (!attributes.hasAttribute(DOCUMENT_SERIALIZE_DIGITIZE_STATE_BEFORE) ||
      !attributes.hasAttribute(DOCUMENT_SERIALIZE_DIGITIZE_STATE_AFTER)) {
    xmlExitWithError (reader,
                      QString ("%1 %2 %3 %4")
                      .arg (QObject::tr ("Missing attribute(s)"))
                      .arg (DOCUMENT_SERIALIZE_DIGITIZE_STATE_BEFORE)
                      .arg (QObject::tr ("and/or"))
                      .arg (DOCUMENT_SERIALIZE_DIGITIZE_STATE_AFTER));
  }

  m_stateBefore = static_cast<DigitizeState> (attributes.value(DOCUMENT_SERIALIZE_DIGITIZE_STATE_BEFORE).toInt());
  m_stateAfter = static_cast<DigitizeState> (attributes.value(DOCUMENT_SERIALIZE_DIGITIZE_STATE_AFTER).toInt());
}

CmdDigitizeState::~CmdDigitizeState ()
{
}

void CmdDigitizeState::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdDigitizeState::cmdRedo"
                              << " state=" << m_stateAfter;

  mainWindow().digitizeState (m_stateAfter);
}

void CmdDigitizeState::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdDigitizeState::cmdUndo"
                              << " state=" << m_stateBefore;

  mainWindow().digitizeState (m_stateBefore);
}

void CmdDigitizeState::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_DIGITIZE_STATE);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  writer.writeAttribute(DOCUMENT_SERIALIZE_DIGITIZE_STATE_BEFORE, QString::number (m_stateBefore));
  writer.writeAttribute(DOCUMENT_SERIALIZE_DIGITIZE_STATE_AFTER, QString::number (m_stateAfter));
  writer.writeEndElement();
}
