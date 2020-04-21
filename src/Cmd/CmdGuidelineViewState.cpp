/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdGuidelineViewState.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include "Xml.h"

const QString CMD_DESCRIPTION ("GuidelineViewState");

CmdGuidelineViewState::CmdGuidelineViewState(MainWindow &mainWindow,
                                             Document &document,
                                             GuidelineViewState stateBefore,
                                             GuidelineViewState stateAfter) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_stateBefore (stateBefore),
  m_stateAfter (stateAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineViewState::CmdGuidelineViewState";
}

CmdGuidelineViewState::CmdGuidelineViewState (MainWindow &mainWindow,
                                              Document &document,
                                              const QString &cmdDescription,
                                              QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineViewState::CmdGuidelineViewState";

  QXmlStreamAttributes attributes = reader.attributes();

  if (!attributes.hasAttribute(DOCUMENT_SERIALIZE_GUIDELINE_VIEW_STATE_BEFORE) ||
      !attributes.hasAttribute(DOCUMENT_SERIALIZE_GUIDELINE_VIEW_STATE_AFTER)) {
    xmlExitWithError (reader,
                      QString ("%1 %2 %3 %4")
                      .arg (QObject::tr ("Missing attribute(s)"))
                      .arg (DOCUMENT_SERIALIZE_GUIDELINE_VIEW_STATE_BEFORE)
                      .arg (QObject::tr ("and/or"))
                      .arg (DOCUMENT_SERIALIZE_GUIDELINE_VIEW_STATE_AFTER));
  }

  m_stateBefore = static_cast<GuidelineViewState> (attributes.value(DOCUMENT_SERIALIZE_GUIDELINE_VIEW_STATE_BEFORE).toInt());
  m_stateAfter = static_cast<GuidelineViewState> (attributes.value(DOCUMENT_SERIALIZE_GUIDELINE_VIEW_STATE_AFTER).toInt());
}

CmdGuidelineViewState::~CmdGuidelineViewState ()
{
}

void CmdGuidelineViewState::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineViewState::cmdRedo"
                              << " state=" << m_stateAfter;

  mainWindow().guidelineViewState (m_stateAfter);
}

void CmdGuidelineViewState::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdGuidelineViewState::cmdUndo"
                              << " state=" << m_stateBefore;

  mainWindow().guidelineViewState (m_stateBefore);
}

void CmdGuidelineViewState::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_GUIDELINE_VIEW_STATE);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  writer.writeAttribute(DOCUMENT_SERIALIZE_GUIDELINE_VIEW_STATE_BEFORE, QString::number (m_stateBefore));
  writer.writeAttribute(DOCUMENT_SERIALIZE_GUIDELINE_VIEW_STATE_AFTER, QString::number (m_stateAfter));
  writer.writeEndElement();
}
