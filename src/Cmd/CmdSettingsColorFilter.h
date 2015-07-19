#ifndef CMD_SETTINGS_COLOR_FILTER_H
#define CMD_SETTINGS_COLOR_FILTER_H

#include "CmdAbstract.h"
#include "DocumentModelColorFilter.h"

class QXmlStreamReader;

/// Command for DlgSettingsColorFilter
class CmdSettingsColorFilter : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdSettingsColorFilter(MainWindow &mainWindow,
                         Document &document,
                         const DocumentModelColorFilter &modelColorFilterBefore,
                         const DocumentModelColorFilter &modelColorFilterAfter);

  /// Constructor for parsing error report file xml
  CmdSettingsColorFilter(MainWindow &mainWindow,
                         Document &document,
                         const QString &cmdDescription,
                         QXmlStreamReader &reader);

  virtual ~CmdSettingsColorFilter();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdSettingsColorFilter();

  DocumentModelColorFilter m_modelColorFilterBefore;
  DocumentModelColorFilter m_modelColorFilterAfter;
};

#endif // CMD_SETTINGS_COLOR_FILTER_H
