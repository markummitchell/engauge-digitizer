#ifndef CMD_SETTINGS_FILTER_H
#define CMD_SETTINGS_FILTER_H

#include "CmdAbstract.h"

/// Command for DlgSettingsFilter
class CmdSettingsFilter : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsFilter(MainWindow &mainWindow,
                    Document &document);

  virtual void cmdRedo ();
  virtual void cmdUndo ();

private:
  CmdSettingsFilter();
};

#endif // CMD_SETTINGS_FILTER_H
