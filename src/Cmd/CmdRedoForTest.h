/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CMD_REDO_FOR_TEST_H
#define CMD_REDO_FOR_TEST_H

#include "CmdAbstract.h"
#include "CurvesGraphs.h"
#include <QHash>
#include <QStringList>

class QXmlStreamReader;

/// Command for performing Redo during testing. This command is never created automatically, since when the user triggers
/// an Redo that just results in the command stack getting backed up by one command. This command is manually created by
/// editing an xml test file
class CmdRedoForTest : public CmdAbstract
{
public:
  /// Constructor for normal creation
  CmdRedoForTest(MainWindow &mainWindow,
                 Document &document);

  /// Constructor for parsing error report file xml
  CmdRedoForTest(MainWindow &mainWindow,
                 Document &document,
                 const QString &cmdDescription,
                 QXmlStreamReader &reader);

  virtual ~CmdRedoForTest();

  virtual void cmdRedo ();
  virtual void cmdUndo ();
  virtual void saveXml (QXmlStreamWriter &writer) const;

private:
  CmdRedoForTest();

};

#endif // CMD_REDO_FOR_TEST_H
