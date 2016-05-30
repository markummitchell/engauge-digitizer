/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdSettingsAxesChecker.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>
#include "Xml.h"

const QString CMD_DESCRIPTION ("Axes checker settings");

CmdSettingsAxesChecker::CmdSettingsAxesChecker(MainWindow &mainWindow,
                                               Document &document,
                                               const DocumentModelAxesChecker &modelAxesCheckerBefore,
                                               const DocumentModelAxesChecker &modelAxesCheckerAfter) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_modelAxesCheckerBefore (modelAxesCheckerBefore),
  m_modelAxesCheckerAfter (modelAxesCheckerAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsAxesChecker::CmdSettingsAxesChecker";
}

CmdSettingsAxesChecker::CmdSettingsAxesChecker (MainWindow &mainWindow,
                                                Document &document,
                                                const QString &cmdDescription,
                                                QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsAxesChecker::CmdSettingsAxesChecker";

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
        (reader.name() == DOCUMENT_SERIALIZE_AXES_CHECKER)) {

      if (isBefore) {

        m_modelAxesCheckerBefore.loadXml (reader);
        isBefore = false;

      } else {

        m_modelAxesCheckerAfter.loadXml (reader);

      }
    }
  }

  if (!success) {
    reader.raiseError ("Cannot read axes checker settings");
  }
}

CmdSettingsAxesChecker::~CmdSettingsAxesChecker ()
{
}

void CmdSettingsAxesChecker::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsAxesChecker::cmdRedo";

  saveOrCheckPreCommandDocumentStateHash (document ());
  mainWindow().updateSettingsAxesChecker(m_modelAxesCheckerAfter);
  mainWindow().updateAfterCommand();
  saveOrCheckPostCommandDocumentStateHash (document ());
}

void CmdSettingsAxesChecker::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsAxesChecker::cmdUndo";

  saveOrCheckPostCommandDocumentStateHash (document ());
  mainWindow().updateSettingsAxesChecker(m_modelAxesCheckerBefore);
  mainWindow().updateAfterCommand();
  saveOrCheckPreCommandDocumentStateHash (document ());
}

void CmdSettingsAxesChecker::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_SETTINGS_AXES_CHECKER);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  m_modelAxesCheckerBefore.saveXml(writer);
  m_modelAxesCheckerAfter.saveXml(writer);
  writer.writeEndElement();
}
