#ifndef CMD_SETTINGS_POINT_MATCH_H
#define CMD_SETTINGS_POINT_MATCH_H

#include "CmdAbstract.h"
#include "DocumentModelPointMatch.h"

/// Command for DlgSettingsPointMatch
class CmdSettingsPointMatch : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsPointMatch(MainWindow &mainWindow,
                        Document &document,
                        const DocumentModelPointMatch &modelPointMatchBefore,
                        const DocumentModelPointMatch &modelPointMatchAfter);

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveCommands (QXmlStreamWriter &writer) const;

private:
  CmdSettingsPointMatch();

  DocumentModelPointMatch m_modelPointMatchBefore;
  DocumentModelPointMatch m_modelPointMatchAfter;
};

#endif // CMD_SETTINGS_POINT_MATCH_H
