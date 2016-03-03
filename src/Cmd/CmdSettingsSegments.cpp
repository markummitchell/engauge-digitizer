/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdSettingsSegments.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>
#include "Xml.h"

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

  bool success = true;

  // Read until end of this subtree
  bool isBefore = true;
  while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
  (reader.name() != DOCUMENT_SERIALIZE_CMD)){
    loadNextFromReader(reader);
    if (reader.atEnd()) {
      xmlExitWithError (reader,
                        QString ("%1 %2")
                        .arg (QObject::tr ("Reached end of file before finding end element for"))
                        .arg (DOCUMENT_SERIALIZE_CMD));
      success = false;
      break;
    }

    if ((reader.tokenType() == QXmlStreamReader::StartElement) &&
        (reader.name() == DOCUMENT_SERIALIZE_SEGMENTS)) {

      if (isBefore) {

        m_modelSegmentsBefore.loadXml (reader);
        isBefore = false;

      } else {

        m_modelSegmentsAfter.loadXml (reader);

      }
    }
  }

  if (!success) {
    reader.raiseError ("Cannot read segments settings");
  }
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
