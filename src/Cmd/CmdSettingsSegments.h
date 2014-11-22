#ifndef CMD_SETTINGS_SEGMENTS_H
#define CMD_SETTINGS_SEGMENTS_H

#include "CmdAbstract.h"

/// Command for DlgSettingsSegments
class CmdSettingsSegments : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsSegments(MainWindow &mainWindow,
                      Document &document);

  virtual void cmdRedo ();
  virtual void cmdUndo ();

private:
  CmdSettingsSegments();
};

#endif // CMD_SETTINGS_SEGMENTS_H
