#include "CmdSettingsExport.h"
#include "DocumentModelExport.h"
#include "Document.h"
#include "Logger.h"
#include "MainWindow.h"

CmdSettingsExport::CmdSettingsExport(MainWindow &mainWindow,
                                     Document &document,
                                     const DocumentModelExport &modelExportBefore,
                                     const DocumentModelExport &modelExportAfter) :
  CmdAbstract(mainWindow,
              document,
              "Export settings"),
  m_modelExportBefore (modelExportBefore),
  m_modelExportAfter (modelExportAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsExport::CmdSettingsExport";
}

void CmdSettingsExport::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsExport::cmdRedo";

  mainWindow().updateSettingsExport(m_modelExportAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsExport::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsExport::cmdUndo";

  mainWindow().updateSettingsExport(m_modelExportBefore);
  mainWindow().updateAfterCommand();
}

void CmdSettingsExport::saveCommands (QXmlStreamWriter &writer) const
{
  writer.writeStartElement("CmdSettingsExport");
  m_modelExportBefore.saveDocument (writer);
  m_modelExportAfter.saveDocument(writer);
  writer.writeEndElement();
}
