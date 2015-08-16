#ifndef CMD_SETTINGS_CURVE_NAMES_H
#define CMD_SETTINGS_CURVE_NAMES_H

#include "CmdAbstract.h"
#include "CurvesGraphs.h"

class CurveNameList;
class QXmlStreamReader;

/// Command for DlgSettingsCurveNames
class CmdSettingsCurveNames : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdSettingsCurveNames(MainWindow &mainWindow,
                        Document &document,
                        const CurveNameList &modelCurves);

  /// Constructor for parsing error report file xml
  CmdSettingsCurveNames(MainWindow &mainWindow,
                        Document &document,
                        const QString &cmdDescription,
                        QXmlStreamReader &reader);
  
  virtual ~CmdSettingsCurveNames();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdSettingsCurveNames();

  CurvesGraphs m_curvesGraphsBefore;
  CurvesGraphs m_curvesGraphsAfter;
};

#endif // CMD_SETTINGS_CURVE_NAMES_H
