#ifndef CMD_SETTINGS_CURVE_PROPERTIES_H
#define CMD_SETTINGS_CURVE_PROPERTIES_H

#include "CmdAbstract.h"
#include "DocumentModelCurveProperties.h"
#include "LineStyle.h"
#include "PointStyle.h"

class DocumentModelCurveProperties;

/// Command for DlgSettingsCurveProperties
class CmdSettingsCurveProperties : public CmdAbstract
{
public:
  /// Single constructor.
  CmdSettingsCurveProperties(MainWindow &mainWindow,
                             Document &document,
                             const DocumentModelCurveProperties &modelCurvePropertiesBefore,
                             const DocumentModelCurveProperties &modelCurvePropertiesAfter);

  virtual void cmdRedo ();
  virtual void cmdUndo ();

private:
  CmdSettingsCurveProperties();

  DocumentModelCurveProperties m_modelCurvePropertiesBefore;
  DocumentModelCurveProperties m_modelCurvePropertiesAfter;
};

#endif // CMD_SETTINGS_CURVE_PROPERTIES_H
