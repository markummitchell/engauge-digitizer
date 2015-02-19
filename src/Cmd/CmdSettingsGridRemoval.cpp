#include "CmdSettingsGridRemoval.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"

CmdSettingsGridRemoval::CmdSettingsGridRemoval(MainWindow &mainWindow,
                                               Document &document,
                                               const DocumentModelGridRemoval &modelGridRemovalBefore,
                                               const DocumentModelGridRemoval &modelGridRemovalAfter) :
  CmdAbstract(mainWindow,
              document,
              "Grid Removal settings"),
  m_modelGridRemovalBefore (modelGridRemovalBefore),
  m_modelGridRemovalAfter (modelGridRemovalAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGridRemoval::CmdSettingsGridRemoval";
}

void CmdSettingsGridRemoval::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGridRemoval::cmdRedo";

  mainWindow().updateSettingsGridRemoval(m_modelGridRemovalAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsGridRemoval::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGridRemoval::cmdUndo";

  mainWindow().updateSettingsGridRemoval(m_modelGridRemovalBefore);
  mainWindow().updateAfterCommand();
}

void CmdSettingsGridRemoval::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD_SETTINGS_GRID_REMOVAL);
  m_modelGridRemovalBefore.saveXml (writer);
  m_modelGridRemovalAfter.saveXml(writer);
  writer.writeEndElement();
}
