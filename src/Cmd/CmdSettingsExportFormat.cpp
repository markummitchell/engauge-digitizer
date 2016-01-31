#include "CmdSettingsExportFormat.h"
#include "Document.h"
#include "DocumentModelExportFormat.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>

const QString CMD_DESCRIPTION ("Export settings");

CmdSettingsExportFormat::CmdSettingsExportFormat(MainWindow &mainWindow,
                                                 Document &document,
                                                 const DocumentModelExportFormat &modelExportBefore,
                                                 const DocumentModelExportFormat &modelExportAfter) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_modelExportBefore (modelExportBefore),
  m_modelExportAfter (modelExportAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsExportFormat::CmdSettingsExportFormat";
}

CmdSettingsExportFormat::CmdSettingsExportFormat (MainWindow &mainWindow,
                                                  Document &document,
                                                  const QString &cmdDescription,
                                                  QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsExportFormat::CmdSettingsExportFormat";

  m_modelExportBefore.loadXml (reader);
  m_modelExportAfter.loadXml (reader);
}

CmdSettingsExportFormat::~CmdSettingsExportFormat ()
{
}

void CmdSettingsExportFormat::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsExportFormat::cmdRedo";

  mainWindow().updateSettingsExportFormat(m_modelExportAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsExportFormat::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsExportFormat::cmdUndo";

  mainWindow().updateSettingsExportFormat(m_modelExportBefore);
  mainWindow().updateAfterCommand();
}

void CmdSettingsExportFormat::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_SETTINGS_EXPORT);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  m_modelExportBefore.saveXml (writer);
  m_modelExportAfter.saveXml(writer);
  writer.writeEndElement();
}
