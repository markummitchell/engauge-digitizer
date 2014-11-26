#ifndef CMD_SETTINGS_FILTER_H
#define CMD_SETTINGS_FILTER_H

#include "CmdAbstract.h"
#include "DlgModelFilter.h"

/// Command for DlgSettingsFilter
class CmdSettingsFilter : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsFilter(MainWindow &mainWindow,
                    Document &document,
                    const DlgModelFilter &modelFilterBefore,
                    const DlgModelFilter &modelFilterAfter);

  virtual void cmdRedo ();
  virtual void cmdUndo ();

private:
  CmdSettingsFilter();

  DlgModelFilter m_modelFilterBefore;
  DlgModelFilter m_modelFilterAfter;
};

#endif // CMD_SETTINGS_FILTER_H
