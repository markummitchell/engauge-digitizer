#ifndef CMD_SETTINGS_POINT_MATCH_H
#define CMD_SETTINGS_POINT_MATCH_H

#include "CmdAbstract.h"
#include "DlgModelPointMatch.h"

/// Command for DlgSettingsPointMatch
class CmdSettingsPointMatch : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsPointMatch(MainWindow &mainWindow,
                        Document &document,
                        const DlgModelPointMatch &modelPointMatchBefore,
                        const DlgModelPointMatch &modelPointMatchAfter);

  virtual void cmdRedo ();
  virtual void cmdUndo ();

private:
  CmdSettingsPointMatch();

  DlgModelPointMatch m_modelPointMatchBefore;
  DlgModelPointMatch m_modelPointMatchAfter;
};

#endif // CMD_SETTINGS_POINT_MATCH_H
