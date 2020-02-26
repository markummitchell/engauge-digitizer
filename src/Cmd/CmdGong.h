/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CMD_GONG_H
#define CMD_GONG_H

#include "CmdAbstract.h"

class QXmlStreamReader;

/// Command for sending a satisfying signal to the unit test framework to indicate completion of queued commands
class CmdGong : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdGong(MainWindow &mainWindow,
          Document &document);

  /// Constructor for parsing error report file xml
  CmdGong(MainWindow &mainWindow,
          Document &document,
          const QString &cmdDescription,
          QXmlStreamReader &reader);

  virtual ~CmdGong();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdGong();
};

#endif // CMD_GONG_H
