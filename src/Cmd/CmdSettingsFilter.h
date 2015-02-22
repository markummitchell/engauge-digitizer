#ifndef CMD_SETTINGS_FILTER_H
#define CMD_SETTINGS_FILTER_H

#include "CmdAbstract.h"
#include "DocumentModelFilter.h"

class QXmlStreamReader;

/// Command for DlgSettingsFilter
class CmdSettingsFilter : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdSettingsFilter(MainWindow &mainWindow,
                    Document &document,
                    const DocumentModelFilter &modelFilterBefore,
                    const DocumentModelFilter &modelFilterAfter);

  /// Constructor for parsing error report file xml
  CmdSettingsFilter(MainWindow &mainWindow,
                    Document &document,
                    const QString &cmdDescription,
                    QXmlStreamReader &reader);

  virtual ~CmdSettingsFilter();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdSettingsFilter();

  DocumentModelFilter m_modelFilterBefore;
  DocumentModelFilter m_modelFilterAfter;
};

#endif // CMD_SETTINGS_FILTER_H
