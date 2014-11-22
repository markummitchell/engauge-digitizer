#ifndef CMD_SETTINGS_COORDS_H
#define CMD_SETTINGS_COORDS_H

#include "CmdAbstract.h"

/// Command for DlgSettingsExport
class CmdSettingsExport : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsExport(MainWindow &mainWindow,
                    Document &document);

  virtual void cmdRedo ();
  virtual void cmdUndo ();

private:
  CmdSettingsExport();
};

#endif // CMD_SETTINGS_COORDS_H
