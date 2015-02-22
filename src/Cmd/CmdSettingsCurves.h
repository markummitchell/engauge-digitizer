#ifndef CMD_SETTINGS_CURVES_H
#define CMD_SETTINGS_CURVES_H

#include "CmdAbstract.h"
#include "CurvesGraphs.h"

class CurveNameList;
class QXmlStreamReader;

/// Command for DlgSettingsCurves
class CmdSettingsCurves : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdSettingsCurves(MainWindow &mainWindow,
                    Document &document,
                    const CurveNameList &modelCurves);

  /// Constructor for parsing error report file xml
  CmdSettingsCurves(MainWindow &mainWindow,
                    Document &document,
                    const QString &cmdDescription,
                    QXmlStreamReader &reader);

  virtual ~CmdSettingsCurves();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdSettingsCurves();

  CurvesGraphs m_curvesGraphsBefore;
  CurvesGraphs m_curvesGraphsAfter;
};

#endif // CMD_SETTINGS_CURVES_H
