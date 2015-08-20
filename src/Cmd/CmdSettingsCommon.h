#ifndef CMD_SETTINGS_COMMON_H
#define CMD_SETTINGS_COMMON_H

#include "CmdAbstract.h"
#include "DocumentModelCommon.h"

class QXmlStreamReader;

/// Command for DlgSettingsCommon
class CmdSettingsCommon : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdSettingsCommon(MainWindow &mainWindow,
                    Document &document,
                    const DocumentModelCommon &modelCommonBefore,
                    const DocumentModelCommon &modelCommonAfter);

  /// Constructor for parsing error report file xml
  CmdSettingsCommon(MainWindow &mainWindow,
                    Document &document,
                    const QString &cmdDescription,
                    QXmlStreamReader &reader);

  virtual ~CmdSettingsCommon();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;
  
private:
  CmdSettingsCommon();

  DocumentModelCommon m_modelCommonBefore;
  DocumentModelCommon m_modelCommonAfter;
};

#endif // CMD_SETTINGS_COMMON_H
