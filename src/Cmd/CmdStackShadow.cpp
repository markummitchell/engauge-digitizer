/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdAbstract.h"
#include "CmdFactory.h"
#include "CmdMediator.h"
#include "CmdRedoForTest.h"
#include "CmdStackShadow.h"
#include "CmdUndoForTest.h"
#include "Document.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QUndoCommand>
#include <QXmlStreamReader>
#include "Xml.h"

CmdStackShadow::CmdStackShadow() :
  m_mainWindow (0)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdStackShadow::CmdStackShadow";
}

bool CmdStackShadow::canRedo() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdStackShadow::canRedo";

  bool canRedo = (m_cmdList.count () > 0);

  return canRedo;
}

void CmdStackShadow::loadCommands (MainWindow &mainWindow,
                                   Document &document,
                                   QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdStackShadow::loadCommands";

  // Save pointer to MainWindow
  m_mainWindow = &mainWindow;

  // Signals for hack that allows script to perform redo/undo
  connect (this, SIGNAL (signalRedo ()), mainWindow.cmdMediator(), SLOT (redo ()));
  connect (this, SIGNAL (signalUndo ()), mainWindow.cmdMediator(), SLOT (undo ()));

  // Load commands
  CmdFactory factory;
  while (!reader.atEnd() && !reader.hasError()) {

    if ((loadNextFromReader (reader) == QXmlStreamReader::StartElement) &&
        (reader.name() == DOCUMENT_SERIALIZE_CMD)) {

      // Extract and append new command to command stack
      m_cmdList.push_back (factory.createCmd (mainWindow,
                                              document,
                                              reader));
    }
  }
}

void CmdStackShadow::slotRedo ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdStackShadow::slotRedo";

  if (m_cmdList.count() > 0) {

    // Get the next command from the shadow command stack
    QUndoCommand *cmd = dynamic_cast<QUndoCommand*> (m_cmdList.front());

    // Remove this command from the shadow command stack
    m_cmdList.pop_front();

    if (m_mainWindow != 0) {

      CmdRedoForTest *cmdRedoForTest = dynamic_cast<CmdRedoForTest*> (cmd);
      CmdUndoForTest *cmdUndoForTest = dynamic_cast<CmdUndoForTest*> (cmd);

      if (cmdRedoForTest != 0) {

        // Redo command is a special case. Redo of this command is equivalent to redo of the last command on the command stack
        // (which will never be CmdRedoForTest or CmdUndoForTest since they are never passed onto that command stack)
        emit (signalRedo ());

      } else if (cmdUndoForTest != 0) {

        // Undo command is a special case. Redo of this command is equivalent to undo of the last command on the command stack
        // (which will never be CmdRedoForTest or CmdUndoForTest since they are never passed onto that command stack)
        emit (signalUndo ());

      } else {

        // Normal command is simply pushed onto the primary command stack
        m_mainWindow->cmdMediator()->push(cmd);

      }
    }
  }
}

void CmdStackShadow::slotUndo()
{
  LOG4CPP_INFO_S ((*mainCat)) << "CmdStackShadow::slotUndo";

  CmdListInternal::iterator itr;
  for (itr = m_cmdList.begin(); itr != m_cmdList.end(); itr++) {

    CmdAbstract *cmd = *itr;
    delete cmd;
  }

  m_cmdList.clear();
}
