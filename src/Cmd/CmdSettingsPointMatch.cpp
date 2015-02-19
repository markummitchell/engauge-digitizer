#include "CmdSettingsPointMatch.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"

CmdSettingsPointMatch::CmdSettingsPointMatch(MainWindow &mainWindow,
                                             Document &document,
                                             const DocumentModelPointMatch &modelPointMatchBefore,
                                             const DocumentModelPointMatch &modelPointMatchAfter) :
  CmdAbstract(mainWindow,
              document,
              "Point Match settings"),
  m_modelPointMatchBefore (modelPointMatchBefore),
  m_modelPointMatchAfter (modelPointMatchAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsPointMatch::CmdSettingsPointMatch";
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
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD_SETTINGS_POINT_MATCH);
  m_modelPointMatchBefore.saveXml (writer);
  m_modelPointMatchAfter.saveXml(writer);
  writer.writeEndElement();
}
