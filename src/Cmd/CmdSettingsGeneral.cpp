#include "CmdSettingsGeneral.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>

const QString CMD_DESCRIPTION ("General settings");

CmdSettingsGeneral::CmdSettingsGeneral(MainWindow &mainWindow,
                                       Document &document,
                                       const DocumentModelGeneral &modelGeneralBefore,
                                       const DocumentModelGeneral &modelGeneralAfter) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_modelGeneralBefore (modelGeneralBefore),
  m_modelGeneralAfter (modelGeneralAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGeneral::CmdSettingsGeneral";
}

CmdSettingsGeneral::CmdSettingsGeneral (MainWindow &mainWindow,
                                        Document &document,
                                        const QString &cmdDescription,
                                        QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGeneral::CmdSettingsGeneral";
  
  m_modelGeneralBefore.loadXml (reader);
  m_modelGeneralAfter.loadXml (reader);
}

CmdSettingsGeneral::~CmdSettingsGeneral ()
{
}

void CmdSettingsGeneral::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGeneral::cmdRedo";

  mainWindow().updateSettingsGeneral(m_modelGeneralAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsGeneral::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGeneral::cmdUndo";

  mainWindow().updateSettingsGeneral(m_modelGeneralBefore);
  mainWindow().updateAfterCommand();
}

void CmdSettingsGeneral::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_SETTINGS_GENERAL);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  m_modelGeneralBefore.saveXml(writer);
  m_modelGeneralAfter.saveXml(writer);
  writer.writeEndElement();
}
