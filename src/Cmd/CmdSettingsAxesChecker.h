#ifndef CMD_SETTINGS_AXES_CHECKER_H
#define CMD_SETTINGS_AXES_CHECKER_H

#include "CmdAbstract.h"
#include "DocumentModelAxesChecker.h"

/// Command for DlgSettingsAxesChecker
class CmdSettingsAxesChecker : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsAxesChecker(MainWindow &mainWindow,
                         Document &document,
                         const DocumentModelAxesChecker &modelAxesCheckerBefore,
                         const DocumentModelAxesChecker &modelAxesCheckerAfter);

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdSettingsAxesChecker();

  DocumentModelAxesChecker m_modelAxesCheckerBefore;
  DocumentModelAxesChecker m_modelAxesCheckerAfter;
};

#endif // CMD_SETTINGS_AXES_CHECKER_H
