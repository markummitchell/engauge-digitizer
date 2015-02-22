#ifndef CMD_SETTINGS_EXPORT_H
#define CMD_SETTINGS_EXPORT_H

#include "CmdAbstract.h"
#include "DocumentModelExport.h"

class QXmlStreamReader;

/// Command for DlgSettingsExport
class CmdSettingsExport : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdSettingsExport(MainWindow &mainWindow,
                    Document &document,
                    const DocumentModelExport &modelExportBefore,
                    const DocumentModelExport &modelExportAfter);

  /// Constructor for parsing error report file xml
  CmdSettingsExport(MainWindow &mainWindow,
                    Document &document,
                    const QString &cmdDescription,
                    QXmlStreamReader &reader);

  virtual ~CmdSettingsExport();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdSettingsExport();

  DocumentModelExport m_modelExportBefore;
  DocumentModelExport m_modelExportAfter;
};

#endif // CMD_SETTINGS_EXPORT_H
