#include "CmdSettingsFilter.h"
#include "Document.h"
#include "Logger.h"
#include "MainWindow.h"

CmdSettingsFilter::CmdSettingsFilter(MainWindow &mainWindow,
                                     Document &document) :
  CmdAbstract(mainWindow,
              document,
              "Filter settings")
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsFilter::CmdSettingsFilter";
}

void CmdSettingsFilter::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsFilter::cmdRedo";

  mainWindow().updateAfterCommand();
}

void CmdSettingsFilter::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsFilter::cmdUndo";

  mainWindow().updateAfterCommand();
}
