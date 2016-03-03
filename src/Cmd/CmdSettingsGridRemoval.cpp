/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdSettingsGridRemoval.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>
#include "Xml.h"

const QString CMD_DESCRIPTION ("Grid Removal settings");

CmdSettingsGridRemoval::CmdSettingsGridRemoval(MainWindow &mainWindow,
                                               Document &document,
                                               const DocumentModelGridRemoval &modelGridRemovalBefore,
                                               const DocumentModelGridRemoval &modelGridRemovalAfter) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_modelGridRemovalBefore (modelGridRemovalBefore),
  m_modelGridRemovalAfter (modelGridRemovalAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGridRemoval::CmdSettingsGridRemoval";
}

CmdSettingsGridRemoval::CmdSettingsGridRemoval (MainWindow &mainWindow,
                                                Document &document,
                                                const QString &cmdDescription,
                                                QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGridRemoval::CmdSettingsGridRemoval";

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
        (reader.name() == DOCUMENT_SERIALIZE_GRID_REMOVAL)) {

      if (isBefore) {

        m_modelGridRemovalBefore.loadXml (reader);
        isBefore = false;

      } else {

        m_modelGridRemovalAfter.loadXml (reader);

      }
    }
  }

  if (!success) {
    reader.raiseError ("Cannot read grid removal settings");
  }
}

CmdSettingsGridRemoval::~CmdSettingsGridRemoval()
{
}

void CmdSettingsGridRemoval::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGridRemoval::cmdRedo";

  mainWindow().updateSettingsGridRemoval(m_modelGridRemovalAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsGridRemoval::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGridRemoval::cmdUndo";

  mainWindow().updateSettingsGridRemoval(m_modelGridRemovalBefore);
  mainWindow().updateAfterCommand();
}

void CmdSettingsGridRemoval::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_SETTINGS_GRID_REMOVAL);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  m_modelGridRemovalBefore.saveXml (writer);
  m_modelGridRemovalAfter.saveXml(writer);
  writer.writeEndElement();
}
