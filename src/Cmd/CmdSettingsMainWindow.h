/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CMD_SETTINGS_MAIN_WINDOW_H
#define CMD_SETTINGS_MAIN_WINDOW_H

#include "CmdAbstract.h"
#include "MainWindowModel.h"

class QXmlStreamReader;

/// Command for DlgSettingsMainWindow
class CmdSettingsMainWindow : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdSettingsMainWindow(MainWindow &mainWindow,
                        Document &document,
                        const MainWindowModel &modelMainWindowBefore,
                        const MainWindowModel &modelMainWindowAfter);

  /// Constructor for parsing error report file xml
  CmdSettingsMainWindow(MainWindow &mainWindow,
                        Document &document,
                        const QString &cmdDescription,
                        QXmlStreamReader &reader);

  virtual ~CmdSettingsMainWindow();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdSettingsMainWindow();

  MainWindowModel m_modelMainWindowBefore;
  MainWindowModel m_modelMainWindowAfter;
};

#endif // CMD_SETTINGS_MAIN_WINDOW_H
