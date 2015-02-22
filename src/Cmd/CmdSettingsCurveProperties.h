#ifndef CMD_SETTINGS_CURVE_PROPERTIES_H
#define CMD_SETTINGS_CURVE_PROPERTIES_H

#include "CmdAbstract.h"
#include "CurveStyles.h"
#include "LineStyle.h"
#include "PointStyle.h"

class CurveStyles;
class QXmlStreamReader;

/// Command for DlgSettingsCurveProperties
class CmdSettingsCurveProperties : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdSettingsCurveProperties(MainWindow &mainWindow,
                             Document &document,
                             const CurveStyles &modelCurveStylesBefore,
                             const CurveStyles &modelCurveStylesAfter);

  /// Constructor for parsing error report file xml
  CmdSettingsCurveProperties(MainWindow &mainWindow,
                             Document &document,
                             const QString &cmdDescription,
                             QXmlStreamReader &reader);

  virtual ~CmdSettingsCurveProperties();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdSettingsCurveProperties();

  CurveStyles m_modelCurveStylesBefore;
  CurveStyles m_modelCurveStylesAfter;
};

#endif // CMD_SETTINGS_CURVE_PROPERTIES_H
