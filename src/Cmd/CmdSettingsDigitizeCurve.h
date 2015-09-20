#ifndef CMD_SETTINGS_DIGITIZE_CURVE_H
#define CMD_SETTINGS_DIGITIZE_CURVE_H

#include "CmdAbstract.h"
#include "DocumentModelDigitizeCurve.h"

class QXmlStreamReader;

/// Command for DlgSettingsDigitizeCurve
class CmdSettingsDigitizeCurve : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdSettingsDigitizeCurve(MainWindow &mainWindow,
                           Document &document,
                           const DocumentModelDigitizeCurve &modelDigitizeCurveBefore,
                           const DocumentModelDigitizeCurve &modelDigitizeCurveAfter);

  /// Constructor for parsing error report file xml
  CmdSettingsDigitizeCurve(MainWindow &mainWindow,
                           Document &document,
                           const QString &cmdDescription,
                           QXmlStreamReader &reader);

  virtual ~CmdSettingsDigitizeCurve();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdSettingsDigitizeCurve();

  DocumentModelDigitizeCurve m_modelDigitizeCurveBefore;
  DocumentModelDigitizeCurve m_modelDigitizeCurveAfter;
};

#endif // CMD_SETTINGS_DIGITIZE_CURVE_H
