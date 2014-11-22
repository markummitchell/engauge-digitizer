#ifndef CMD_SETTINGS_CURVES_H
#define CMD_SETTINGS_CURVES_H

#include "CmdAbstract.h"

/// Command for DlgSettingsCurves
class CmdSettingsCurves : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsCurves(MainWindow &mainWindow,
                    Document &document);

  virtual void cmdRedo ();
  virtual void cmdUndo ();

private:
  CmdSettingsCurves();
};

#endif // CMD_SETTINGS_CURVES_H
