#include "CmdSettingsAxesHighlights.h"
#include "Document.h"
#include "Logger.h"
#include "MainWindow.h"

CmdSettingsAxesHighlights::CmdSettingsAxesHighlights(MainWindow &mainWindow,
                                                     Document &document,
                                                     const DocumentModelAxesHighlights &modelAxesHighlightsBefore,
                                                     const DocumentModelAxesHighlights &modelAxesHighlightsAfter) :
  CmdAbstract(mainWindow,
              document,
              "Axes Highlights settings"),
  m_modelAxesHighlightsBefore (modelAxesHighlightsBefore),
  m_modelAxesHighlightsAfter (modelAxesHighlightsAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsAxesHighlights::CmdSettingsAxesHighlights";
}

void CmdSettingsAxesHighlights::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsAxesHighlights::cmdRedo";

  mainWindow().updateSettingsAxesHighlights(m_modelAxesHighlightsAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsAxesHighlights::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsAxesHighlights::cmdUndo";

  mainWindow().updateSettingsAxesHighlights(m_modelAxesHighlightsBefore);
  mainWindow().updateAfterCommand();
}
