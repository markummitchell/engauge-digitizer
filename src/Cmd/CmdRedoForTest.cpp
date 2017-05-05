/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdRedoForTest.h"
#include "DataKey.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QXmlStreamReader>
#include "Xml.h"

const QString CMD_DESCRIPTION ("RedoForTest");

CmdRedoForTest::CmdRedoForTest(MainWindow &mainWindow,
                               Document &document) :
  CmdAbstract (mainWindow,
               document,
               CMD_DESCRIPTION)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdRedoForTest::CmdRedoForTest";
}

CmdRedoForTest::CmdRedoForTest (MainWindow &mainWindow,
                                Document &document,
                                const QString &cmdDescription,
                                QXmlStreamReader & /* reader */) :
  CmdAbstract (mainWindow,
               document,
               cmdDescription)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdRedoForTest::CmdRedoForTest";
}

CmdRedoForTest::~CmdRedoForTest ()
{
}

void CmdRedoForTest::cmdRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdRedoForTest::cmdRedo";

  // Noop. Real Redo processing is performed externally on the command stack
}

void CmdRedoForTest::cmdUndo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdRedoForTest::cmdUndo";

  // Noop. Undo of an undo does not even make sense
}

void CmdRedoForTest::saveXml (QXmlStreamWriter & /* writer */) const
{
  // Noop. This command must be manually added to xml test files
}
