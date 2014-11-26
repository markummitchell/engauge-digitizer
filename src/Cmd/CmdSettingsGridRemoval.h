#ifndef CMD_SETTINGS_GRID_REMOVAL_H
#define CMD_SETTINGS_GRID_REMOVAL_H

#include "CmdAbstract.h"
#include "DlgModelGridRemoval.h"

/// Command for DlgSettingsGridRemoval
class CmdSettingsGridRemoval : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsGridRemoval(MainWindow &mainWindow,
                         Document &document,
                         const DlgModelGridRemoval &modelGridRemovalBefore,
                         const DlgModelGridRemoval &modelGridRemovalAfter);

  virtual void cmdRedo ();
  virtual void cmdUndo ();

private:
  CmdSettingsGridRemoval();

  DlgModelGridRemoval m_modelGridRemovalBefore;
  DlgModelGridRemoval m_modelGridRemovalAfter;
};

#endif // CMD_SETTINGS_GRID_REMOVAL_H
