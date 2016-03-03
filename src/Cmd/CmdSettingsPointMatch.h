/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CMD_SETTINGS_POINT_MATCH_H
#define CMD_SETTINGS_POINT_MATCH_H

#include "CmdAbstract.h"
#include "DocumentModelPointMatch.h"

class QXmlStreamReader;

/// Command for DlgSettingsPointMatch
class CmdSettingsPointMatch : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdSettingsPointMatch(MainWindow &mainWindow,
                        Document &document,
                        const DocumentModelPointMatch &modelPointMatchBefore,
                        const DocumentModelPointMatch &modelPointMatchAfter);

  /// Constructor for parsing error report file xml
  CmdSettingsPointMatch(MainWindow &mainWindow,
                        Document &document,
                        const QString &cmdDescription,
                        QXmlStreamReader &reader);

  virtual ~CmdSettingsPointMatch();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdSettingsPointMatch();

  DocumentModelPointMatch m_modelPointMatchBefore;
  DocumentModelPointMatch m_modelPointMatchAfter;
};

#endif // CMD_SETTINGS_POINT_MATCH_H
