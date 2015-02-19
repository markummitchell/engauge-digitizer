#ifndef CMD_SETTINGS_COORDS_H
#define CMD_SETTINGS_COORDS_H

#include "CmdAbstract.h"
#include "DocumentModelExport.h"

/// Command for DlgSettingsExport
class CmdSettingsExport : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsExport(MainWindow &mainWindow,
                    Document &document,
                    const DocumentModelExport &modelExportBefore,
                    const DocumentModelExport &modelExportAfter);

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdSettingsExport();

  DocumentModelExport m_modelExportBefore;
  DocumentModelExport m_modelExportAfter;
};

#endif // CMD_SETTINGS_COORDS_H
