/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdSettingsGeneral.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>
#include "Xml.h"

const QString CMD_DESCRIPTION ("General settings");

CmdSettingsGeneral::CmdSettingsGeneral(MainWindow &mainWindow,
                                       Document &document,
                                       const DocumentModelGeneral &modelGeneralBefore,
                                       const DocumentModelGeneral &modelGeneralAfter) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_modelGeneralBefore (modelGeneralBefore),
  m_modelGeneralAfter (modelGeneralAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGeneral::CmdSettingsGeneral";
}

CmdSettingsGeneral::CmdSettingsGeneral (MainWindow &mainWindow,
                                        Document &document,
                                        const QString &cmdDescription,
                                        QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGeneral::CmdSettingsGeneral";
  
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
        (reader.name() == DOCUMENT_SERIALIZE_GENERAL)) {

      if (isBefore) {

        m_modelGeneralBefore.loadXml (reader);
        isBefore = false;

      } else {

        m_modelGeneralAfter.loadXml (reader);

      }
    }
  }

  if (!success) {
    reader.raiseError ("Cannot read general settings");
  }
}

CmdSettingsGeneral::~CmdSettingsGeneral ()
{
}

void CmdSettingsGeneral::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGeneral::cmdRedo";

  mainWindow().updateSettingsGeneral(m_modelGeneralAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsGeneral::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGeneral::cmdUndo";

  mainWindow().updateSettingsGeneral(m_modelGeneralBefore);
  mainWindow().updateAfterCommand();
}

void CmdSettingsGeneral::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_SETTINGS_GENERAL);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  m_modelGeneralBefore.saveXml(writer);
  m_modelGeneralAfter.saveXml(writer);
  writer.writeEndElement();
}
