#ifndef CMD_SETTINGS_FILTER_H
#define CMD_SETTINGS_FILTER_H

#include "CmdAbstract.h"
#include "DocumentModelFilter.h"

/// Command for DlgSettingsFilter
class CmdSettingsFilter : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsFilter(MainWindow &mainWindow,
                    Document &document,
                    const DocumentModelFilter &modelFilterBefore,
                    const DocumentModelFilter &modelFilterAfter);

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveCommands (QXmlStreamWriter &writer) const;

private:
  CmdSettingsFilter();

  DocumentModelFilter m_modelFilterBefore;
  DocumentModelFilter m_modelFilterAfter;
};

#endif // CMD_SETTINGS_FILTER_H
