#ifndef CMD_SETTINGS_COORDS_H
#define CMD_SETTINGS_COORDS_H

#include "CmdAbstract.h"

/// Command for DlgSettingsCoords
class CmdSettingsCoords : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsCoords(MainWindow &mainWindow,
                    Document &document);

  virtual void cmdRedo ();
  virtual void cmdUndo ();

private:
  CmdSettingsCoords();
};

#endif // CMD_SETTINGS_COORDS_H
