#include "CmdSettingsAxesHighlight.h"
#include "Document.h"
#include "Logger.h"
#include "MainWindow.h"

CmdSettingsAxesHighlight::CmdSettingsAxesHighlight(MainWindow &mainWindow,
                                                   Document &document,
                                                   const DocumentModelAxesHighlight &modelAxesHighlightBefore,
                                                   const DocumentModelAxesHighlight &modelAxesHighlightAfter) :
  CmdAbstract(mainWindow,
              document,
              "Axes Highlight settings"),
  m_modelAxesHighlightBefore (modelAxesHighlightBefore),
  m_modelAxesHighlightAfter (modelAxesHighlightAfter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsAxesHighlight::CmdSettingsAxesHighlight";
}

void CmdSettingsAxesHighlight::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsAxesHighlight::cmdRedo";

  mainWindow().updateSettingsAxesHighlight(m_modelAxesHighlightAfter);
  mainWindow().updateAfterCommand();
}

void CmdSettingsAxesHighlight::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdSettingsAxesHighlight::cmdUndo";

  mainWindow().updateSettingsAxesHighlight(m_modelAxesHighlightBefore);
  mainWindow().updateAfterCommand();
}
