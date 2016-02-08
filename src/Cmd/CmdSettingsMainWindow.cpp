#include "CmdSettingsMainWindow.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>
#include "Xml.h"

const QString CMD_DESCRIPTION ("Main window settings");

CmdSettingsMainWindow::CmdSettingsMainWindow(MainWindow &mainWindow,
                                             Document &document,
                                             const MainWindowModel &modelMainWindowBefore,
                                             const MainWindowModel &modelMainWindowAfter) :
  CmdAbstract(mainWindow,
              document,
              CMD_DESCRIPTION),
  m_modelMainWindowBefore (modelMainWindowBefore),
  m_modelMainWindowAfter (modelMainWindowAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsMainWindow::CmdSettingsMainWindow";
}

CmdSettingsMainWindow::CmdSettingsMainWindow(MainWindow &mainWindow,
                                             Document &document,
                                             const QString &cmdDescription,
                                             QXmlStreamReader &reader) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsMainWindow::CmdSettingsMainWindow";

  bool success = true;

  // Read until end of this subtree
  bool isBefore = true;
  while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
  (reader.name() != DOCUMENT_SERIALIZE_CMD)){
    loadNextFromReader(reader);
    if (reader.atEnd()) {
      success = false;
      break;
    }

    if ((reader.tokenType() == QXmlStreamReader::StartElement) &&
        (reader.name() == DOCUMENT_SERIALIZE_MAIN_WINDOW)) {

      if (isBefore) {

        m_modelMainWindowBefore.loadXml (reader);
        isBefore = false;

      } else {

        m_modelMainWindowAfter.loadXml (reader);

      }
    }
  }

  if (!success) {
    reader.raiseError ("Cannot read coordinates data");
  }
}

CmdSettingsMainWindow::~CmdSettingsMainWindow ()
{
}

void CmdSettingsMainWindow::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsMainWindow::cmdRedo";

  mainWindow().updateSettingsMainWindow(m_modelMainWindowAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsMainWindow::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsMainWindow::cmdUndo";

  mainWindow().updateSettingsMainWindow(m_modelMainWindowBefore);
  mainWindow().updateAfterCommand();
}

void CmdSettingsMainWindow::saveXml (QXmlStreamWriter &writer) const
{
  writer.writeStartElement(DOCUMENT_SERIALIZE_CMD);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_TYPE, DOCUMENT_SERIALIZE_CMD_SETTINGS_MAIN_WINDOW);
  writer.writeAttribute(DOCUMENT_SERIALIZE_CMD_DESCRIPTION, QUndoCommand::text ());
  m_modelMainWindowBefore.saveXml(writer);
  m_modelMainWindowAfter.saveXml(writer);
  writer.writeEndElement();
}
