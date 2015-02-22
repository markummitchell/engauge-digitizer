#include "CmdSettingsFilter.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>

const QString CMD_DESCRIPTION ("Filter settings");

CmdSettingsFilter::CmdSettingsFilter(MainWindow &mainWindow,
                                     Document &document,
                                     const DocumentModelFilter &modelFilterBefore,
                                     const DocumentModelFilter &modelFilterAfter) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_modelFilterBefore (modelFilterBefore),
  m_modelFilterAfter (modelFilterAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsFilter::CmdSettingsFilter";
}

CmdSettingsFilter::CmdSettingsFilter (MainWindow &mainWindow,
                                      Document &document,
                                      const QString &cmdDescription,
                                      QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsFilter::CmdSettingsFilter";
}

CmdSettingsFilter::~CmdSettingsFilter ()
{
}

void CmdSettingsFilter::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsFilter::cmdRedo";

  mainWindow().updateSettingsFilter(m_modelFilterAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsFilter::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsFilter::cmdUndo";

  mainWindow().updateSettingsFilter(m_modelFilterBefore);
  mainWindow().updateAfterCommand();
}

void CmdSettingsFilter::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_SETTINGS_FILTER);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  m_modelFilterBefore.saveXml (writer);
  m_modelFilterAfter.saveXml(writer);
  writer.writeEndElement();
}
