#include "CmdSettingsAxesChecker.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>

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
  
  m_modelAxesCheckerBefore.loadXml (reader);
  m_modelAxesCheckerAfter.loadXml (reader);
}

CmdSettingsAxesChecker::~CmdSettingsAxesChecker ()
{
}

void CmdSettingsAxesChecker::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsAxesChecker::cmdRedo";

  mainWindow().updateSettingsAxesChecker(m_modelAxesCheckerAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsAxesChecker::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsAxesChecker::cmdUndo";

  mainWindow().updateSettingsAxesChecker(m_modelAxesCheckerBefore);
  mainWindow().updateAfterCommand();
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
