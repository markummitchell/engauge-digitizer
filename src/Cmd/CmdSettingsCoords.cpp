/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdSettingsCoords.h"
#include "DocumentModelCoords.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>
#include "Xml.h"

const QString CMD_DESCRIPTION ("Coordinate settings");

CmdSettingsCoords::CmdSettingsCoords(MainWindow &mainWindow,
                                     Document &document,
                                     const DocumentModelCoords &modelCoordsBefore,
                                     const DocumentModelCoords &modelCoordsAfter) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_modelCoordsBefore (modelCoordsBefore),
  m_modelCoordsAfter (modelCoordsAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCoords::CmdSettingsCoords";
}

CmdSettingsCoords::CmdSettingsCoords (MainWindow &mainWindow,
                                      Document &document,
                                      const QString &cmdDescription,
                                      QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCoords::CmdSettingsCoords";
  
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
        (reader.name() == DOCUMENT_SERIALIZE_COORDS)) {

      if (isBefore) {

        m_modelCoordsBefore.loadXml (reader);
        isBefore = false;

      } else {

        m_modelCoordsAfter.loadXml (reader);

      }
    }
  }

  if (!success) {
    reader.raiseError ("Cannot read coordinates data settings");
  }
}

CmdSettingsCoords::~CmdSettingsCoords ()
{
}

void CmdSettingsCoords::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCoords::cmdRedo";

  mainWindow().updateSettingsCoords(m_modelCoordsAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsCoords::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCoords::cmdUndo";

  mainWindow().updateSettingsCoords(m_modelCoordsBefore);
  mainWindow().updateAfterCommand();
}

void CmdSettingsCoords::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_SETTINGS_COORDS);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  m_modelCoordsBefore.saveXml(writer);
  m_modelCoordsAfter.saveXml(writer);
  writer.writeEndElement();
}
