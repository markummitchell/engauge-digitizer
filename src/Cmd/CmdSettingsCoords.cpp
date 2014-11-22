#include "CmdSettingsCoords.h"
#include "Document.h"
#include "Logger.h"
#include "MainWindow.h"

CmdSettingsCoords::CmdSettingsCoords(MainWindow &mainWindow,
                                     Document &document) :
  CmdAbstract(mainWindow,
              document,
              "Coordinate settings")
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCoords::CmdSettingsCoords";
}

void CmdSettingsCoords::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCoords::cmdRedo";

  mainWindow().updateAfterCommand();
}

void CmdSettingsCoords::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCoords::cmdUndo";

  mainWindow().updateAfterCommand();
}
