#ifndef CMD_SETTINGS_GRID_DISPLAY_H
#define CMD_SETTINGS_GRID_DISPLAY_H

#include "CmdAbstract.h"

/// Command for DlgSettingsGridDisplay
class CmdSettingsGridDisplay : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsGridDisplay(MainWindow &mainWindow,
                         Document &document);

  virtual void cmdRedo ();
  virtual void cmdUndo ();

private:
  CmdSettingsGridDisplay();
};

#endif // CMD_SETTINGS_GRID_DISPLAY_H
