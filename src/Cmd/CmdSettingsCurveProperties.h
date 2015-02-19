#ifndef CMD_SETTINGS_CURVE_PROPERTIES_H
#define CMD_SETTINGS_CURVE_PROPERTIES_H

#include "CmdAbstract.h"
#include "CurveStyles.h"
#include "LineStyle.h"
#include "PointStyle.h"

class CurveStyles;

/// Command for DlgSettingsCurveProperties
class CmdSettingsCurveProperties : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsCurveProperties(MainWindow &mainWindow,
                             Document &document,
                             const CurveStyles &modelCurveStylesBefore,
                             const CurveStyles &modelCurveStylesAfter);

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveCommands (QXmlStreamWriter &writer) const;

private:
  CmdSettingsCurveProperties();

  CurveStyles m_modelCurveStylesBefore;
  CurveStyles m_modelCurveStylesAfter;
};

#endif // CMD_SETTINGS_CURVE_PROPERTIES_H
