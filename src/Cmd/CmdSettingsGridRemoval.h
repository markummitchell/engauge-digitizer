#ifndef CMD_SETTINGS_GRID_REMOVAL_H
#define CMD_SETTINGS_GRID_REMOVAL_H

#include "CmdAbstract.h"

/// Command for DlgSettingsGridRemoval
class CmdSettingsGridRemoval : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsGridRemoval(MainWindow &mainWindow,
                         Document &document);

  virtual void cmdRedo ();
  virtual void cmdUndo ();

private:
  CmdSettingsGridRemoval();
};

#endif // CMD_SETTINGS_GRID_REMOVAL_H
