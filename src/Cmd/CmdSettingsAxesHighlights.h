#ifndef CMD_SETTINGS_AXES_HIGHLIGHTS_H
#define CMD_SETTINGS_AXES_HIGHLIGHTS_H

#include "CmdAbstract.h"
#include "DocumentModelAxesHighlights.h"

/// Command for DlgSettingsAxesHighlights
class CmdSettingsAxesHighlights : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsAxesHighlights(MainWindow &mainWindow,
                            Document &document,
                            const DocumentModelAxesHighlights &modelAxesHighlightsBefore,
                            const DocumentModelAxesHighlights &modelAxesHighlightsAfter);

  virtual void cmdRedo ();
  virtual void cmdUndo ();

private:
  CmdSettingsAxesHighlights();

  DocumentModelAxesHighlights m_modelAxesHighlightsBefore;
  DocumentModelAxesHighlights m_modelAxesHighlightsAfter;
};

#endif // CMD_SETTINGS_AXES_HIGHLIGHTS_H
