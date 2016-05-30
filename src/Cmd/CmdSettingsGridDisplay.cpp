/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdSettingsGridDisplay.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>
#include "Xml.h"

const QString CMD_DESCRIPTION ("Grid Display settings");

CmdSettingsGridDisplay::CmdSettingsGridDisplay(MainWindow &mainWindow,
                                               Document &document,
                                               const DocumentModelGridDisplay &modelGridDisplayBefore,
                                               const DocumentModelGridDisplay &modelGridDisplayAfter) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_modelGridDisplayBefore (modelGridDisplayBefore),
  m_modelGridDisplayAfter (modelGridDisplayAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGridDisplay::CmdSettingsGridDisplay";
}

CmdSettingsGridDisplay::CmdSettingsGridDisplay (MainWindow &mainWindow,
                                                Document &document,
                                                const QString &cmdDescription,
                                                QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGridDisplay::CmdSettingsGridDisplay";

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
        (reader.name() == DOCUMENT_SERIALIZE_GRID_DISPLAY)) {

      if (isBefore) {

        m_modelGridDisplayBefore.loadXml (reader);
        isBefore = false;

      } else {

        m_modelGridDisplayAfter.loadXml (reader);

      }
    }
  }

  if (!success) {
    reader.raiseError ("Cannot read grid display settings");
  }
}

CmdSettingsGridDisplay::~CmdSettingsGridDisplay()
{
}

void CmdSettingsGridDisplay::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGridDisplay::cmdRedo";

  saveOrCheckPreCommandDocumentStateHash (document ());
  mainWindow().updateSettingsGridDisplay(m_modelGridDisplayAfter);
  mainWindow().updateAfterCommand();
  saveOrCheckPostCommandDocumentStateHash (document ());
}

void CmdSettingsGridDisplay::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGridDisplay::cmdUndo";

  saveOrCheckPostCommandDocumentStateHash (document ());
  mainWindow().updateSettingsGridDisplay(m_modelGridDisplayBefore);
  mainWindow().updateAfterCommand();
  saveOrCheckPreCommandDocumentStateHash (document ());
}

void CmdSettingsGridDisplay::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_SETTINGS_GRID_DISPLAY);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  m_modelGridDisplayBefore.saveXml (writer);
  m_modelGridDisplayAfter.saveXml(writer);
  writer.writeEndElement();
}
