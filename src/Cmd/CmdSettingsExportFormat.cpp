/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdSettingsExportFormat.h"
#include "Document.h"
#include "DocumentModelExportFormat.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>
#include "Xml.h"

const QString CMD_DESCRIPTION ("Export settings");

CmdSettingsExportFormat::CmdSettingsExportFormat(MainWindow &mainWindow,
                                                 Document &document,
                                                 const DocumentModelExportFormat &modelExportBefore,
                                                 const DocumentModelExportFormat &modelExportAfter) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_modelExportBefore (modelExportBefore),
  m_modelExportAfter (modelExportAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsExportFormat::CmdSettingsExportFormat";
}

CmdSettingsExportFormat::CmdSettingsExportFormat (MainWindow &mainWindow,
                                                  Document &document,
                                                  const QString &cmdDescription,
                                                  QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsExportFormat::CmdSettingsExportFormat";

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
        (reader.name() == DOCUMENT_SERIALIZE_EXPORT)) {

      if (isBefore) {

        m_modelExportBefore.loadXml (reader);
        isBefore = false;

      } else {

        m_modelExportAfter.loadXml (reader);

      }
    }
  }

  if (!success) {
    reader.raiseError ("Cannot read export format settings");
  }
}

CmdSettingsExportFormat::~CmdSettingsExportFormat ()
{
}

void CmdSettingsExportFormat::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsExportFormat::cmdRedo";

  saveOrCheckPreCommandDocumentStateHash (document ());
  mainWindow().updateSettingsExportFormat(m_modelExportAfter);
  mainWindow().updateAfterCommand();
  saveOrCheckPostCommandDocumentStateHash (document ());
}

void CmdSettingsExportFormat::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsExportFormat::cmdUndo";

  saveOrCheckPostCommandDocumentStateHash (document ());
  mainWindow().updateSettingsExportFormat(m_modelExportBefore);
  mainWindow().updateAfterCommand();
  saveOrCheckPreCommandDocumentStateHash (document ());
}

void CmdSettingsExportFormat::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_SETTINGS_EXPORT);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  m_modelExportBefore.saveXml (writer);
  m_modelExportAfter.saveXml(writer);
  writer.writeEndElement();
}
