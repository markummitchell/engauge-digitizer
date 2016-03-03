/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdAbstract.h"
#include "CmdFactory.h"
#include "CmdMediator.h"
#include "CmdStackShadow.h"
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

    QUndoCommand *cmd = dynamic_cast<QUndoCommand*> (m_cmdList.front());

    m_cmdList.pop_front();

    if (m_mainWindow != 0) {
       m_mainWindow->cmdMediator()->push(cmd);
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
