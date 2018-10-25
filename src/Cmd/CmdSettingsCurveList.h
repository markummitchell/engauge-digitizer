/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CMD_SETTINGS_CURVE_LIST_H
#define CMD_SETTINGS_CURVE_LIST_H

#include "CmdAbstract.h"
#include "CurvesGraphs.h"

class CurveNameList;
class QXmlStreamReader;

/// Command for DlgSettingsCurveList
class CmdSettingsCurveList : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdSettingsCurveList(MainWindow &mainWindow,
                       Document &document,
                       const CurveNameList &modelCurves);

  /// Constructor for parsing error report file xml
  CmdSettingsCurveList(MainWindow &mainWindow,
                       Document &document,
                       const QString &cmdDescription,
                       QXmlStreamReader &reader);
  
  virtual ~CmdSettingsCurveList();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdSettingsCurveList();

  CurvesGraphs m_curvesGraphsBefore;
  CurvesGraphs m_curvesGraphsAfter;
};

#endif // CMD_SETTINGS_CURVE_LIST_H
