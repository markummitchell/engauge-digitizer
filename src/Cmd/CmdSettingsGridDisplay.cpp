#include "CmdSettingsGridDisplay.h"
#include "Document.h"
#include "Logger.h"
#include "MainWindow.h"

CmdSettingsGridDisplay::CmdSettingsGridDisplay(MainWindow &mainWindow,
                                               Document &document,
                                               const DlgModelGridDisplay &modelGridDisplayBefore,
                                               const DlgModelGridDisplay &modelGridDisplayAfter) :
  CmdAbstract(mainWindow,
              document,
              "Grid Display settings"),
  m_modelGridDisplayBefore (modelGridDisplayBefore),
  m_modelGridDisplayAfter (modelGridDisplayAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGridDisplay::CmdSettingsGridDisplay";
}

void CmdSettingsGridDisplay::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGridDisplay::cmdRedo";

  mainWindow().updateSettingsGridDisplay(m_modelGridDisplayAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsGridDisplay::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGridDisplay::cmdUndo";

  mainWindow().updateSettingsGridDisplay(m_modelGridDisplayBefore);
  mainWindow().updateAfterCommand();
}
