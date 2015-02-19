#include "CmdSettingsAxesChecker.h"
#include "Document.h"
#include "Logger.h"
#include "MainWindow.h"

CmdSettingsAxesChecker::CmdSettingsAxesChecker(MainWindow &mainWindow,
                                               Document &document,
                                               const DocumentModelAxesChecker &modelAxesCheckerBefore,
                                               const DocumentModelAxesChecker &modelAxesCheckerAfter) :
  CmdAbstract(mainWindow,
              document,
              "Axes Checker settings"),
  m_modelAxesCheckerBefore (modelAxesCheckerBefore),
  m_modelAxesCheckerAfter (modelAxesCheckerAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsAxesChecker::CmdSettingsAxesChecker";
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

void CmdSettingsAxesChecker::saveCommands (QXmlStreamWriter &writer) const
{
  writer.writeStartElement("CmdSettingsAxesChecker");
  m_modelAxesCheckerBefore.saveDocument(writer);
  m_modelAxesCheckerAfter.saveDocument(writer);
  writer.writeEndElement();
}
