#include "CmdSettingsExport.h"
#include "Document.h"
#include "Logger.h"
#include "MainWindow.h"

CmdSettingsExport::CmdSettingsExport(MainWindow &mainWindow,
                                     Document &document) :
  CmdAbstract(mainWindow,
              document,
              "Export settings")
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsExport::CmdSettingsExport";
}

void CmdSettingsExport::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsExport::cmdRedo";

  mainWindow().updateAfterCommand();
}

void CmdSettingsExport::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsExport::cmdUndo";

  mainWindow().updateAfterCommand();
}
