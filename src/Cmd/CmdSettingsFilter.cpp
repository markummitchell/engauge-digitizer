#include "CmdSettingsFilter.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"

CmdSettingsFilter::CmdSettingsFilter(MainWindow &mainWindow,
                                     Document &document,
                                     const DocumentModelFilter &modelFilterBefore,
                                     const DocumentModelFilter &modelFilterAfter) :
  CmdAbstract(mainWindow,
              document,
              "Filter settings"),
  m_modelFilterBefore (modelFilterBefore),
  m_modelFilterAfter (modelFilterAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsFilter::CmdSettingsFilter";
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
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD_SETTINGS_FILTER);
  m_modelFilterBefore.saveXml (writer);
  m_modelFilterAfter.saveXml(writer);
  writer.writeEndElement();
}
