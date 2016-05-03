/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CMD_SETTINGS_GRID_DISPLAY_H
#define CMD_SETTINGS_GRID_DISPLAY_H

#include "CmdAbstract.h"
#include "DocumentModelGridDisplay.h"

class QXmlStreamReader;

/// Command for DlgSettingsGridDisplay
class CmdSettingsGridDisplay : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdSettingsGridDisplay(MainWindow &mainWindow,
                         Document &document,
                         const DocumentModelGridDisplay &modelGridDisplayBefore,
                         const DocumentModelGridDisplay &modelGridDisplayAfter);

  /// Constructor for parsing error report file xml
  CmdSettingsGridDisplay(MainWindow &mainWindow,
                         Document &document,
                         const QString &cmdDescription,
                         QXmlStreamReader &reader);

  virtual ~CmdSettingsGridDisplay();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdSettingsGridDisplay();

  DocumentModelGridDisplay m_modelGridDisplayBefore;
  DocumentModelGridDisplay m_modelGridDisplayAfter;
};

#endif // CMD_SETTINGS_GRID_DISPLAY_H
