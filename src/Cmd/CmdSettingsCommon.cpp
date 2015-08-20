#include "CmdSettingsCommon.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>

const QString CMD_DESCRIPTION ("Common settings");

CmdSettingsCommon::CmdSettingsCommon(MainWindow &mainWindow,
                                     Document &document,
                                     const DocumentModelCommon &modelCommonBefore,
                                     const DocumentModelCommon &modelCommonAfter) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_modelCommonBefore (modelCommonBefore),
  m_modelCommonAfter (modelCommonAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCommon::CmdSettingsCommon";
}

CmdSettingsCommon::CmdSettingsCommon (MainWindow &mainWindow,
                                      Document &document,
                                      const QString &cmdDescription,
                                      QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCommon::CmdSettingsCommon";
  
  m_modelCommonBefore.loadXml (reader);
  m_modelCommonAfter.loadXml (reader);
}

CmdSettingsCommon::~CmdSettingsCommon ()
{
}

void CmdSettingsCommon::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCommon::cmdRedo";

  mainWindow().updateSettingsCommon(m_modelCommonAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsCommon::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCommon::cmdUndo";

  mainWindow().updateSettingsCommon(m_modelCommonBefore);
  mainWindow().updateAfterCommand();
}

void CmdSettingsCommon::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_SETTINGS_COMMON);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  m_modelCommonBefore.saveXml(writer);
  m_modelCommonAfter.saveXml(writer);
  writer.writeEndElement();
}
