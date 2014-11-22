#ifndef CMD_SETTINGS_CURVE_PROPERTIES_H
#define CMD_SETTINGS_CURVE_PROPERTIES_H

#include "CmdAbstract.h"

/// Command for DlgSettingsCurveProperties
class CmdSettingsCurveProperties : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsCurveProperties(MainWindow &mainWindow,
                             Document &document);

  virtual void cmdRedo ();
  virtual void cmdUndo ();

private:
  CmdSettingsCurveProperties();
};

#endif // CMD_SETTINGS_CURVE_PROPERTIES_H
