#ifndef CMD_SETTINGS_GRID_REMOVAL_H
#define CMD_SETTINGS_GRID_REMOVAL_H

#include "CmdAbstract.h"
#include "DocumentModelGridRemoval.h"

class QXmlStreamReader;

/// Command for DlgSettingsGridRemoval
class CmdSettingsGridRemoval : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdSettingsGridRemoval(MainWindow &mainWindow,
                         Document &document,
                         const DocumentModelGridRemoval &modelGridRemovalBefore,
                         const DocumentModelGridRemoval &modelGridRemovalAfter);

  /// Constructor for parsing error report file xml
  CmdSettingsGridRemoval(MainWindow &mainWindow,
                         Document &document,
                         const QString &cmdDescription,
                         QXmlStreamReader &reader);

  virtual ~CmdSettingsGridRemoval();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdSettingsGridRemoval();

  DocumentModelGridRemoval m_modelGridRemovalBefore;
  DocumentModelGridRemoval m_modelGridRemovalAfter;
};

#endif // CMD_SETTINGS_GRID_REMOVAL_H
