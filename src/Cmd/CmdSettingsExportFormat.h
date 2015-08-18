#ifndef CMD_SETTINGS_EXPORT_FORMAT_H
#define CMD_SETTINGS_EXPORT_FORMAT_H

#include "CmdAbstract.h"
#include "DocumentModelExportFormat.h"

class QXmlStreamReader;

/// Command for DlgSettingsExportFormat
class CmdSettingsExportFormat : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdSettingsExportFormat(MainWindow &mainWindow,
                          Document &document,
                          const DocumentModelExportFormat &modelExportBefore,
                          const DocumentModelExportFormat &modelExportAfter);

  /// Constructor for parsing error report file xml
  CmdSettingsExportFormat(MainWindow &mainWindow,
                          Document &document,
                          const QString &cmdDescription,
                          QXmlStreamReader &reader);

  virtual ~CmdSettingsExportFormat();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdSettingsExportFormat();

  DocumentModelExportFormat m_modelExportBefore;
  DocumentModelExportFormat m_modelExportAfter;
};

#endif // CMD_SETTINGS_EXPORT_FORMAT_H
