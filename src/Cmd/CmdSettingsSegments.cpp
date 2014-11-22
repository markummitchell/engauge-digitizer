#include "CmdSettingsSegments.h"
#include "Document.h"
#include "Logger.h"
#include "MainWindow.h"

CmdSettingsSegments::CmdSettingsSegments(MainWindow &mainWindow,
                                         Document &document) :
  CmdAbstract(mainWindow,
              document,
              "Segments settings")
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsSegments::CmdSettingsSegments";
}

void CmdSettingsSegments::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsSegments::cmdRedo";

  mainWindow().updateAfterCommand();
}

void CmdSettingsSegments::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsSegments::cmdUndo";

  mainWindow().updateAfterCommand();
}
