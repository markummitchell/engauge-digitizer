#ifndef CMD_SETTINGS_POINT_MATCH_H
#define CMD_SETTINGS_POINT_MATCH_H

#include "CmdAbstract.h"

/// Command for DlgSettingsPointMatch
class CmdSettingsPointMatch : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsPointMatch(MainWindow &mainWindow,
                        Document &document);

  virtual void cmdRedo ();
  virtual void cmdUndo ();

private:
  CmdSettingsPointMatch();
};

#endif // CMD_SETTINGS_POINT_MATCH_H
