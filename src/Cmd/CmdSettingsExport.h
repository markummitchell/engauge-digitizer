#ifndef CMD_SETTINGS_COORDS_H
#define CMD_SETTINGS_COORDS_H

#include "CmdAbstract.h"
#include "DlgModelExport.h"

/// Command for DlgSettingsExport
class CmdSettingsExport : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsExport(MainWindow &mainWindow,
                    Document &document,
                    const DlgModelExport &modelExportBefore,
                    const DlgModelExport &modelExportAfter);

  virtual void cmdRedo ();
  virtual void cmdUndo ();

private:
  CmdSettingsExport();

  DlgModelExport m_modelExportBefore;
  DlgModelExport m_modelExportAfter;
};

#endif // CMD_SETTINGS_COORDS_H
