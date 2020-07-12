/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CMD_DIGITIZE_STATE_H
#define CMD_DIGITIZE_STATE_H

#include "CmdAbstract.h"
#include "DigitizeState.h"

class QXmlStreamReader;

/// Command for changing the Digitize state
class CmdDigitizeState : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdDigitizeState(MainWindow &mainWindow,
                   Document &document,
                   DigitizeState stateBefore,
                   DigitizeState stateAfter);
  
  /// Constructor for parsing error report file xml
  CmdDigitizeState(MainWindow &mainWindow,
                   Document &document,
                   const QString &cmdDescription,
                   QXmlStreamReader &reader);

  virtual ~CmdDigitizeState();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdDigitizeState();

  // Values
  DigitizeState m_stateBefore;
  DigitizeState m_stateAfter;
};

#endif // CMD_DIGITIZE_STATE_H
