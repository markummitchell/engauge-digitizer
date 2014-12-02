#ifndef CMD_SETTINGS_GRID_DISPLAY_H
#define CMD_SETTINGS_GRID_DISPLAY_H

#include "CmdAbstract.h"
#include "DocumentModelGridDisplay.h"

/// Command for DlgSettingsGridDisplay
class CmdSettingsGridDisplay : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsGridDisplay(MainWindow &mainWindow,
                         Document &document,
                         const DocumentModelGridDisplay &modelGridDisplayBefore,
                         const DocumentModelGridDisplay &modelGridDisplayAfter);

  virtual void cmdRedo ();
  virtual void cmdUndo ();

private:
  CmdSettingsGridDisplay();

  DocumentModelGridDisplay m_modelGridDisplayBefore;
  DocumentModelGridDisplay m_modelGridDisplayAfter;
};

#endif // CMD_SETTINGS_GRID_DISPLAY_H
