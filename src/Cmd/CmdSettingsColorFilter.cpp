/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdSettingsColorFilter.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>
#include "Xml.h"

const QString CMD_DESCRIPTION ("Filter settings");

CmdSettingsColorFilter::CmdSettingsColorFilter(MainWindow &mainWindow,
                                               Document &document,
                                               const DocumentModelColorFilter &modelColorFilterBefore,
                                               const DocumentModelColorFilter &modelColorFilterAfter) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_modelColorFilterBefore (modelColorFilterBefore),
  m_modelColorFilterAfter (modelColorFilterAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsColorFilter::CmdSettingsColorFilter";
}

CmdSettingsColorFilter::CmdSettingsColorFilter (MainWindow &mainWindow,
                                                Document &document,
                                                const QString &cmdDescription,
                                                QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsColorFilter::CmdSettingsColorFilter";

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
        (reader.name() == DOCUMENT_SERIALIZE_FILTER)) {

      if (isBefore) {

        m_modelColorFilterBefore.loadXml (reader);
        isBefore = false;

      } else {

        m_modelColorFilterAfter.loadXml (reader);

      }
    }
  }

  if (!success) {
    reader.raiseError ("Cannot read color filter settings");
  }
}

CmdSettingsColorFilter::~CmdSettingsColorFilter ()
{
}

void CmdSettingsColorFilter::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsColorFilter::cmdRedo";

  mainWindow().updateSettingsColorFilter(m_modelColorFilterAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsColorFilter::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsColorFilter::cmdUndo";

  mainWindow().updateSettingsColorFilter(m_modelColorFilterBefore);
  mainWindow().updateAfterCommand();
}

void CmdSettingsColorFilter::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_SETTINGS_COLOR_FILTER);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  m_modelColorFilterBefore.saveXml (writer);
  m_modelColorFilterAfter.saveXml(writer);
  writer.writeEndElement();
}
