#ifndef CMD_SETTINGS_GRID_DISPLAY_H
#define CMD_SETTINGS_GRID_DISPLAY_H

#include "CmdAbstract.h"
#include "DlgModelGridDisplay.h"

/// Command for DlgSettingsGridDisplay
class CmdSettingsGridDisplay : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsGridDisplay(MainWindow &mainWindow,
                         Document &document,
                         const DlgModelGridDisplay &modelGridDisplayBefore,
                         const DlgModelGridDisplay &modelGridDisplayAfter);

  virtual void cmdRedo ();
  virtual void cmdUndo ();

private:
  CmdSettingsGridDisplay();

  DlgModelGridDisplay m_modelGridDisplayBefore;
  DlgModelGridDisplay m_modelGridDisplayAfter;
};

#endif // CMD_SETTINGS_GRID_DISPLAY_H
