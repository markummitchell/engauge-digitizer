#include "CmdSettingsPointMatch.h"
#include "Document.h"
#include "Logger.h"
#include "MainWindow.h"

CmdSettingsPointMatch::CmdSettingsPointMatch(MainWindow &mainWindow,
                                             Document &document) :
  CmdAbstract(mainWindow,
              document,
              "Point Match settings")
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsPointMatch::CmdSettingsPointMatch";
}

void CmdSettingsPointMatch::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsPointMatch::cmdRedo";

  mainWindow().updateAfterCommand();
}

void CmdSettingsPointMatch::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsPointMatch::cmdUndo";

  mainWindow().updateAfterCommand();
}
