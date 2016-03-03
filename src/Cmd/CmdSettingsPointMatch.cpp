/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdSettingsPointMatch.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>
#include "Xml.h"

const QString CMD_DESCRIPTION ("Point Match settings");

CmdSettingsPointMatch::CmdSettingsPointMatch(MainWindow &mainWindow,
                                             Document &document,
                                             const DocumentModelPointMatch &modelPointMatchBefore,
                                             const DocumentModelPointMatch &modelPointMatchAfter) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_modelPointMatchBefore (modelPointMatchBefore),
  m_modelPointMatchAfter (modelPointMatchAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsPointMatch::CmdSettingsPointMatch";
}

CmdSettingsPointMatch::CmdSettingsPointMatch (MainWindow &mainWindow,
                                              Document &document,
                                              const QString &cmdDescription,
                                              QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsPointMatch::CmdSettingsPointMatch";

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
        (reader.name() == DOCUMENT_SERIALIZE_POINT_MATCH)) {

      if (isBefore) {

        m_modelPointMatchBefore.loadXml (reader);
        isBefore = false;

      } else {

        m_modelPointMatchAfter.loadXml (reader);

      }
    }
  }

  if (!success) {
    reader.raiseError ("Cannot read point match settings");
  }
}

CmdSettingsPointMatch::~CmdSettingsPointMatch ()
{
}

void CmdSettingsPointMatch::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsPointMatch::cmdRedo";

  mainWindow().updateSettingsPointMatch(m_modelPointMatchAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsPointMatch::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsPointMatch::cmdUndo";

  mainWindow().updateSettingsPointMatch(m_modelPointMatchBefore);
  mainWindow().updateAfterCommand();
}

void CmdSettingsPointMatch::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_SETTINGS_POINT_MATCH);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  m_modelPointMatchBefore.saveXml (writer);
  m_modelPointMatchAfter.saveXml(writer);
  writer.writeEndElement();
}
