#include "CmdSettingsGridDisplay.h"
#include "Document.h"
#include "Logger.h"
#include "MainWindow.h"

CmdSettingsGridDisplay::CmdSettingsGridDisplay(MainWindow &mainWindow,
                                               Document &document) :
  CmdAbstract(mainWindow,
              document,
              "Grid Display settings")
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGridDisplay::CmdSettingsGridDisplay";
}

void CmdSettingsGridDisplay::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGridDisplay::cmdRedo";

  mainWindow().updateAfterCommand();
}

void CmdSettingsGridDisplay::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGridDisplay::cmdUndo";

  mainWindow().updateAfterCommand();
}
