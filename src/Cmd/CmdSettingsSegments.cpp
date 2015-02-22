#include "CmdSettingsSegments.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>

const QString CMD_DESCRIPTION ("Segments settings");

CmdSettingsSegments::CmdSettingsSegments(MainWindow &mainWindow,
                                         Document &document,
                                         const DocumentModelSegments &modelSegmentsBefore,
                                         const DocumentModelSegments &modelSegmentsAfter) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_modelSegmentsBefore (modelSegmentsBefore),
  m_modelSegmentsAfter (modelSegmentsAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsSegments::CmdSettingsSegments";
}

CmdSettingsSegments::CmdSettingsSegments (MainWindow &mainWindow,
                                          Document &document,
                                          const QString &cmdDescription,
                                          QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsSegments::CmdSettingsSegments";

  m_modelSegmentsBefore.loadXml (reader);
  m_modelSegmentsAfter.loadXml (reader);
}

CmdSettingsSegments::~CmdSettingsSegments ()
{
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
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_SETTINGS_SEGMENTS);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  m_modelSegmentsBefore.saveXml (writer);
  m_modelSegmentsAfter.saveXml(writer);
  writer.writeEndElement();
}
