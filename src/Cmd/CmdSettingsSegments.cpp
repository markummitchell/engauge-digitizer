#include "CmdSettingsSegments.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"

CmdSettingsSegments::CmdSettingsSegments(MainWindow &mainWindow,
                                         Document &document,
                                         const DocumentModelSegments &modelSegmentsBefore,
                                         const DocumentModelSegments &modelSegmentsAfter) :
  CmdAbstract(mainWindow,
              document,
              "Segments settings"),
  m_modelSegmentsBefore (modelSegmentsBefore),
  m_modelSegmentsAfter (modelSegmentsAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsSegments::CmdSettingsSegments";
}

void CmdSettingsSegments::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsSegments::cmdRedo";

  mainWindow().updateSettingsSegments(m_modelSegmentsAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsSegments::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsSegments::cmdUndo";

  mainWindow().updateSettingsSegments(m_modelSegmentsBefore);
  mainWindow().updateAfterCommand();
}

void CmdSettingsSegments::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD_SETTINGS_SEGMENTS);
  m_modelSegmentsBefore.saveXml (writer);
  m_modelSegmentsAfter.saveXml(writer);
  writer.writeEndElement();
}
