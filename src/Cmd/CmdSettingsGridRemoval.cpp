#include "CmdSettingsGridRemoval.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>

const QString CMD_DESCRIPTION ("Grid Removal settings");

CmdSettingsGridRemoval::CmdSettingsGridRemoval(MainWindow &mainWindow,
                                               Document &document,
                                               const DocumentModelGridRemoval &modelGridRemovalBefore,
                                               const DocumentModelGridRemoval &modelGridRemovalAfter) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_modelGridRemovalBefore (modelGridRemovalBefore),
  m_modelGridRemovalAfter (modelGridRemovalAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGridRemoval::CmdSettingsGridRemoval";
}

CmdSettingsGridRemoval::CmdSettingsGridRemoval (MainWindow &mainWindow,
                                                Document &document,
                                                const QString &cmdDescription,
                                                QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGridRemoval::CmdSettingsGridRemoval";

  m_modelGridRemovalBefore.loadXml (reader);
  m_modelGridRemovalAfter.loadXml (reader);
}

CmdSettingsGridRemoval::~CmdSettingsGridRemoval()
{
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
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_SETTINGS_GRID_REMOVAL);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  m_modelGridRemovalBefore.saveXml (writer);
  m_modelGridRemovalAfter.saveXml(writer);
  writer.writeEndElement();
}
