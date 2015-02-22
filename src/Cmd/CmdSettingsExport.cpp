#include "CmdSettingsExport.h"
#include "Document.h"
#include "DocumentModelExport.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>

const QString CMD_DESCRIPTION ("Export settings");

CmdSettingsExport::CmdSettingsExport(MainWindow &mainWindow,
                                     Document &document,
                                     const DocumentModelExport &modelExportBefore,
                                     const DocumentModelExport &modelExportAfter) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_modelExportBefore (modelExportBefore),
  m_modelExportAfter (modelExportAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsExport::CmdSettingsExport";
}

CmdSettingsExport::CmdSettingsExport (MainWindow &mainWindow,
                                      Document &document,
                                      const QString &cmdDescription,
                                      QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsExport::CmdSettingsExport";

  m_modelExportBefore.loadXml (reader);
  m_modelExportAfter.loadXml (reader);
}

CmdSettingsExport::~CmdSettingsExport ()
{
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

void CmdSettingsExport::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_SETTINGS_EXPORT);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  m_modelExportBefore.saveXml (writer);
  m_modelExportAfter.saveXml(writer);
  writer.writeEndElement();
}
