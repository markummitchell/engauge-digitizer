#include "CmdSettingsGridRemoval.h"
#include "Document.h"
#include "Logger.h"
#include "MainWindow.h"

CmdSettingsGridRemoval::CmdSettingsGridRemoval(MainWindow &mainWindow,
                                               Document &document) :
  CmdAbstract(mainWindow,
              document,
              "Grid Removal settings")
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGridRemoval::CmdSettingsGridRemoval";
}

void CmdSettingsGridRemoval::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGridRemoval::cmdRedo";

  mainWindow().updateAfterCommand();
}

void CmdSettingsGridRemoval::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsGridRemoval::cmdUndo";

  mainWindow().updateAfterCommand();
}
