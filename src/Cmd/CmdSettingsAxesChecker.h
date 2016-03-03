/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CMD_SETTINGS_AXES_CHECKER_H
#define CMD_SETTINGS_AXES_CHECKER_H

#include "CmdAbstract.h"
#include "DocumentModelAxesChecker.h"

class QXmlStreamReader;

/// Command for DlgSettingsAxesChecker
class CmdSettingsAxesChecker : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdSettingsAxesChecker(MainWindow &mainWindow,
                         Document &document,
                         const DocumentModelAxesChecker &modelAxesCheckerBefore,
                         const DocumentModelAxesChecker &modelAxesCheckerAfter);

  /// Constructor for parsing error report file xml
  CmdSettingsAxesChecker(MainWindow &mainWindow,
                         Document &document,
                         const QString &cmdDescription,
                         QXmlStreamReader &reader);

  virtual ~CmdSettingsAxesChecker();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdSettingsAxesChecker();

  DocumentModelAxesChecker m_modelAxesCheckerBefore;
  DocumentModelAxesChecker m_modelAxesCheckerAfter;
};

#endif // CMD_SETTINGS_AXES_CHECKER_H
