#ifndef CMD_SETTINGS_GRID_REMOVAL_H
#define CMD_SETTINGS_GRID_REMOVAL_H

#include "CmdAbstract.h"
#include "DocumentModelGridRemoval.h"

/// Command for DlgSettingsGridRemoval
class CmdSettingsGridRemoval : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsGridRemoval(MainWindow &mainWindow,
                         Document &document,
                         const DocumentModelGridRemoval &modelGridRemovalBefore,
                         const DocumentModelGridRemoval &modelGridRemovalAfter);

  virtual void cmdRedo ();
  virtual void cmdUndo ();

private:
  CmdSettingsGridRemoval();

  DocumentModelGridRemoval m_modelGridRemovalBefore;
  DocumentModelGridRemoval m_modelGridRemovalAfter;
};

#endif // CMD_SETTINGS_GRID_REMOVAL_H
