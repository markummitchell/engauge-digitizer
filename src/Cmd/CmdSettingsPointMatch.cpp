#include "CmdSettingsPointMatch.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>

const QString CMD_DESCRIPTION ("Point Match settings");

CmdSettingsPointMatch::CmdSettingsPointMatch(MainWindow &mainWindow,
                                             Document &document,
                                             const DocumentModelPointMatch &modelPointMatchBefore,
                                             const DocumentModelPointMatch &modelPointMatchAfter) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_modelPointMatchBefore (modelPointMatchBefore),
  m_modelPointMatchAfter (modelPointMatchAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsPointMatch::CmdSettingsPointMatch";
}

CmdSettingsPointMatch::CmdSettingsPointMatch (MainWindow &mainWindow,
                                              Document &document,
                                              const QString &cmdDescription,
                                              QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsPointMatch::CmdSettingsPointMatch";

  m_modelPointMatchBefore.loadXml (reader);
  m_modelPointMatchAfter.loadXml (reader);
}

CmdSettingsPointMatch::~CmdSettingsPointMatch ()
{
}

void CmdSettingsPointMatch::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsPointMatch::cmdRedo";

  mainWindow().updateSettingsPointMatch(m_modelPointMatchAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsPointMatch::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsPointMatch::cmdUndo";

  mainWindow().updateSettingsPointMatch(m_modelPointMatchBefore);
  mainWindow().updateAfterCommand();
}

void CmdSettingsPointMatch::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_SETTINGS_POINT_MATCH);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  m_modelPointMatchBefore.saveXml (writer);
  m_modelPointMatchAfter.saveXml(writer);
  writer.writeEndElement();
}
