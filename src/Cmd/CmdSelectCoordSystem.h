/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CMD_SELECT_COORD_SYSTEM_H
#define CMD_SELECT_COORD_SYSTEM_H

#include "CmdAbstract.h"
#include "CoordSystemIndex.h"

class QXmlStreamReader;

/// Command for changing the currently selected CoordSystem
class CmdSelectCoordSystem : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdSelectCoordSystem(MainWindow &mainWindow,
                       Document &document,
                       CoordSystemIndex coordSystem);

  /// Constructor for parsing error report file xml
  CmdSelectCoordSystem(MainWindow &mainWindow,
                       Document &document,
                       const QString &cmdDescription,
                       QXmlStreamReader &reader);
  
  virtual ~CmdSelectCoordSystem();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdSelectCoordSystem();

  CoordSystemIndex m_coordSystemIndexBefore;
  CoordSystemIndex m_coordSystemIndexAfter;
};

#endif // CMD_SELECT_COORD_SYSTEM_H
