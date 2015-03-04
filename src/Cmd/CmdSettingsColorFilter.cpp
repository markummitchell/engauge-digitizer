#include "CmdSettingsColorFilter.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>

const QString CMD_DESCRIPTION ("Filter settings");

CmdSettingsColorFilter::CmdSettingsColorFilter(MainWindow &mainWindow,
                                               Document &document,
                                               const DocumentModelColorFilter &modelColorFilterBefore,
                                               const DocumentModelColorFilter &modelColorFilterAfter) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_modelColorFilterBefore (modelColorFilterBefore),
  m_modelColorFilterAfter (modelColorFilterAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsColorFilter::CmdSettingsColorFilter";
}

CmdSettingsColorFilter::CmdSettingsColorFilter (MainWindow &mainWindow,
                                                Document &document,
                                                const QString &cmdDescription,
                                                QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsColorFilter::CmdSettingsColorFilter";

  m_modelColorFilterBefore.loadXml (reader);
  m_modelColorFilterAfter.loadXml (reader);
}

CmdSettingsColorFilter::~CmdSettingsColorFilter ()
{
}

void CmdSettingsColorFilter::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsColorFilter::cmdRedo";

  mainWindow().updateSettingsColorFilter(m_modelColorFilterAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsColorFilter::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsColorFilter::cmdUndo";

  mainWindow().updateSettingsColorFilter(m_modelColorFilterBefore);
  mainWindow().updateAfterCommand();
}

void CmdSettingsColorFilter::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_SETTINGS_COLOR_FILTER);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  m_modelColorFilterBefore.saveXml (writer);
  m_modelColorFilterAfter.saveXml(writer);
  writer.writeEndElement();
}
