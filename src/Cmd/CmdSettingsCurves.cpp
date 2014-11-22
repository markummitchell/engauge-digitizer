#include "CmdSettingsCurves.h"
#include "Document.h"
#include "Logger.h"
#include "MainWindow.h"

CmdSettingsCurves::CmdSettingsCurves(MainWindow &mainWindow,
                                     Document &document) :
  CmdAbstract(mainWindow,
              document,
              "Curves settings")
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurves::CmdSettingsCurves";
}

void CmdSettingsCurves::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurves::cmdRedo";

  mainWindow().updateAfterCommand();
}

void CmdSettingsCurves::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsCurves::cmdUndo";

  mainWindow().updateAfterCommand();
}
