#ifndef CMD_SETTINGS_AXES_HIGHLIGHT_H
#define CMD_SETTINGS_AXES_HIGHLIGHT_H

#include "CmdAbstract.h"
#include "DocumentModelAxesHighlight.h"

/// Command for DlgSettingsAxesHighlight
class CmdSettingsAxesHighlight : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsAxesHighlight(MainWindow &mainWindow,
                           Document &document,
                           const DocumentModelAxesHighlight &modelAxesHighlightBefore,
                           const DocumentModelAxesHighlight &modelAxesHighlightAfter);

  virtual void cmdRedo ();
  virtual void cmdUndo ();

private:
  CmdSettingsAxesHighlight();

  DocumentModelAxesHighlight m_modelAxesHighlightBefore;
  DocumentModelAxesHighlight m_modelAxesHighlightAfter;
};

#endif // CMD_SETTINGS_AXES_HIGHLIGHT_H
