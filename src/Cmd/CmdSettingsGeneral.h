/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CMD_SETTINGS_GENERAL_H
#define CMD_SETTINGS_GENERAL_H

#include "CmdAbstract.h"
#include "DocumentModelGeneral.h"

class QXmlStreamReader;

/// Command for DlgSettingsGeneral
class CmdSettingsGeneral : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdSettingsGeneral(MainWindow &mainWindow,
                    Document &document,
                    const DocumentModelGeneral &modelGeneralBefore,
                    const DocumentModelGeneral &modelGeneralAfter);

  /// Constructor for parsing error report file xml
  CmdSettingsGeneral(MainWindow &mainWindow,
                    Document &document,
                    const QString &cmdDescription,
                    QXmlStreamReader &reader);

  virtual ~CmdSettingsGeneral();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;
  
private:
  CmdSettingsGeneral();

  DocumentModelGeneral m_modelGeneralBefore;
  DocumentModelGeneral m_modelGeneralAfter;
};

#endif // CMD_SETTINGS_GENERAL_H
